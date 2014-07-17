#!/usr/bin/env python2


### This program is made for UKETORIROBOT by Tokunn
### 2014 OyNCT Robocon Ateam Tsushin
### H26 Jul. 5


import time
import math
import serial
import subprocess
import get_gamepad


#arduino_port = '/dev/ttyACM0'
arduino_port = '/dev/ttyUSB0'


class Serial_write():

    def __init__(self):
        self.arduino = serial.Serial(arduino_port, 9600)


    def serial_update(self, F710):
        self.serial_command = ['$', 'f', '0', 'n', '0', 's', '0', 'n', '0', '0', '0', '0']

        self.make_serial_direction(F710, "tire")
        self.make_serial_direction(F710, "catarpillar")
        self.make_serial_level(F710)
        self.make_serial_openclose(F710)
        self.make_serial_turn(F710)


    def make_serial_direction(self, F710, ti_or_ca):
        command_number = []
        Axis_left_or_rigt = ''

        if (ti_or_ca == "tire"):
            command_number = [1, 3]
            Axis_left_or_rigt = [F710.left_Axis_Y, F710.left_Axis_X]
        elif (ti_or_ca == "catarpillar"):
            command_number = [5, 7]
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
        self.serial_command[2] = str(int(math.fabs(round(F710.left_Axis_Y * 10))))
        self.serial_command[4] = str(int(math.fabs(round(F710.left_Axis_X * 10))))
        self.serial_command[6] = str(int(math.fabs(round(F710.rigt_Axis_Y * 10))))
        self.serial_command[8] = str(int(math.fabs(round(F710.rigt_Axis_X * 10))))

        for i in [2, 4, 6, 8]:
            if self.serial_command[i] == '10':
                self.serial_command[i] = '9'
                

    def make_serial_openclose(self, F710):
        if (F710.Button_X):
            self.serial_command[9] = '1'
        else:
            self.serial_command[9] = '0'


    def make_serial_turn(self, F710):
        if (F710.Hat_X == 1):
            self.serial_command[10] = 'r'
        elif (F710.Hat_X == -1):
            self.serial_command[10] = 'l'
        else:
            self.serial_command[10] = 'n'


    def send_serial(self):
        self.serial_command = ''.join(self.serial_command)
        self.arduino.write(self.serial_command)
        print("\t\t\t\t\t{0}".format(self.serial_command))


def main():

    Arduino = Serial_write()
    F710 = get_gamepad.LogicoolGamepad()

    while True:
        F710.update()

        Arduino.serial_update(F710)
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

    except KeyboardInterrupt:
        print("\nexit")
        quit
