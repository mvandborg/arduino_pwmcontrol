# -*- coding: utf-8 -*-
"""
Created on Tue Sep 13 12:56:57 2022

@author: madshv

This program is used to write commands to the Arduino temperature controller for 2 piezo stages.
The piezo stages requires a voltage from 0-5 V, and each piezo stage has 3 axes, meaning that
3 separate voltages must be supplied to each stage. In total 6 voltages to the 2 stages must
be controlled.

This program is an example of how to write a command to the Arduino from the a computer
using serial usb connection. The arduino has 6 PWM outputs with the following notation:

# Arduino pwm pins
# stage 1, X = pin D6
# stage 1, Y = pin D5
# stage 1, Z = pin D9
# stage 2, X = pin D10
# stage 2, Y = pin D11
# stage 2, Z = pin D3

To make the program work.
1) Change the COM port such that it matches with the used USB port.
2) Set the duty cycle to an number in the range 0-1, linearly corresponding to a voltage of 0-5 V.
3) Set the stage to ether 1 or 2
4) Set the direction to either 'X', 'Y' or 'Z'

"""


import serial
import io

# Function used for serial reading.
def read_buf(Ser):
    return Ser.read(Ser.inWaiting())

# Function used for sending a duty cycle command to the Arduino
# Ser: Serial object.
# stage_no: 1 or 2
# direction: 'X', 'Y' or 'Z'
# duty cycle: Number between 0-1.

def write_duty(Ser,stage_no,direction,duty_cycle):
    pwm_byte = duty_cycle*255   # Calculate duty cycle as number between 0-255
    msg = direction+stage_no+str(int(pwm_byte)) # Code the message to the Arduino
    msg = msg.encode('ascii')
    Ser.write(msg)  # Serial write the message

# Establish serial connection
port = 'COM8'   # CHANGE TO APPROPRIATE PORT

#### DO NOT CHANGE THE FOLLOWING #############
ser = serial.Serial()
ser.port = port
ser.baudrate = 115200   # Must match with the Arduino serial baudrate.
ser.timeout = 1

if ser.is_open == False:
    ser.open()
##############################################

# Example of how to write to Arduino
duty_cycle = 0.5
stage = '2'
direction = 'Z'
write_duty(ser,stage,direction,duty_cycle)
