#ifndef _FLASH_H
#define _FLASH_H

#include <stddef.h>

void flash_init(void);
void flash_read(uint8_t *dst, uint8_t page, size_t offs, size_t num);
void flash_write(uint8_t page, const uint8_t *src, size_t num);

#endif
