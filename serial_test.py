#!/usr/bin/env python2

import time
import serial


def main(arduino):


    while True:
        for i in ['s0n0s0n0', 'f3r8b6l2', 'b8l3s0n0']:
            arduino.write(i)
            print(arduino.read())
        time.sleep(0.1)


def read_serial(arduino):
    while True:
        chunck = ['']
        chunck[0] = arduino.read()
        if chunck[0] == 'S' or 'A':
            return chunck


if __name__ == '__main__':
    arduino = serial.Serial('/dev/ttyACM0', 9600)

    while True:
        chunck = read_serial(arduino)
        print("Read SYN")
        print(chunck)
        if chunck == ['S']:
            while True:
                print("Write SYN/ACK")
                arduino.write('O')

                print("Read ACK")
                chunck2 = read_serial(arduino)
                if chunck2 == ['A']:
                    main(arduino)
                print(chunck2)

                time.sleep(0.1)
