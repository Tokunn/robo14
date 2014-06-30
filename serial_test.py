#!/usr/bin/env python2

import time
import serial


def main():
    arduino = serial.Serial('/dev/ttyACM0', 9600)

    while True:
        for i in ['s0n0s0n0', 'f3r8b6l2', 'b8l3s0n0']:
            arduino.write(i)
            print(arduino.read())
        time.sleep(0.1)


if __name__ == '__main__':
    main()
