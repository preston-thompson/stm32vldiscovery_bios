#include <stddef.h>
#include <stdint.h>

#include "gpio.h"
#include "registerset.h"

static volatile uint32_t * const rcc_apb2enr =
    (volatile uint32_t *)(REG_RCC_ADDR + REG_RCC_APB2ENR_OFFS);

static volatile uint32_t * const gpio_port_crl[] = {
    (volatile uint32_t *)(REG_GPIO_PORTA_ADDR + REG_GPIO_CRL_OFFS),
    (volatile uint32_t *)(REG_GPIO_PORTB_ADDR + REG_GPIO_CRL_OFFS),
    (volatile uint32_t *)(REG_GPIO_PORTC_ADDR + REG_GPIO_CRL_OFFS),
    (volatile uint32_t *)(REG_GPIO_PORTD_ADDR + REG_GPIO_CRL_OFFS),
    (volatile uint32_t *)(REG_GPIO_PORTE_ADDR + REG_GPIO_CRL_OFFS),
};

static volatile uint32_t * const gpio_port_crh[] = {
    (volatile uint32_t *)(REG_GPIO_PORTA_ADDR + REG_GPIO_CRH_OFFS),
    (volatile uint32_t *)(REG_GPIO_PORTB_ADDR + REG_GPIO_CRH_OFFS),
    (volatile uint32_t *)(REG_GPIO_PORTC_ADDR + REG_GPIO_CRH_OFFS),
    (volatile uint32_t *)(REG_GPIO_PORTD_ADDR + REG_GPIO_CRH_OFFS),
    (volatile uint32_t *)(REG_GPIO_PORTE_ADDR + REG_GPIO_CRH_OFFS),
};

static volatile uint16_t * const gpio_port_odr[] = {
    (volatile uint16_t *)(REG_GPIO_PORTA_ADDR + REG_GPIO_ODR_OFFS),
    (volatile uint16_t *)(REG_GPIO_PORTB_ADDR + REG_GPIO_ODR_OFFS),
    (volatile uint16_t *)(REG_GPIO_PORTC_ADDR + REG_GPIO_ODR_OFFS),
    (volatile uint16_t *)(REG_GPIO_PORTD_ADDR + REG_GPIO_ODR_OFFS),
    (volatile uint16_t *)(REG_GPIO_PORTE_ADDR + REG_GPIO_ODR_OFFS),
};

static volatile uint16_t * const gpio_port_idr[] = {
    (volatile uint16_t *)(REG_GPIO_PORTA_ADDR + REG_GPIO_IDR_OFFS),
    (volatile uint16_t *)(REG_GPIO_PORTB_ADDR + REG_GPIO_IDR_OFFS),
    (volatile uint16_t *)(REG_GPIO_PORTC_ADDR + REG_GPIO_IDR_OFFS),
    (volatile uint16_t *)(REG_GPIO_PORTD_ADDR + REG_GPIO_IDR_OFFS),
    (volatile uint16_t *)(REG_GPIO_PORTE_ADDR + REG_GPIO_IDR_OFFS),
};

void gpio_init(void) {

    // Enable AFIO clock.
    *rcc_apb2enr |= REG_RCC_APB2ENR_AFIOEN_MASK;

    // Enable GPIO port clocks.
    *rcc_apb2enr |= REG_RCC_APB2ENR_IOPAEN_MASK;
    *rcc_apb2enr |= REG_RCC_APB2ENR_IOPBEN_MASK;
    *rcc_apb2enr |= REG_RCC_APB2ENR_IOPCEN_MASK;
    *rcc_apb2enr |= REG_RCC_APB2ENR_IOPDEN_MASK;
    *rcc_apb2enr |= REG_RCC_APB2ENR_IOPEEN_MASK;

}

void gpio_setup_input_pin(struct gpio_pin pin, enum gpio_pin_mode mode) {

    // Convert to zero-based indexing.
    pin.port -= 'A';

    if (pin.pin > 7) {
        *gpio_port_crh[pin.port] &= ~(0xF << ((pin.pin - 8) * 4));
        *gpio_port_crh[pin.port] |= mode << (2 + ((pin.pin - 8) * 4));
    } else {
        *gpio_port_crl[pin.port] &= ~(0xF << (pin.pin * 4));
        *gpio_port_crl[pin.port] |= mode << (2 + pin.pin * 4);
    }

}

void gpio_setup_output_pin(struct gpio_pin pin, enum gpio_pin_mode mode, enum gpio_pin_speed speed) {

    // Convert to zero-based indexing.
    pin.port -= 'A';

    // Set the mode and speed of the pin.
    if (pin.pin > 7) {
        *gpio_port_crh[pin.port] &= ~(0xF << ((pin.pin - 8) * 4));
        *gpio_port_crh[pin.port] |= mode << (2 + ((pin.pin - 8) * 4));
        *gpio_port_crh[pin.port] |= speed << ((pin.pin - 8) * 4);
    }
    else {
        *gpio_port_crl[pin.port] &= ~(0xF << (pin.pin * 4));
        *gpio_port_crl[pin.port] |= mode << (2 + pin.pin * 4);
        *gpio_port_crl[pin.port] |= speed << (pin.pin * 4);
    }

}

void gpio_set_pin(struct gpio_pin pin, int state) {

    // Convert to zero-based indexing.
    pin.port -= 'A';

    // Set the pin.
    if (state)
        *gpio_port_odr[pin.port] |= (1 << pin.pin);
    else
        *gpio_port_odr[pin.port] &= ~(1 << pin.pin);

}

int gpio_get_pin(struct gpio_pin pin) {

    int state;

    // Convert to zero-based indexing.
    pin.port -= 'A';

    // Get the state of the pin.
    state = *gpio_port_idr[pin.port] & (1 << pin.pin);

    if (state)
        return 1;
    else
        return 0;

}
