#include <stdint.h>

#include "adc.h"
#include "gpio.h"
#include "registerset.h"

static volatile uint32_t * const rcc_apb2enr =
    (volatile uint32_t *)(REG_RCC_ADDR + REG_RCC_APB2ENR_OFFS);

static volatile uint32_t * const adc_sr =
    (volatile uint32_t *)(REG_ADC1_ADDR + REG_ADC_SR_OFFS);
static volatile uint32_t * const adc_cr2 =
    (volatile uint32_t *)(REG_ADC1_ADDR + REG_ADC_CR2_OFFS);
static volatile uint32_t * const adc_sqr3 =
    (volatile uint32_t *)(REG_ADC1_ADDR + REG_ADC_SQR3_OFFS);
static volatile uint32_t * const adc_dr =
    (volatile uint32_t *)(REG_ADC1_ADDR + REG_ADC_DR_OFFS);

static const struct gpio_pin adc_pins[] = {
    {'A', 0}, {'A', 1}, {'A', 2}, {'A', 3},
    {'A', 4}, {'A', 5}, {'A', 6}, {'A', 7},
    {'B', 0}, {'B', 1}, {'C', 0}, {'C', 1},
    {'C', 2}, {'C', 3}, {'C', 4}, {'C', 5},
};

void adc_init(void) {

    // Enable ADC clock.
    *rcc_apb2enr |= REG_RCC_APB2ENR_ADC1EN_MASK;

    // Enable ADC.
    *adc_cr2 |= REG_ADC_CR2_ADON_MASK;

    // Calibrate ADC.
    *adc_cr2 |= REG_ADC_CR2_CAL_MASK;
    while (*adc_cr2 & REG_ADC_CR2_CAL_MASK);

}

void adc_enable_channel(int channel) {

    gpio_setup_input_pin(adc_pins[channel], GPIO_INPUT_MODE_ANALOG);

}

uint16_t adc_sample(int channel) {

    // Select the channel for conversion.
    *adc_sqr3 &= ~REG_ADC_SQR3_SQ1_MASK;
    *adc_sqr3 |= channel << REG_ADC_SQR3_SQ1_POS;

    // Start the conversion.
    *adc_cr2 |= REG_ADC_CR2_ADON_MASK;

    // Wait for conversion to end.
    while (!(*adc_sr & REG_ADC_SR_EOC_MASK));

    return *adc_dr;
}
