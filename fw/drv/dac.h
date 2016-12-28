#ifndef _DAC_H
#define _DAC_H

#include <stdint.h>

void dac_enable_channel(int channel);
void dac_set_output(int channel, uint16_t level);

#endif
