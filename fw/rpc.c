#include <stdint.h>
#include <stddef.h>

#include "rpc.h"
#include "drv/usart.h"
#include "drv/gpio.h"
#include "drv/dac.h"
#include "drv/adc.h"
#include "drv/pwm.h"

#define RPC_GPIO_SETUP_INPUT_PIN        0x0000
#define RPC_GPIO_SETUP_OUTPUT_PIN       0x0001
#define RPC_GPIO_SET_PIN                0x0002
#define RPC_GPIO_GET_PIN                0x0003
#define RPC_DAC_ENABLE_CHANNEL          0x0100
#define RPC_DAC_SET_OUTPUT              0x0101
#define RPC_PWM_ENABLE_CHANNEL          0x0200
#define RPC_PWM_ENABLE_TIMER            0x0201
#define RPC_PWM_SET_CHANNEL_DUTY_CYCLE  0x0202
#define RPC_ADC_ENABLE_CHANNEL          0x0300
#define RPC_ADC_SAMPLE                  0x0301

void rpc_listen(void) {

    uint16_t code;

    while (1) {

        // Wait for an RPC function code to come in.
        while (usart_in_waiting() < 2);

        usart_read(&code, sizeof(code));

        if (code == RPC_GPIO_SETUP_INPUT_PIN)
            rpc_gpio_setup_input_pin();

        else if (code == RPC_GPIO_SETUP_OUTPUT_PIN)
            rpc_gpio_setup_output_pin();

        else if (code == RPC_GPIO_SET_PIN)
            rpc_gpio_set_pin();

        else if (code == RPC_GPIO_GET_PIN)
            rpc_gpio_get_pin();

        else if (code == RPC_DAC_ENABLE_CHANNEL)
            rpc_dac_enable_channel();

        else if (code == RPC_DAC_SET_OUTPUT)
            rpc_dac_set_output();

        else if (code == RPC_PWM_ENABLE_CHANNEL)
            rpc_pwm_enable_channel();

        else if (code == RPC_PWM_ENABLE_TIMER)
            rpc_pwm_enable_timer();

        else if (code == RPC_PWM_SET_CHANNEL_DUTY_CYCLE)
            rpc_pwm_set_channel_duty_cycle();

        else if (code == RPC_ADC_ENABLE_CHANNEL)
            rpc_adc_enable_channel();

        else if (code == RPC_ADC_SAMPLE)
            rpc_adc_sample();

    }

}

void rpc_gpio_setup_input_pin(void) {
    struct gpio_pin pin;
    uint8_t mode;
    size_t argsize = sizeof(pin) + sizeof(mode);
    while (usart_in_waiting() < argsize);
    usart_read(&pin.port, sizeof(pin.port));
    usart_read(&pin.pin, sizeof(pin.pin));
    usart_read(&mode, sizeof(mode));
    gpio_setup_input_pin(pin, mode);
}

void rpc_gpio_setup_output_pin(void) {
    struct gpio_pin pin;
    uint8_t mode;
    uint8_t speed;
    size_t argsize = sizeof(pin) + sizeof(mode) + sizeof(speed);
    while (usart_in_waiting() < argsize);
    usart_read(&pin.port, sizeof(pin.port));
    usart_read(&pin.pin, sizeof(pin.pin));
    usart_read(&mode, sizeof(mode));
    usart_read(&speed, sizeof(speed));
    gpio_setup_output_pin(pin, mode, speed);
}

void rpc_gpio_set_pin(void) {
    struct gpio_pin pin;
    uint8_t state;
    size_t argsize = sizeof(pin) + sizeof(state);
    while (usart_in_waiting() < argsize);
    usart_read(&pin.port, sizeof(pin.port));
    usart_read(&pin.pin, sizeof(pin.pin));
    usart_read(&state, sizeof(state));
    gpio_set_pin(pin, state);
}

void rpc_gpio_get_pin(void) {
    struct gpio_pin pin;
    size_t argsize = sizeof(pin);
    uint8_t state;
    while (usart_in_waiting() < argsize);
    usart_read(&pin.port, sizeof(pin.port));
    usart_read(&pin.pin, sizeof(pin.pin));
    state = gpio_get_pin(pin);
    usart_write(&state, sizeof(state));
}

void rpc_dac_enable_channel(void) {
    uint8_t channel;
    size_t argsize = sizeof(channel);
    while (usart_in_waiting() < argsize);
    usart_read(&channel, sizeof(channel));
    dac_enable_channel(channel);
}

void rpc_dac_set_output(void) {
    uint8_t channel;
    uint16_t level;
    size_t argsize = sizeof(channel) + sizeof(level);
    while (usart_in_waiting() < argsize);
    usart_read(&channel, sizeof(channel));
    usart_read(&level, sizeof(level));
    dac_set_output(channel, level);
}

void rpc_pwm_enable_channel(void) {
    uint8_t timer;
    uint8_t channel;
    size_t argsize = sizeof(timer) + sizeof(channel);
    while (usart_in_waiting() < argsize);
    usart_read(&timer, sizeof(timer));
    usart_read(&channel, sizeof(channel));
    pwm_enable_channel(timer, channel);
}

void rpc_pwm_enable_timer(void) {
    uint8_t timer;
    uint16_t period;
    size_t argsize = sizeof(timer) + sizeof(period);
    while (usart_in_waiting() < argsize);
    usart_read(&timer, sizeof(timer));
    usart_read(&period, sizeof(period));
    pwm_enable_timer(timer, period);
}

void rpc_pwm_set_channel_duty_cycle(void) {
    uint8_t timer;
    uint8_t channel;
    uint16_t reset;
    size_t argsize = sizeof(timer) + sizeof(channel) + sizeof(reset);
    while (usart_in_waiting() < argsize);
    usart_read(&timer, sizeof(timer));
    usart_read(&channel, sizeof(channel));
    usart_read(&reset, sizeof(reset));
    pwm_set_channel_duty_cycle(timer, channel, reset);
}

void rpc_adc_enable_channel(void) {
    uint8_t channel;
    size_t argsize = sizeof(channel);
    while (usart_in_waiting() < argsize);
    usart_read(&channel, sizeof(channel));
    adc_enable_channel(channel);
}

void rpc_adc_sample(void) {
    uint8_t channel;
    size_t argsize = sizeof(channel);
    uint16_t sample;
    while (usart_in_waiting() < argsize);
    usart_read(&channel, sizeof(channel));
    sample = adc_sample(channel);
    usart_write(&sample, sizeof(sample));
}
