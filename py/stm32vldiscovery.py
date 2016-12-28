import serial
import struct
import sys

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

def init(path):
    global ser
    ser = serial.Serial(path, 115200)
