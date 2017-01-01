#ifndef _PWM_H
#define _PWM_H

void pwm_init(void);
void pwm_enable_channel(int timer, int channel);
void pwm_enable_timer(int timer, uint16_t period);
void pwm_set_channel_duty_cycle(int timer, int channel, uint16_t reset);

#endif
