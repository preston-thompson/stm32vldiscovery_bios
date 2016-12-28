#include <stdint.h>
#include <stddef.h>

#include "rpc.h"
#include "drv/usart.h"
#include "drv/gpio.h"

#define RPC_GPIO_SETUP_INPUT_PIN        0x0000
#define RPC_GPIO_SETUP_OUTPUT_PIN       0x0001
#define RPC_GPIO_SET_PIN                0x0002
#define RPC_GPIO_GET_PIN                0x0003

void rpc_listen(void) {

    uint16_t code;

    while (1) {

        // Wait for an RPC function code to come in.
        while (usart_in_waiting() < 2);

        usart_read(&code, sizeof(code));

        if (code == RPC_GPIO_SETUP_INPUT_PIN) {
            struct gpio_pin pin;
            uint8_t mode;
            size_t argsize = sizeof(pin) + sizeof(mode);
            while (usart_in_waiting() < argsize);
            usart_read(&pin.port, sizeof(pin.port));
            usart_read(&pin.pin, sizeof(pin.pin));
            usart_read(&mode, sizeof(mode));
            gpio_setup_input_pin(pin, mode);

        } else if (code == RPC_GPIO_SETUP_OUTPUT_PIN) {
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

        } else if (code == RPC_GPIO_SET_PIN) {
            struct gpio_pin pin;
            uint8_t state;
            size_t argsize = sizeof(pin) + sizeof(state);
            while (usart_in_waiting() < argsize);
            usart_read(&pin.port, sizeof(pin.port));
            usart_read(&pin.pin, sizeof(pin.pin));
            usart_read(&state, sizeof(state));
            gpio_set_pin(pin, state);

        } else if (code == RPC_GPIO_GET_PIN) {
            struct gpio_pin pin;
            size_t argsize = sizeof(pin);
            uint8_t state;
            while (usart_in_waiting() < argsize);
            usart_read(&pin.port, sizeof(pin.port));
            usart_read(&pin.pin, sizeof(pin.pin));
            state = gpio_get_pin(pin);
            usart_write(&state, sizeof(state));

        }
    }
}
