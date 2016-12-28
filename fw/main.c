#include "rpc.h"
#include "drv/gpio.h"
#include "drv/usart.h"
#include "drv/flash.h"
#include "drv/rtc.h"
#include "drv/interrupt.h"

static const struct gpio_pin blue_led = {'C', 8};

void main(void) {
    gpio_init();
    usart_init();
    flash_init();
    rtc_set_prescaler(0x7fff);
    rtc_set_count(0);

    gpio_setup_output_pin(blue_led, GPIO_OUTPUT_MODE_GPIO_PUSH_PULL, GPIO_OUTPUT_SPEED_2MHZ);

    interrupt_enable();

    gpio_set_pin(blue_led, 1);

    rpc_listen();
}
