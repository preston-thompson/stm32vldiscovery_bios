#include <stdint.h>

#include "pwm.h"
#include "gpio.h"
#include "registerset.h"

static volatile uint32_t * const rcc_apb1enr =
    (volatile uint32_t *)(REG_RCC_ADDR + REG_RCC_APB1ENR_OFFS);

static volatile uint16_t * const tim_cr1[] = {
    (volatile uint16_t *)(REG_TIM2_ADDR + REG_TIM_CR1_OFFS),
    (volatile uint16_t *)(REG_TIM3_ADDR + REG_TIM_CR1_OFFS),
    (volatile uint16_t *)(REG_TIM4_ADDR + REG_TIM_CR1_OFFS),
};

static volatile uint16_t * const tim_arr[] = {
    (volatile uint16_t *)(REG_TIM2_ADDR + REG_TIM_ARR_OFFS),
    (volatile uint16_t *)(REG_TIM3_ADDR + REG_TIM_ARR_OFFS),
    (volatile uint16_t *)(REG_TIM4_ADDR + REG_TIM_ARR_OFFS),
};

static volatile uint16_t * const tim_ccmr1[] = {
    (volatile uint16_t *)(REG_TIM2_ADDR + REG_TIM_CCMR1_OFFS),
    (volatile uint16_t *)(REG_TIM3_ADDR + REG_TIM_CCMR1_OFFS),
    (volatile uint16_t *)(REG_TIM4_ADDR + REG_TIM_CCMR1_OFFS),
};

static volatile uint16_t * const tim_ccmr2[] = {
    (volatile uint16_t *)(REG_TIM2_ADDR + REG_TIM_CCMR2_OFFS),
    (volatile uint16_t *)(REG_TIM3_ADDR + REG_TIM_CCMR2_OFFS),
    (volatile uint16_t *)(REG_TIM4_ADDR + REG_TIM_CCMR2_OFFS),
};

static volatile uint16_t * const tim_ccr[][4] = {
    {
        (volatile uint16_t *)(REG_TIM2_ADDR + REG_TIM_CCR1_OFFS),
        (volatile uint16_t *)(REG_TIM2_ADDR + REG_TIM_CCR2_OFFS),
        (volatile uint16_t *)(REG_TIM2_ADDR + REG_TIM_CCR3_OFFS),
        (volatile uint16_t *)(REG_TIM2_ADDR + REG_TIM_CCR4_OFFS),
    },
    {
        (volatile uint16_t *)(REG_TIM3_ADDR + REG_TIM_CCR1_OFFS),
        (volatile uint16_t *)(REG_TIM3_ADDR + REG_TIM_CCR2_OFFS),
        (volatile uint16_t *)(REG_TIM3_ADDR + REG_TIM_CCR3_OFFS),
        (volatile uint16_t *)(REG_TIM3_ADDR + REG_TIM_CCR4_OFFS),
    },
    {
        (volatile uint16_t *)(REG_TIM4_ADDR + REG_TIM_CCR1_OFFS),
        (volatile uint16_t *)(REG_TIM4_ADDR + REG_TIM_CCR2_OFFS),
        (volatile uint16_t *)(REG_TIM4_ADDR + REG_TIM_CCR3_OFFS),
        (volatile uint16_t *)(REG_TIM4_ADDR + REG_TIM_CCR4_OFFS),
    },
};

static volatile uint16_t * const tim_egr[] = {
    (volatile uint16_t *)(REG_TIM2_ADDR + REG_TIM_EGR_OFFS),
    (volatile uint16_t *)(REG_TIM3_ADDR + REG_TIM_EGR_OFFS),
    (volatile uint16_t *)(REG_TIM4_ADDR + REG_TIM_EGR_OFFS),
};

static volatile uint16_t * const tim_ccer[] = {
    (volatile uint16_t *)(REG_TIM2_ADDR + REG_TIM_CCER_OFFS),
    (volatile uint16_t *)(REG_TIM3_ADDR + REG_TIM_CCER_OFFS),
    (volatile uint16_t *)(REG_TIM4_ADDR + REG_TIM_CCER_OFFS),
};

static const struct gpio_pin pwm_pins[][4] = {
    {{'A', 0}, {'A', 1}, {'A', 2}, {'A', 3}},
    {{'A', 6}, {'A', 7}, {'B', 0}, {'B', 1}},
    {{'B', 6}, {'B', 7}, {'B', 8}, {'B', 9}},
};

void pwm_init(void) {

    // Enable timer clocks.
    *rcc_apb1enr |= REG_RCC_APB1ENR_TIM2EN_MASK;
    *rcc_apb1enr |= REG_RCC_APB1ENR_TIM3EN_MASK;
    *rcc_apb1enr |= REG_RCC_APB1ENR_TIM4EN_MASK;

}

void pwm_enable_timer(int timer, uint16_t period) {

    // Convert to zero-based indexing.
    timer -= 2;

    // Set timer period.
    *tim_arr[timer] = period;

    // Set channels to PWM mode 1.
    *tim_ccmr1[timer] &= ~REG_TIM_CCMR1_OC1M_MASK;
    *tim_ccmr1[timer] &= ~REG_TIM_CCMR1_OC2M_MASK;
    *tim_ccmr1[timer] |= 6 << REG_TIM_CCMR1_OC1M_POS;
    *tim_ccmr1[timer] |= 6 << REG_TIM_CCMR1_OC2M_POS;

    *tim_ccmr2[timer] &= ~REG_TIM_CCMR2_OC3M_MASK;
    *tim_ccmr2[timer] &= ~REG_TIM_CCMR2_OC4M_MASK;
    *tim_ccmr2[timer] |= 6 << REG_TIM_CCMR2_OC3M_POS;
    *tim_ccmr2[timer] |= 6 << REG_TIM_CCMR2_OC4M_POS;

    // Enable preload on channels.
    *tim_ccmr1[timer] |= REG_TIM_CCMR1_OC1PE_MASK;
    *tim_ccmr1[timer] |= REG_TIM_CCMR1_OC2PE_MASK;
    *tim_ccmr2[timer] |= REG_TIM_CCMR2_OC3PE_MASK;
    *tim_ccmr2[timer] |= REG_TIM_CCMR2_OC4PE_MASK;

    *tim_cr1[timer] |= REG_TIM_CR1_ARPE_MASK;

    *tim_cr1[timer] |= REG_TIM_CR1_CEN_MASK;

    *tim_egr[timer] |= REG_TIM_EGR_UG_MASK;

}

void pwm_enable_channel(int timer, int channel) {

    // Convert to zero-based indexing.
    channel -= 1;
    timer -= 2;

    gpio_setup_output_pin(
        pwm_pins[timer][channel],
        GPIO_OUTPUT_MODE_AF_PUSH_PULL,
        GPIO_OUTPUT_SPEED_10MHZ
    );

    switch (channel) {
        case 0:
            *tim_ccer[timer] |= REG_TIM_CCER_CC1E_MASK;
            break;
        case 1:
            *tim_ccer[timer] |= REG_TIM_CCER_CC2E_MASK;
            break;
        case 2:
            *tim_ccer[timer] |= REG_TIM_CCER_CC3E_MASK;
            break;
        case 3:
            *tim_ccer[timer] |= REG_TIM_CCER_CC4E_MASK;
            break;
    }

}

void pwm_set_channel_duty_cycle(int timer, int channel, uint16_t reset) {

    // Convert to zero-based indexing.
    channel -= 1;
    timer -= 2;

    // Set duty cycle.
    *tim_ccr[timer][channel] = reset;

}
