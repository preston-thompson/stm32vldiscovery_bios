#include "rtc.h"
#include "registerset.h"

static volatile uint32_t * const rcc_apb1enr =
    (volatile uint32_t *)(REG_RCC_ADDR + REG_RCC_APB1ENR_OFFS);

static volatile uint32_t * const rtc_cntl =
    (volatile uint32_t *)(REG_RTC_ADDR + REG_RTC_CNTL_OFFS);
static volatile uint32_t * const rtc_cnth =
    (volatile uint32_t *)(REG_RTC_ADDR + REG_RTC_CNTH_OFFS);
static volatile uint32_t * const rtc_crh =
    (volatile uint32_t *)(REG_RTC_ADDR + REG_RTC_CRH_OFFS);
static volatile uint32_t * const rtc_crl =
    (volatile uint32_t *)(REG_RTC_ADDR + REG_RTC_CRL_OFFS);
static volatile uint32_t * const rtc_prll =
    (volatile uint32_t *)(REG_RTC_ADDR + REG_RTC_PRLL_OFFS);
static volatile uint32_t * const rtc_prlh =
    (volatile uint32_t *)(REG_RTC_ADDR + REG_RTC_PRLH_OFFS);

static volatile uint32_t * const pwr_cr =
    (volatile uint32_t *)(REG_PWR_ADDR + REG_PWR_CR_OFFS);

static void rtc_enter_configuration_mode(void) {
    *rcc_apb1enr |= REG_RCC_APB1ENR_PWREN_MASK;
    *pwr_cr |= REG_PWR_CR_DBP_MASK;
    while (!(*rtc_crl & REG_RTC_CRL_RTOFF_MASK));
    *rtc_crl |= REG_RTC_CRL_CNF_MASK;
}

static void rtc_exit_configuration_mode(void) {
    *rtc_crl &= ~REG_RTC_CRL_CNF_MASK;
    while (!(*rtc_crl & REG_RTC_CRL_RTOFF_MASK));
    *pwr_cr &= ~REG_PWR_CR_DBP_MASK;
}

void rtc_set_prescaler(uint32_t prescaler) {
    rtc_enter_configuration_mode();
    *rtc_prll = prescaler & 0xFFFF;
    *rtc_prlh = prescaler >> 16;
    rtc_exit_configuration_mode();
}

void rtc_set_count(uint32_t count) {
    rtc_enter_configuration_mode();
    *rtc_cntl = count & 0xFFFF;
    *rtc_cnth = count >> 16;
    rtc_exit_configuration_mode();
}

uint32_t rtc_get_time(void) {
    return ((*rtc_cnth) << 16) + *rtc_cntl;
}
