#ifndef _GPIO_H
#define _GPIO_H

enum gpio_pin_mode {
    GPIO_INPUT_MODE_ANALOG = 0,
    GPIO_INPUT_MODE_FLOATING,
    GPIO_INPUT_MODE_PULL,

    GPIO_OUTPUT_MODE_GPIO_PUSH_PULL = 0,
    GPIO_OUTPUT_MODE_GPIO_OPEN_DRAIN,
    GPIO_OUTPUT_MODE_AF_PUSH_PULL,
    GPIO_OUTPUT_MODE_AF_OPEN_DRAIN,
};

enum gpio_pin_speed {
    GPIO_OUTPUT_SPEED_10MHZ = 1,
    GPIO_OUTPUT_SPEED_2MHZ,
    GPIO_OUTPUT_SPEED_50MHZ,
};

struct gpio_pin {
    char port;
    uint8_t pin;
};

void gpio_init(void);
void gpio_setup_input_pin(struct gpio_pin pin, enum gpio_pin_mode mode);
void gpio_setup_output_pin(struct gpio_pin pin, enum gpio_pin_mode mode, enum gpio_pin_speed speed);
void gpio_set_pin(struct gpio_pin, int state);
int gpio_get_pin(struct gpio_pin);

#endif
