#include <stddef.h>
#include <stdint.h>

#include "registerset.h"
#include "usart.h"
#include "interrupt.h"

static volatile uint32_t *nvic_iser1 =
    (volatile uint32_t *)(NVIC_ADDR + NVIC_ISER1_OFFS);
static volatile uint32_t *rcc_apb2enr =
    (volatile uint32_t *)(RCC_ADDR + RCC_APB2ENR_OFFS);
static volatile uint32_t *gpio_porta_crh =
    (volatile uint32_t *)(GPIO_PORTA_ADDR + GPIO_CRH_OFFS);
static volatile uint32_t *usart1_cr1 =
    (volatile uint32_t *)(USART1_ADDR + USART_CR1_OFFS);
static volatile uint32_t *usart1_brr =
    (volatile uint32_t *)(USART1_ADDR + USART_BRR_OFFS);
static volatile uint32_t *usart1_sr =
    (volatile uint32_t *)(USART1_ADDR + USART_SR_OFFS);
static volatile uint8_t *usart1_dr =
    (volatile uint8_t *)(USART1_ADDR + USART_DR_OFFS);

struct fifo {
    uint8_t buf[USART_FIFO_SIZE];
    int in;
    int out;
};

static volatile struct fifo tx_fifo;
static volatile struct fifo rx_fifo;

static volatile int tx;

static void fifo_init(volatile struct fifo *f) {
    f->in = 0;
    f->out = 0;
}

static int fifo_dequeue(volatile struct fifo *f, uint8_t *b) {
    if (f->in == f->out)
        return 0;

    if (b)
        *b = f->buf[f->out];

    f->out = (f->out + 1) % USART_FIFO_SIZE;

    return 1;
}

static int fifo_enqueue(volatile struct fifo *f, uint8_t b) {
    if (f->in == ((f->out - 1 + USART_FIFO_SIZE) % USART_FIFO_SIZE))
        return 0;

    f->buf[f->in] = b;
    f->in = (f->in + 1) % USART_FIFO_SIZE;

    return 1;
}

void usart1_isr(void) {
    if (*usart1_sr & USART_SR_RXNE_MASK) {
        *usart1_sr &= ~(USART_SR_RXNE_MASK);
        fifo_enqueue(&rx_fifo, *usart1_dr);
    }

    if (*usart1_sr & USART_SR_TC_MASK) {
        char c;
        *usart1_sr &= ~(USART_SR_TC_MASK);
        if (fifo_dequeue(&tx_fifo, &c)) {
            *usart1_dr = c;
        } else {
            tx = 0;
        }
    }
}

int usart_init(void) {
    tx = 0;
    fifo_init(&tx_fifo);
    fifo_init(&rx_fifo);

    // Enable USART1 clock.
    *rcc_apb2enr |= RCC_APB2ENR_USART1EN_MASK;

    // Enable AFIO clock.
    *rcc_apb2enr |= RCC_APB2ENR_AFIOEN_MASK;

    // Enable GPIO port A clock.
    *rcc_apb2enr |= RCC_APB2ENR_IOPAEN_MASK;

    // Set baud rate.
    *usart1_brr &= ~USART_BRR_DIV_FRACTION_MASK;
    *usart1_brr |= 1 << USART_BRR_DIV_FRACTION_POS;
    *usart1_brr &= ~USART_BRR_DIV_MANTISSA_MASK;
    *usart1_brr |= 52 << USART_BRR_DIV_MANTISSA_POS;

    // Enable TX pin.
    *gpio_porta_crh &= ~GPIO_CRH_MODE9_MASK;
    *gpio_porta_crh |= 3 << GPIO_CRH_MODE9_POS;

    *gpio_porta_crh &= ~GPIO_CRH_CNF9_MASK;
    *gpio_porta_crh |= 2 << GPIO_CRH_CNF9_POS;

    // Enable RX pin.
    *gpio_porta_crh &= ~GPIO_CRH_MODE10_MASK;
    *gpio_porta_crh |= 0 << GPIO_CRH_MODE10_POS;

    *gpio_porta_crh &= ~GPIO_CRH_CNF10_MASK;
    *gpio_porta_crh |= 2 << GPIO_CRH_CNF10_POS;

    // Enable USART1 interrupts.
    *usart1_cr1 |= USART_CR1_TCIE_MASK;
    *usart1_cr1 |= USART_CR1_RXNEIE_MASK;

    // Enable USART1 interrupts in NVIC.
    *nvic_iser1 |= NVIC_ISER1_USART1_MASK;

    // Enable USART1.
    *usart1_cr1 |= USART_CR1_UE_MASK;
    *usart1_cr1 |= USART_CR1_RE_MASK;
    *usart1_cr1 |= USART_CR1_TE_MASK;

    return 1;
}

size_t usart_read(uint8_t *buf, size_t count) {
    const uint8_t *end = buf + count;
    int i = 0;

    while (buf < end && fifo_dequeue(&rx_fifo, buf)) {
        i++;
        buf++;
    }

    return i;
}

void usart_write(const uint8_t *buf, size_t count) {
    const uint8_t *end = buf + count;
    while (buf < end) {
        //asm volatile ("cpsid i");
        interrupt_disable();

        if (!tx) {
            tx = 1;
            *usart1_dr = *buf;
        } else {
            while (1) {
                if (fifo_enqueue(&tx_fifo, *buf))
                    break;
                //asm volatile ("cpsie i");
                interrupt_enable();
                //asm volatile ("cpsid i");
                interrupt_disable();
            }
        }

        //asm volatile ("cpsie i");
        interrupt_enable();

        buf++;
    }
}

void usart_putc(char c) {
    usart_write(&c, 1);
}

void usart_getc(char *c) {
    while (!usart_read(c, 1));
}

void usart_puts(const char *s) {
    while (*s)
        usart_write(s++, 1);
}

void usart_gets(char *s, size_t count) {
    char *end = s + count - 1;

    while (s < end) {
        usart_getc(s);

        if (*s == '\r') {
            *s = '\0';
            return;
        }

        if (*s != '\b')
            s++;
        else
            s--;
    }

    *s = '\0';
}
