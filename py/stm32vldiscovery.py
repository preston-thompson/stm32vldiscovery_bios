import serial
import struct
import sys

# Constants for GPIO
GPIO_INPUT_MODE_ANALOG = 0
GPIO_INPUT_MODE_FLOATING = 1
GPIO_INPUT_MODE_PULL = 2

GPIO_OUTPUT_MODE_GPIO_PUSH_PULL = 0
GPIO_OUTPUT_MODE_GPIO_OPEN_DRAIN = 1
GPIO_OUTPUT_MODE_AF_PUSH_PULL = 2
GPIO_OUTPUT_MODE_AF_OPEN_DRAIN = 3

GPIO_OUTPUT_SPEED_10MHZ = 1
GPIO_OUTPUT_SPEED_2MHZ = 2
GPIO_OUTPUT_SPEED_50MHZ = 3

# gpio_set_pin - Set state of a GPIO pin.
#   Arguments:
#     pin - tuple containing pin: ('C', 3)
#     state - 1 or 0, True or False
def gpio_set_pin(pin, state):
    global ser
    cmd = b'\x02\x00'
    cmd += bytes(pin[0], "utf-8")
    cmd += bytes([pin[1]])
    cmd += bytes([state])
    ser.write(cmd)

# gpio_get_pin - Get the state of a GPIO pin.
#   Arguments:
#     pin - tuple containing pin: ('C', 3)
#   Returns:
#     1 or 0
def gpio_get_pin(pin):
    global ser
    cmd = b'\x03\x00'
    cmd += bytes(pin[0], "utf-8")
    cmd += bytes([pin[1]])
    ser.write(cmd)
    return struct.unpack("<B", ser.read(1))[0]

# gpio_setup_output_pin - Setup a GPIO pin as an output.
#   Arguments:
#     pin - tuple containing pin: ('C', 3)
#     mode - see constants above
#     speed - see constants above
def gpio_setup_output_pin(pin, mode, speed):
    global ser
    cmd = b'\x01\x00'
    cmd += bytes(pin[0], "utf-8")
    cmd += bytes([pin[1], mode, speed])
    ser.write(cmd)

# gpio_setup_input_pin - Setup a GPIO pin as an input.
#   Arguments:
#     pin - tuple containing pin: ('C', 3)
#     mode - see constants above
def gpio_setup_input_pin(pin, mode):
    global ser
    cmd = b'\x00\x00'
    cmd += bytes(pin[0], "utf-8")
    cmd += bytes([pin[1], mode])
    ser.write(cmd)

# dac_enable_channel - Enable a DAC channel.
#   Arguments:
#     channel - channel to enable
def dac_enable_channel(channel):
    global ser
    cmd = b'\x00\x01'
    cmd += bytes([channel])
    ser.write(cmd)

# dac_set_output - Set an output level on a DAC channel.
#   Arguments:
#     channel - channel to set (1 or 2)
#     level - level to set channel to (0 to 4095)
def dac_set_output(channel, level):
    global ser
    cmd = b'\x01\x01'
    cmd += bytes([channel, level & 0xFF, level >> 8])
    ser.write(cmd)

# pwm_enable_timer - Enable a PWM timer.
#   Arguments:
#     timer - which timer peripheral (2 through 5)
#     period - timer period (0 through 65535)
def pwm_enable_timer(timer, period):
    global ser
    cmd = b'\x01\x02'
    cmd += bytes([timer, period & 0xFF, period >> 8])
    ser.write(cmd)

# pwm_enable_channel - Enable a PWM channel.
#   Arguments:
#     timer - which timer peripheral (2 through 5)
#     channel - channel to enable (1 through 4)
def pwm_enable_channel(timer, channel):
    global ser
    cmd = b'\x00\x02'
    cmd += bytes([timer, channel])
    ser.write(cmd)

# pwm_set_channel_duty_cycle - Set duty cycle of a PWM channel.
#   Arguments:
#     timer - which timer peripheral (2 through 5)
#     channel - channel to configure (1 through 4)
#     reset - reset value (0 through 65535)
def pwm_set_channel_duty_cycle(timer, channel, reset):
    global ser
    cmd = b'\x02\x02'
    cmd += bytes([timer, channel, reset & 0xFF, reset >> 8])
    ser.write(cmd)

# adc_enable_channel - Enable an ADC channel.
#   Arguments:
#     channel - channel to enable (0 through 15)
def adc_enable_channel(channel):
    global ser
    cmd = b'\x00\x03'
    cmd += bytes([channel])
    ser.write(cmd)

# adc_sample - Sample an ADC channel.
#   Arguments:
#     channel - channel to sample (0 through 15)
#   Returns:
#     ADC sample value (0 through 4095)
def adc_sample(channel):
    global ser
    cmd = b'\x01\x03'
    cmd += bytes([channel])
    ser.write(cmd)
    return struct.unpack("<H", ser.read(2))[0]

def init(path):
    global ser
    ser = serial.Serial(path, 115200)
