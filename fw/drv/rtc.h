#ifndef _RTC_H
#define _RTC_H

#include <stdint.h>

void rtc_set_prescaler(uint32_t prescaler);
void rtc_set_count(uint32_t count);
uint32_t rtc_get_count(void);

#endif
