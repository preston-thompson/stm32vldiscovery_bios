#include <stdint.h>
#include "drv/usart.h"
#include "drv/flash.h"
#include "drv/interrupt.h"

void main(void) {
    char buf[32];
    uint32_t flash_test = 0xdeadbeef;

    usart_init();
    flash_init();

    interrupt_enable();

    usart_puts("\r\nstm32vldiscovery_os boot\r\ngit version: ");
    usart_puts(GIT_VERSION);
    usart_puts("\r\n");

    flash_write(2, (uint8_t*)(&flash_test), sizeof(flash_test));

    while (1) {
        usart_gets(buf, sizeof(buf));
        usart_puts(buf);
        usart_puts("\r\n");
    }
}
