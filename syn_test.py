#!/usr/bin/env python2


import time
import serial


arduino = serial.Serial('/dev/ttyACM0', 9600)
while True:
    chunck = ['', '', '']
    chunck[0] = arduino.read()
    if chunck[0] == 'S':
        for i in [1, 2]:
            chunck[i] = arduino.read()
            print(chunck)
    time.sleep(0.1)
