#ifndef _RPC_H
#define _RPC_H

#include <stdint.h>
#include <stddef.h>

void rpc_listen(void);

void rpc_gpio_setup_input_pin(void);
void rpc_gpio_setup_output_pin(void);
void rpc_gpio_set_pin(void);
void rpc_gpio_get_pin(void);
void rpc_dac_enable_channel(void);
void rpc_dac_set_output(void);
void rpc_pwm_enable_channel(void);
void rpc_pwm_enable_timer(void);
void rpc_pwm_set_channel_duty_cycle(void);
void rpc_adc_enable_channel(void);
void rpc_adc_sample(void);

#endif
