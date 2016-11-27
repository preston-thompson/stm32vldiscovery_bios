#ifndef _FLASH_H
#define _FLASH_H

#include <stddef.h>

void flash_init(void);
void flash_read(uint8_t *buf, size_t count, uint32_t addr);
void flash_write(const uint8_t *buf, size_t count, uint32_t addr);

#endif
