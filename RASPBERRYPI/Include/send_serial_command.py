#!/usr/bin/env python2

### This program is made for DEMAEROBOT and UKETORIROBOT by Tokunn
### 2014 OyNCT Robocon Ateam Tsushin
### H26 Jul. 15

import serial

class Send_Serial():
    def __init__(self, dev):
        self.__dev = dev
        self.__usb_serial = serial.Serial(self.__dev, 9600)

    def send(self, command):
        print(command)
        self.__usb_serial.write(command)
def main():
    dev = '/dev/ttyACM0'
    SERIAL = Send_Serial(dev)
    while True:
        command = "$f3s0"
        SERIAL.send(command)

if __name__ == '__main__':
    try:
        main()
    except KeyboardInterrupt:
        print("\n")
        quit
