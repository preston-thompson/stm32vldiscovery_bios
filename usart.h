#ifndef _USART_H
#define _USART_H

#define USART_FIFO_SIZE 64

#include <stddef.h>

int usart_init(int slot);

void usart_putc(int slot, char c);
void usart_getc(int slot, char *c);

void usart_puts(int slot, const char *s);
void usart_gets(int slot, char *s, size_t count);

size_t usart_read(int slot, uint8_t *buf, size_t count);
void usart_write(int slot, const uint8_t *buf, size_t count);

#endif
