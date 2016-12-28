#include "rpc.h"
#include "drv/gpio.h"
#include "drv/usart.h"
#include "drv/flash.h"
#include "drv/rtc.h"
#include "drv/dac.h"
#include "drv/interrupt.h"

static const struct gpio_pin blue_led = {'C', 8};
static const struct gpio_pin green_led = {'C', 9};

void main(void) {
    gpio_init();
    usart_init();
    flash_init();
    rtc_set_prescaler(0x7fff);
    rtc_set_count(0);

    gpio_setup_output_pin(blue_led, GPIO_OUTPUT_MODE_GPIO_PUSH_PULL, GPIO_OUTPUT_SPEED_2MHZ);

    interrupt_enable();

    gpio_set_pin(blue_led, 1);

    dac_enable_channel(1);

    while (1)
        for (uint16_t i = 0; i < 0x1000; i++) {
            dac_set_output(1, i);
        }

    rpc_listen();
}
