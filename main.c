#include <stdint.h>
#include "drv/usart.h"
#include "drv/flash.h"
#include "drv/interrupt.h"

void main(void) {
    char buf[32];
    uint8_t flash_test[4] = { 0xBE, 0xEF, 0xDE, 0xAD };

    usart_init();
    flash_init();

    interrupt_enable();

    usart_puts("stm32vldiscovery_os boot\r\n");

    flash_write(flash_test, sizeof(flash_test), 0x800);

    while (1) {
        usart_gets(buf, sizeof(buf));
        usart_puts(buf);
        usart_puts("\r\n");
    }
}
