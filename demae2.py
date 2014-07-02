#!/usr/bin/env python2

import time
import math
import serial
import decimal
import subprocess
import get_gamepad
import RPi.GPIO as GPIO

debug = 1


class Serial_write():

    def __init__(self, port1):
        self.arduino1 = serial.Serial(port1, 9600)

        self.serial_command = ['s', 0, 'n', 0, 's', 0, 'n', 0]


    def make_serial_direction(self, F710, ti_or_ca):
        command_number = []
        Axis_left_or_rigt = ''

        if (ti_or_ca == "ti"):
            command_number = [0, 2]
            Axis_left_or_rigt = [F710.left_Axis_Y, F710.left_Axis_X]
        elif (ti_or_ca == "ca"):
            command_number = [4, 6]
            Axis_left_or_rigt = [F710.rigt_Axis_Y, F710.rigt_Axis_X]

        if (Axis_left_or_rigt[0] > 0):
            self.serial_command[command_number[0]] = 'f'
        elif (Axis_left_or_rigt[0] < 0):
            self.serial_command[command_number[0]] = 'b'
        else:
            self.serial_command[command_number[0]] = 's'

        if (Axis_left_or_rigt[1] > 0):
            self.serial_command[command_number[1]] = 'r'
        elif (Axis_left_or_rigt[1] < 0):
            self.serial_command[command_number[1]] = 'l'
        else:
            self.serial_command[command_number[1]] = 'n'


    def make_serial_level(self, F710):
        self.serial_command[1] = int(math.fabs(round(F710.left_Axis_Y * 10)))
        self.serial_command[3] = int(math.fabs(round(F710.left_Axis_X * 10)))
        self.serial_command[5] = int(math.fabs(round(F710.rigt_Axis_Y * 10)))
        self.serial_command[7] = int(math.fabs(round(F710.rigt_Axis_X * 10)))


    def send_serial(self):
        self.arduino1.write(self.serial_command)
        if (debug):
            self.debug_print()


    def debug_print(self):
        print(self.serial_command)



def main():
    F710 = get_gamepad.LogicoolGamepad()
    Arduino = Serial_write('/dev/ttyUSB0')

    while True:
        F710.update()

        if (F710.Button_X):
            pass

        Arduino.make_serial_direction(F710, "ti")
        Arduino.make_serial_direction(F710, "ca")
        Arduino.make_serial_level(F710)
        Arduino.send_serial()

        if (F710.Button_Back + F710.Button_Strt == 2):
            subprocess.call("sudo shutdown -h now".split())
            return 0

        time.sleep(0.05)



if __name__ == '__main__':
    try:
        main()

    except get_gamepad.GamepadError:
        print("\nGamepadDevice not found !!")
        print("Please connect GamepadDevice\n")

    except KeyboardInterrupt:
        print("\nexit")
        quit
