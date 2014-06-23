#!/usr/bin/env python2

import time
import math
import serial
import decimal
import subprocess
import get_gamepad
#import RPi.GPIO as GPIO


debug = 1


class Serial_write():

    def __init__(self, port1, port2):
        self.arduino1 = serial.Serial(port1, 9600)
        self.arduino2 = serial.Serial(port2, 9600)

        self.serial_command = ['s', 0, 'n', 0]


    def make_serial_direction(self, F710):
        if (F710.left_Axis_Y > 0):
            self.serial_command[0] = 'f'
        elif (F710.left_Axis_Y < 0):
            self.serial_command[0] = 'b'
        else:
            self.serial_command[0] = 's'

        if (F710.left_Axis_X > 0):
            self.serial_command[2] = 'r'
        elif (F710.left_Axis_X < 0):
            self.serial_command[2] = 'l'
        else:
            self.serial_command[2] = 'n'


    def make_serial_level(self, F710):
        self.serial_command[1] = int(math.fabs(round(F710.left_Axis_Y * 10)))
        self.serial_command[3] = int(math.fabs(round(F710.left_Axis_X * 10)))


    def send_serial(self):
        self.arduino1.write(self.serial_command)
        self.arduino2.write(self.serial_command)
        if (debug):
            self.debug_print()


    def debug_print(self):
        print(self.serial_command)



class GPIO_write():
    
    def __init__(self, pin):
        self.pin = pin

        GPIO.setmode(GPIO.BCM)
        GPIO.setup(pin, GPIO.OUT)
        GPIO.output(self.pin, False)

    def send_GPIO(self):
        GPIO.output(self.pin, True)
        time.sleep(0.05)
        GPIO.output(self.pin, False)
        if (debug):
            self.debug_print()


    def debug_print(self):
        print(self.pin)



def main():
    F710 = get_gamepad.LogicoolGamepad()
    Arduino = Serial_write('/dev/ttyACM0', '/dev/ttyACM1')
    #GPIO_pin = GPIO_write(18)

    while True:
        F710.update()

        #if (F710.Button_X):
            #GPIO_pin.send_GPIO()

        Arduino.make_serial_direction(F710)
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
