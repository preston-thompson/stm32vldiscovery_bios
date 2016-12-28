#ifndef _USART_H
#define _USART_H

#include <stddef.h>

void usart_init(void);
size_t usart_read(void *dst, size_t count);
size_t usart_in_waiting(void);
void usart_write(const void *src, size_t count);

#endif
