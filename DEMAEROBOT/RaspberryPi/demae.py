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
import send_udp_command

#arduino_port = '/dev/ttyACM0'
#arduino_port = '/dev/ttyUSB0'

arduino_addr = '127.0.0.1'
arduino_port = 4000

gamepad_assignment = ['X', 'A', 'B', 'RB', 'LB']    # Type [Y A B X LB RB LT RT]

class Command_write():

    def __init__(self, terecom_type):
        self.file_flag_onoff = False
        self.file_flag_written = True
        self.file_list = []

        if (terecom_type == 'SERIAL'):
            self.arduino = serial.Serial(arduino_port, 9600)
        elif (terecom_type == 'NW'):
            self.arduino = Send_UDP(arduino_addr, arduino_port)

    def serial_update(self, F710):
        self.serial_command = ['$', 's', '0', 's', '0','s', '0', 's', '0', '0', '0', '0']

        self.gamepad_assignment_value = {'Y':F710.Button_Y,
                                         'A':F710.Button_A,
                                         'B':F710.Button_B,
                                         'X':F710.Button_X,
                                         'LB':F710.left_Bumper,
                                         'RB':F710.rigt_Bumper,
                                         'LT':F710.left_Trigger,
                                         'RT':F710.rigt_Trigger}

        self.make_serial_direction(F710, "tire")
        self.make_serial_direction(F710, "cata")
        self.make_serial_updown(F710)
        self.check_file_onoff(F710)

    def make_serial_direction(self, F710, ti_or_ca):
        com_num = []
        Axis_tire_cata = ''

        if (ti_or_ca == "tire"):
            com_num = [2, 4]
            Axis_tire_cata = [ F710.left_Axis_Y, F710.left_Axis_X ]
        if (ti_or_ca == "cata"):
            com_num = [6, 8]
            Axis_tire_cata = [ F710.rigt_Axis_Y, F710.rigt_Axis_X ]

        self.sped = int( round( Axis_tire_cata[0] * 10 ) )      # Speed
        self.curv = int( round( Axis_tire_cata[1] * 03 ) )      # CurvSpeed

        self.serial_command[ com_num[0] ] = self.sped + self.curv   #Left tire(cata)
        self.serial_command[ com_num[1] ] = self.sped - self.curv   #Right tire(cata)

        for com_num2 in [ [ com_num[0], com_num[1] ], [ com_num[1], com_num[0]] ]:  #fix overflow
            if (self.serial_command[ com_num2[0] ] > +10):
                self.serial_command[ com_num2[1] ] += 10 - self.serial_command[ com_num2[0] ]
                self.serial_command[ com_num2[0] ] = +10
            if (self.serial_command[ com_num2[0] ] < -10):
                self.serial_command[ com_num2[1] ] -= 10 + self.serial_command[ com_num2[0] ]
                self.serial_command[ com_num2[0] ] = -10

        for com_num3 in [ com_num[0], com_num[1] ]:
            if (self.serial_command[ com_num3 ] == 0):
                self.serial_command[ com_num3 - 1 ] = 's'
            if (self.serial_command[ com_num3 ] > 0):
                self.serial_command[ com_num3 - 1 ] = 'f'
            if (self.serial_command[ com_num3 ] < 0):
                self.serial_command[ com_num3 - 1 ] = 'b'
            self.serial_command[ com_num3 ] = math.fabs(self.serial_command[ com_num3 ])

            if (self.serial_command[ com_num3 ] == 10):
                self.serial_command[ com_num3 ] = 9

            self.serial_command[ com_num3 ] = str(int(self.serial_command[ com_num3 ]))

    def make_serial_updown(self, F710):
        if (self.gamepad_assignment_value[gamepad_assignment[0]]):
            self.serial_command[9] = '1'
        else:
            self.serial_command[9] = '0'

        if (self.gamepad_assignment_value[gamepad_assignment[1]]):
            self.serial_command[10] = '1'
        else:
            self.serial_command[10] = '0'

        if (self.gamepad_assignment_value[gamepad_assignment[2]]):
            self.serial_command[11] = '1'
        else:
            self.serial_command[11] = '0'

    def check_file_onoff(self, F710):
        if(self.gamepad_assignment_value[gamepad_assignment[3]]):
            self.file_flag_onoff = True
            self.file_flag_written = False

            today_file = datetime.datetime.today()
            self.file_name = os.path.join('RecordingData', today_file.strftime("%Y-%m-%d_%H:%M:%S"))

        elif(self.gamepad_assignment_value[gamepad_assignment[4]]):
            self.file_flag_onoff = False

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

    def send_serial(self):
        self.serial_command = ''.join(self.serial_command)
        self.arduino.write(self.serial_command)
        print("\t\t\t\t\t{0}".format(self.serial_command))

def main():
    Arduino = Command_write('NW')
    F710 = get_gamepad.LogicoolGamepad()

    while True:
        F710.update()
        Arduino.command_update(F710)
        Arduino.send_command()
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
