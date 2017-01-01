#include "rpc.h"
#include "drv/gpio.h"
#include "drv/usart.h"
#include "drv/flash.h"
#include "drv/rtc.h"
#include "drv/dac.h"
#include "drv/adc.h"
#include "drv/pwm.h"
#include "drv/interrupt.h"

static const struct gpio_pin blue_led = {'C', 8};
static const struct gpio_pin green_led = {'C', 9};

void main(void) {

    gpio_init();
    usart_init();
    pwm_init();
    adc_init();
    dac_init();

    // Set up the RTC for a frequency of 1 Hz.
    rtc_set_prescaler(0x7fff);
    rtc_set_count(0);

    // Turn on the blue LED for good measure. Blue is a nice color.
    gpio_setup_output_pin(blue_led, GPIO_OUTPUT_MODE_GPIO_PUSH_PULL, GPIO_OUTPUT_SPEED_2MHZ);
    gpio_set_pin(blue_led, 1);

    interrupt_enable();

    // Listen for commands.
    rpc_listen();

}
