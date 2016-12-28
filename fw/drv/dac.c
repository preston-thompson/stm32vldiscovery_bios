#include "dac.h"
#include "gpio.h"
#include "registerset.h"

static volatile uint32_t * const rcc_apb1enr =
    (volatile uint32_t *)(REG_RCC_ADDR + REG_RCC_APB1ENR_OFFS);

static volatile uint32_t * const dac_cr =
    (volatile uint32_t *)(REG_DAC_ADDR + REG_DAC_CR_OFFS);
static volatile uint32_t * const dac_swtrigr =
    (volatile uint32_t *)(REG_DAC_ADDR + REG_DAC_SWTRIGR_OFFS);
static volatile uint32_t * const dac_dhr12r1 =
    (volatile uint32_t *)(REG_DAC_ADDR + REG_DAC_DHR12R1_OFFS);
static volatile uint32_t * const dac_dhr12r2 =
    (volatile uint32_t *)(REG_DAC_ADDR + REG_DAC_DHR12R2_OFFS);

static const struct gpio_pin dac_pins[] = {
    {'A', 4},
    {'A', 5},
};

void dac_enable_channel(int channel) {

    // Interestingly enough, the pins should first be configured as an analog
    // input. From the datasheet: "In order to avoid parasitic consumption."
    gpio_setup_input_pin(dac_pins[channel - 1], GPIO_INPUT_MODE_ANALOG);

    // Enable the DAC clock.
    *rcc_apb1enr |= REG_RCC_APB1ENR_DACEN_MASK;

    if (channel == 1) {

        // Enable software triggering.
        *dac_swtrigr |= REG_DAC_SWTRIGR_SWTRIG1_MASK;

        // Set trigger source to software trigger.
        *dac_cr |= 7 << REG_DAC_CR_TSEL1_POS;

        // Enable the channel.
        *dac_cr |= REG_DAC_CR_EN1_MASK;

    } else if (channel == 2) {

        // Enable software triggering.
        *dac_swtrigr |= REG_DAC_SWTRIGR_SWTRIG2_MASK;

        // Set trigger source to software trigger.
        *dac_cr |= 7 << REG_DAC_CR_TSEL2_POS;

        // Enable the channel.
        *dac_cr |= REG_DAC_CR_EN2_MASK;

    }

}

void dac_set_output(int channel, uint16_t level) {

    if (channel == 1) {

        // Set the level.
        *dac_dhr12r1 = level;

        // Trigger the output.
        *dac_cr |= REG_DAC_CR_TEN1_MASK;
        *dac_cr &= ~REG_DAC_CR_TEN1_MASK;

    } else if (channel == 2) {

        // Set the level.
        *dac_dhr12r2 = level;

        // Trigger the output.
        *dac_cr |= REG_DAC_CR_TEN2_MASK;
        *dac_cr &= ~REG_DAC_CR_TEN2_MASK;

    }

}
