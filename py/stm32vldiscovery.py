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

def gpio_setup_input_pin(pin, mode):
    global ser
    cmd = b'\x00\x00'
    cmd += bytes(pin[0], "utf-8")
    cmd += bytes([pin[1], mode])
    ser.write(cmd)

def dac_enable_channel(channel):
    global ser
    cmd = b'\x00\x01'
    cmd += bytes([channel])
    ser.write(cmd)

def dac_set_output(channel, level):
    global ser
    cmd = b'\x01\x01'
    cmd += bytes([channel, level & 0xFF, level >> 8])
    ser.write(cmd)

def pwm_enable_channel(timer, channel):
    global ser
    cmd = b'\x00\x02'
    cmd += bytes([timer, channel])
    ser.write(cmd)

def pwm_enable_timer(timer, period):
    global ser
    cmd = b'\x01\x02'
    cmd += bytes([timer, period & 0xFF, period >> 8])
    ser.write(cmd)

def pwm_set_channel_duty_cycle(timer, channel, reset):
    global ser
    cmd = b'\x02\x02'
    cmd += bytes([timer, channel, reset & 0xFF, reset >> 8])
    ser.write(cmd)

def adc_enable_channel(channel):
    global ser
    cmd = b'\x00\x03'
    cmd += bytes([channel])
    ser.write(cmd)

def adc_sample(channel):
    global ser
    cmd = b'\x01\x03'
    cmd += bytes([channel])
    ser.write(cmd)
    return struct.unpack("<H", ser.read(2))[0]

def init(path):
    global ser
    ser = serial.Serial(path, 115200)
