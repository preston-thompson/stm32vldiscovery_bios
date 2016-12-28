import serial
import struct
import sys

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

def gpio_set_pin(pin, state):
    global ser
    cmd = b'\x02\x00'
    cmd += bytes(pin[0], "utf-8")
    cmd += bytes([pin[1]])
    cmd += bytes([state])
    ser.write(cmd)

def gpio_get_pin(pin):
    global ser
    cmd = b'\x03\x00'
    cmd += bytes(pin[0], "utf-8")
    cmd += bytes([pin[1]])
    ser.write(cmd)
    return struct.unpack("<B", ser.read(1))[0]

def gpio_setup_output_pin(pin, mode, speed):
    global ser
    cmd = b'\x01\x00'
    cmd += bytes(pin[0], "utf-8")
    cmd += bytes([pin[1], mode, speed])
    ser.write(cmd)

def init(path):
    global ser
    ser = serial.Serial(path, 115200)
