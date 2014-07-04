#!/usr/bin/env python2

import time
import math
import serial
import subprocess
import get_gamepad


arduino_port = '/dev/ttyACM0'


class Serial_write():

    def __init__(self):
        self.arduino = serial.Serial(arduino_port, 9600)

    def make_serial(self):
        self.serial_command = "$s0n0s0n00"

    def send_serial(self):
        self.arduino.write(self.serial_command)
        print("\t\t\t\t\t{0}".format(self.serial_command))


def main():

    Arduino = Serial_write()

    while True:
        Arduino.make_serial()
        Arduino.send_serial()

        time.sleep(5)


if __name__ == '__main__':
    try:
        main()

    except KeyboardInterrupt:
        print("\nexit")
        quit
