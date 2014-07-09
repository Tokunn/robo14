#!/usr/bin/env python2


### This program is made for DEMAEROBOT by Tokunn
### 2014 OyNCT Robocon Ateam TsuShin
### H26 Jul. 7


import os
import time
import math
import serial
import datetime
import subprocess
import get_gamepad


#arduino_port = '/dev/ttyACM0'
arduino_port = '/dev/ttyUSB0'
gamepad_assignment = ['X', 'A', 'B', 'RB', 'LB']    # Type [Y A B X LB RB LT RT]
                                                    # [Front, Rea, All, Record_Start, Record_Stop]


class Serial_write():

    def __init__(self):
        self.arduino = serial.Serial(arduino_port, 9600)
        self.file_flag_onoff = False
        self.file_flag_written = True
        self.file_list = []


    def serial_update(self, F710):
        self.serial_command = ['$', 's', '0', 's', '0', '0', '0', '0']

        self.gamepad_assignment_value = {'Y':F710.Button_Y,
                                         'A':F710.Button_X,
                                         'B':F710.Button_B,
                                         'X':F710.Button_X,
                                         'LB':F710.left_Bumper,
                                         'RB':F710.rigt_Bumper,
                                         'LT':F710.left_Trigger,
                                         'RT':F710.rigt_Trigger}

        self.make_serial_direction(F710, "tire")
        self.make_serial_direction(F710, "cata")
        self.make_serial_level(F710)
        self.make_serial_updown(F710)
        
        self.check_file_onoff(F710)


    def make_serial_direction(self, F710, ti_or_ca):
        command_number = []
        Axis_tire_cata = ''

        if (ti_or_ca == "tire"):
            command_number = [1, 3]
            Axis_tire_cata = [F710.left_Axis_Y, F710.left_Axis_X]
        elif (ti_or_ca == "cata"):
            command_number = [5, 7]
            Axis_tire_cata = [F710.rigt_Axis_Y, F710.rigt_Axis_X]

        self.speed = int(round(Axis_tire_cata[0] * 10))
        self.curv = int(round(Axis_tire_cata[1] * 3))
        self.curv_left = self.speed + self.curv
        self.curv_rigt = self.speed - self.curv
        for curv in [[self.curv_left, self.curv_rigt], [self.curv_rigt, self.curv_left]]:
            if (curv[0] > 10):
                curv[1] += 10 - curv[0]
            elif (curv[0] < -10):
                curv[1] -= 10 + curv[0]
                


    def make_serial_level(self, F710):

        for i in [2, 4]:
            if self.serial_command[i] == '10':
                self.serial_command[i] = '9'
                

    def make_serial_updown(self, F710):

        if (self.gamepad_assignment_value[gamepad_assignment[0]]):
            self.serial_command[5] = '1'
        else:
            self.serial_command[5] = '0'

        if (self.gamepad_assignment_value[gamepad_assignment[1]]):
            self.serial_command[6] = '1'
        else:
            self.serial_command[6] = '0'

        if (self.gamepad_assignment_value[gamepad_assignment[2]]):
            self.serial_command[7] = '1'
        else:
            self.serial_command[7] = '0'




    def check_file_onoff(self, F710):
        if(self.gamepad_assignment_value[gamepad_assignment[3]]):
            self.file_flag_onoff = True
            self.file_flag_written = False

            today_file = datetime.datetime.today()
            self.file_name = os.path.join('RecordingData', today_file.strftime("%Y-%m-%d_%H:%M:%S"))

        elif(self.gamepad_assignment_value[gamepad_assignment[4]]):
            self.file_flag_onoff = False


    def send_serial(self):
        self.serial_command = ''.join(self.serial_command)
        self.arduino.write(self.serial_command)
        print("\t\t\t\t\t{0}".format(self.serial_command))


    def write_add_file(self):
        if(self.file_flag_onoff == True and self.file_flag_written == False):
            self.file_list.append(self.serial_command + '\n')
            print("Recording")

        elif(self.file_flag_onoff == False and self.file_flag_written == False):
            self.file_flag_written = True
            print("Recording Stop")

            f = open(self.file_name, 'w')
            f.writelines(self.file_list)
            f.close()

            self.file_list = []


def main():

    Arduino = Serial_write()
    F710 = get_gamepad.LogicoolGamepad()

    while True:
        F710.update()

        Arduino.serial_update(F710)
        Arduino.send_serial()
        Arduino.write_add_file()

        if (F710.Button_Back + F710.Button_Strt == 2):
            subprocess.call("sudo shutdown -h now".split())
            return 0

        time.sleep(0.1)


if __name__ == '__main__':
    try:
        main()

    except get_gamepad.GamepadError:
        print("\nGamepadDevice not found !!")

    except KeyboardInterrupt:
        print("\nexit")
