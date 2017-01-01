#include "dac.h"
#include "gpio.h"
#include "registerset.h"

static volatile uint32_t * const rcc_apb1enr =
    (volatile uint32_t *)(REG_RCC_ADDR + REG_RCC_APB1ENR_OFFS);

static volatile uint32_t * const dac_cr =
    (volatile uint32_t *)(REG_DAC_ADDR + REG_DAC_CR_OFFS);
static volatile uint32_t * const dac_swtrigr =
    (volatile uint32_t *)(REG_DAC_ADDR + REG_DAC_SWTRIGR_OFFS);

static volatile uint32_t * const dac_dhr12r[] = {
    (volatile uint32_t *)(REG_DAC_ADDR + REG_DAC_DHR12R1_OFFS),
    (volatile uint32_t *)(REG_DAC_ADDR + REG_DAC_DHR12R2_OFFS),
};

static const struct gpio_pin dac_pins[] = {
    {'A', 4},
    {'A', 5},
};

static const uint32_t reg_dac_swtrigr_swtrig_mask[] = {
    REG_DAC_SWTRIGR_SWTRIG1_MASK,
    REG_DAC_SWTRIGR_SWTRIG2_MASK,
};

static const uint32_t reg_dac_cr_tsel_pos[] = {
    REG_DAC_CR_TSEL1_POS,
    REG_DAC_CR_TSEL2_POS,
};

static const uint32_t reg_dac_cr_en_mask[] = {
    REG_DAC_CR_EN1_MASK,
    REG_DAC_CR_EN2_MASK,
};

static const uint32_t reg_dac_cr_ten_mask[] = {
    REG_DAC_CR_TEN1_MASK,
    REG_DAC_CR_TEN2_MASK,
};

void dac_init(void) {

    // Enable the DAC clock.
    *rcc_apb1enr |= REG_RCC_APB1ENR_DACEN_MASK;

}

void dac_enable_channel(int channel) {

    // The pins need to be configured as an analog input.
    gpio_setup_input_pin(dac_pins[channel - 1], GPIO_INPUT_MODE_ANALOG);

    // Enable software triggering.
    *dac_swtrigr |= reg_dac_swtrigr_swtrig_mask[channel - 1];

    // Set trigger source to software trigger.
    *dac_cr |= 7 << reg_dac_cr_tsel_pos[channel - 1];

    // Enable the channel.
    *dac_cr |= reg_dac_cr_en_mask[channel - 1];

}

void dac_set_output(int channel, uint16_t level) {

    // Set the level.
    *dac_dhr12r[channel - 1] = level;

    // Trigger the output.
    *dac_cr |= reg_dac_cr_ten_mask[channel - 1];
    *dac_cr &= ~reg_dac_cr_ten_mask[channel - 1];

}
