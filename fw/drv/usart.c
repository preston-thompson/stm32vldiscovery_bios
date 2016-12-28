#include <stddef.h>
#include <stdint.h>

#include "registerset.h"
#include "usart.h"
#include "gpio.h"
#include "interrupt.h"

static volatile uint32_t * const nvic_iser1 =
    (volatile uint32_t *)(REG_NVIC_ADDR + REG_NVIC_ISER1_OFFS);
static volatile uint32_t * const rcc_apb2enr =
    (volatile uint32_t *)(REG_RCC_ADDR + REG_RCC_APB2ENR_OFFS);
static volatile uint32_t * const usart1_cr1 =
    (volatile uint32_t *)(REG_USART1_ADDR + REG_USART_CR1_OFFS);
static volatile uint32_t * const usart1_brr =
    (volatile uint32_t *)(REG_USART1_ADDR + REG_USART_BRR_OFFS);
static volatile uint32_t * const usart1_sr =
    (volatile uint32_t *)(REG_USART1_ADDR + REG_USART_SR_OFFS);
static volatile uint8_t * const usart1_dr =
    (volatile uint8_t *)(REG_USART1_ADDR + REG_USART_DR_OFFS);

static const struct gpio_pin tx_pin = {'A', 9};
static const struct gpio_pin rx_pin = {'A', 10};

static uint8_t rx_buf[64];
static size_t rx_buf_count = 0;

void usart1_isr(void) {

    if (*usart1_sr & REG_USART_SR_RXNE_MASK) {

        *usart1_sr &= ~(REG_USART_SR_RXNE_MASK);

        if (rx_buf_count < sizeof(rx_buf))
            rx_buf[rx_buf_count++] = *usart1_dr;

    }
}

void usart_init(void) {
    // Enable USART1 clock.
    *rcc_apb2enr |= REG_RCC_APB2ENR_USART1EN_MASK;

    // Set baud rate.
    // BAUD     FRACTION    MANTISSA
    // 9600     1           52
    // 115200   5           4
    *usart1_brr &= ~REG_USART_BRR_DIV_FRACTION_MASK;
    *usart1_brr |= 5 << REG_USART_BRR_DIV_FRACTION_POS;
    *usart1_brr &= ~REG_USART_BRR_DIV_MANTISSA_MASK;
    *usart1_brr |= 4 << REG_USART_BRR_DIV_MANTISSA_POS;

    // Enable TX pin.
    gpio_setup_output_pin(tx_pin, GPIO_OUTPUT_MODE_AF_PUSH_PULL, GPIO_OUTPUT_SPEED_50MHZ);

    // Enable RX pin.
    gpio_setup_input_pin(rx_pin, GPIO_INPUT_MODE_PULL);

    // Enable USART1 interrupts.
    *usart1_cr1 |= REG_USART_CR1_RXNEIE_MASK;

    // Enable USART1 interrupts in NVIC.
    *nvic_iser1 |= REG_NVIC_ISER1_USART1_MASK;

    // Enable USART1.
    *usart1_cr1 |= REG_USART_CR1_UE_MASK;
    *usart1_cr1 |= REG_USART_CR1_RE_MASK;
    *usart1_cr1 |= REG_USART_CR1_TE_MASK;
}

size_t usart_read(void *dst, size_t count) {

    uint8_t *dstb = dst;

    if (rx_buf_count <= count) {

        size_t rv = rx_buf_count;

        for (int i = 0; i < rx_buf_count; i++)
            *dstb++ = rx_buf[i];

        rx_buf_count = 0;
        return rv;

    } else {

        for (int i = 0; i < count; i++)
            *dstb++ = rx_buf[i];

        for (int i = 0; i < rx_buf_count - count; i++)
            rx_buf[i] = rx_buf[i + count];

        rx_buf_count -= count;
        return count;

    }

}

size_t usart_in_waiting(void) {

    return rx_buf_count;

}

void usart_write(const void *src, size_t count) {

    const uint8_t *srcb = src;

    for (int i = 0; i < count; i++) {

        // Wait for completion of previous transfer.
        while (!(*usart1_sr & REG_USART_SR_TC_MASK));

        // Send byte.
        *usart1_dr = *srcb++;

    }

}
