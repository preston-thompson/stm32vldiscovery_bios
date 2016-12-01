#include <stddef.h>
#include <stdint.h>

#include "registerset.h"
#include "flash.h"

static volatile uint32_t * const flash_keyr =
    (volatile uint32_t *)(REG_FLASH_ADDR + REG_FLASH_KEYR_OFFS);
static volatile uint32_t * const flash_sr =
    (volatile uint32_t *)(REG_FLASH_ADDR + REG_FLASH_SR_OFFS);
static volatile uint32_t * const flash_cr =
    (volatile uint32_t *)(REG_FLASH_ADDR + REG_FLASH_CR_OFFS);
static volatile uint32_t * const flash_ar =
    (volatile uint32_t *)(REG_FLASH_ADDR + REG_FLASH_AR_OFFS);
static volatile uint32_t * const flash_obr =
    (volatile uint32_t *)(REG_FLASH_ADDR + REG_FLASH_OBR_OFFS);
static volatile uint32_t * const flash_wrpr =
    (volatile uint32_t *)(REG_FLASH_ADDR + REG_FLASH_WRPR_OFFS);

static void flash_unlock(void) {
    *flash_keyr = REG_FLASH_KEY1;
    *flash_keyr = REG_FLASH_KEY2;
}

static void flash_program(uint16_t halfword, uint32_t addr) {
    *flash_cr |= REG_FLASH_CR_PG_MASK;
    *((volatile uint16_t *)(REG_FLASH_MEM_ADDR + addr)) = halfword;
    while (*flash_sr & REG_FLASH_SR_BSY_MASK);
}

static void flash_erase(uint32_t addr) {
    *flash_cr |= REG_FLASH_CR_PER_MASK;
    *flash_ar = REG_FLASH_MEM_ADDR + addr;
    *flash_cr |= REG_FLASH_CR_STRT_MASK;
    while (*flash_sr & REG_FLASH_SR_BSY_MASK);
}

void flash_init(void) {
    flash_unlock();
}

void flash_read(uint8_t *buf, size_t count, uint32_t addr) {
}

void flash_write(const uint8_t *buf, size_t count, uint32_t addr) {
    const uint8_t *end = buf + count;
    uint16_t halfword;
    flash_erase(addr);
    while (buf < end) {
        halfword = *buf;
        halfword |= *(buf + 1) << 8;
        flash_program(halfword, addr);
        buf += 2;
    }
}
