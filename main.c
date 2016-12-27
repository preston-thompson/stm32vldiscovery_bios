#include <stdint.h>
#include "str.h"
#include "drv/gpio.h"
#include "drv/usart.h"
#include "drv/flash.h"
#include "drv/rtc.h"
#include "drv/interrupt.h"

void main(void) {
    char buf[32];
    uint32_t flash_test = 0xdeadbeef;

    gpio_init();
    usart_init();
    flash_init();

    rtc_set_prescaler(0x7fff);
    rtc_set_count(0);

    struct gpio_pin blue_led = {'C', 8};
    gpio_setup_output_pin(blue_led, GPIO_OUTPUT_MODE_GPIO_PUSH_PULL, GPIO_OUTPUT_SPEED_2MHZ);

    interrupt_enable();

    usart_puts("\r\nstm32vldiscovery_os boot\r\ngit version: ");
    usart_puts(GIT_VERSION);
    usart_puts("\r\n");

    str_hex(buf, &flash_test, sizeof(uint32_t));
    usart_puts(buf);
    usart_puts("\r\n");

    flash_write(63, (uint8_t*)(&flash_test), sizeof(flash_test));

    flash_test = rtc_get_time();
    while (1) {
        while (rtc_get_time() == flash_test);
        flash_test = rtc_get_time();
        str_hex(buf, &flash_test, sizeof(uint32_t));
        usart_puts(buf);
        usart_puts("\r\n");
    }

    /*
    while (1) {
        gpio_set_pin(blue_led, !gpio_get_pin(blue_led));
        usart_gets(buf, sizeof(buf));
        usart_puts(buf);
        usart_puts("\r\n");
    }
    */
}
