#!/usr/bin/env python2


import time
import serial


def main():
    arduino = serial.Serial('/dev/ttyACM0', 9600)

    while True:
        for i in ['s0n0s0n00', 'f3r8b6120', 'b8l3s0n00']:
            arduino.write(i)
        time.sleep(0.1)


if __name__ == '__main__':
    main()
