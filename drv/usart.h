#ifndef _USART_H
#define _USART_H

#define USART_FIFO_SIZE 64

#include <stddef.h>
#include <stdint.h>

void usart_init(void);

void usart_putc(char c);
void usart_getc(char *c);

void usart_puts(const char *s);
void usart_gets(char *s, size_t count);

size_t usart_read(uint8_t *buf, size_t count);
void usart_write(const uint8_t *buf, size_t count);

#endif
