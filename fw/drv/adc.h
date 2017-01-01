#ifndef _ADC_H
#define _ADC_H

#include <stdint.h>

void adc_init(void);
void adc_enable_channel(int channel);
uint16_t adc_sample(int channel);

#endif
