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

static void flash_program(uint8_t page, size_t offs, uint16_t word) {

    // Put the flash controller into programming mode.
    *flash_cr |= REG_FLASH_CR_PG_MASK;

    // Write the half word to the flash.
    *((volatile uint16_t *)(FLASH_START_ADDR + page * FLASH_PAGE_SIZE + offs)) = word;

    // Wait until the flash is done writing.
    while (*flash_sr & REG_FLASH_SR_BSY_MASK);

    // Disable programming mode on the flash controller.
    *flash_cr &= ~REG_FLASH_CR_PG_MASK;

}

static void flash_erase(uint8_t page) {

    // Put the flash controller into erase mode.
    *flash_cr |= REG_FLASH_CR_PER_MASK;

    // Choose the address to erase.
    *flash_ar = FLASH_START_ADDR + page * FLASH_PAGE_SIZE;

    // Start the erasure process.
    *flash_cr |= REG_FLASH_CR_STRT_MASK;

    // Wait until the flash is done erasing.
    while (*flash_sr & REG_FLASH_SR_BSY_MASK);

    // Disable erase mode on the flash controller.
    *flash_cr &= ~REG_FLASH_CR_PER_MASK;

}

void flash_init(void) {

    flash_unlock();

}

void flash_read(uint8_t *dst, uint8_t page, size_t offs, size_t num) {

    for (size_t i = 0; i < num; i++)
        *dst++ = *((volatile uint8_t *)(FLASH_START_ADDR + page * FLASH_PAGE_SIZE + offs));

}

void flash_write(uint8_t page, const uint8_t *src, size_t num) {

    for (uint8_t i = 0; i <= num / FLASH_PAGE_SIZE; i++)
        flash_erase(page + i);

    for (size_t i = 0; i < num; i += 2, src += 2)
        flash_program(page, i, *src + (*(src + 1) << 8));

}
