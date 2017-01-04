# stm32vldiscovery_fw
A prototyping tool based on the STM32VLDISCOVERY evaluation board.

## How is this used?
A Python library in the `py/` directory exposes the functionality of some of the peripherals of the STM32VLDISCOVERY board.
The board must be hooked up to the host PC through UART using 115200N1 settings. An example Python script to flash the
green LED (GPIO port C, pin 9):

```python
import time

import stm32vldiscovery

green_led = ('C', 9)

stm32vldiscovery.init('/dev/ttyAMA0')

stm32vldiscovery.gpio_setup_output_pin(
    green_led,
    stm32vldiscovery.GPIO_OUTPUT_MODE_PIO_PUSH_PULL,
    stm32vldiscovery.GPIO_OUTPUT_SPEED_2MHZ
)

while True:
    state = stm32vldiscovery.gpio_get_pin(green_led)
    stm32vldiscovery.gpio_set_pin(green_led, not state)
    time.sleep(0.1)
```

Documentation for the drivers can be found in `stm32vldiscovery.py` and in the drivers themselves under `drv/`.

## How does this work?
The peripheral drivers' interfaces are wrapped in `fw/rpc.c` and each driver function call is assigned a 2 byte code. To call
one of the drivers' functions, the function code is sent over the UART and then the function arguments are sent over the UART.
