# -*- coding: utf-8 -*-
"""
Created on Tue Sep 13 12:56:57 2022

@author: madshv
"""

import serial
import io

# Arduino pwm pins
# stage 1, X = pin D6
# stage 1, Y = pin D5
# stage 1, Z = pin D9
# stage 2, X = pin D10
# stage 2, Y = pin D11
# stage 2, Z = pin D3

def read_buf(Ser):
    return Ser.read(Ser.inWaiting())

def write_duty(Ser,stage_no,direction,duty_cycle):
    # voltage: 0-5 V
    # direction: 'X', 'Y' or 'Z'
    # stage_no: '1' or '2'
    
    pwm_byte = duty_cycle*255
    msg = direction+stage_no+str(int(pwm_byte))
    msg = msg.encode('ascii')
    Ser.write(msg)

# Establish serial connection
port = 'COM8'

ser = serial.Serial()
ser.port = port
ser.baudrate = 115200
ser.timeout = 1

if ser.is_open == False:
    ser.open()

# Example of how to write to Arduino
duty_cycle = 0.5
stage = '2'
direction = 'Z'
write_duty(ser,stage,direction,duty_cycle)
