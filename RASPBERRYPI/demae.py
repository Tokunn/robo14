#!/usr/bin/env python2

###     DEMAEROBOT PROGRAM
###     2014 OyNCT Robocon Aterm Tsushin
###     Designed On 2014.Jul.15 By Tokunn
###     Update On 2014.Jul.15 By Tokunn make

import get_gamepad
import time
import math
import datetime
import os
import subprocess
import serial
import send_udp_command
import send_serial_command


class LogicoolGamepad_int( get_gamepad.LogicoolGamepad ):
    def rounds( self, raw_Axiss ):
        self.__handred_Axis = raw_Axis * 10
        self.__round_Axiss = int(round( self.__handred_Axis ))
        return self.__converted_Axiss

class RecordCommand():
    pass

class MakeCommand():
    def __init__( self, com_id ):
        self.__command = [ com_id, 'S', '0', 'S', '0' ]
        self.__speedsValues = [ 0, 0 ]
        self.__LEFT_VALUE = 2
        self.__RIGT_VALUE = 4
        self.SPEED_VALUE = 0
        self.STEERING_VALUE = 1

    def set( self, speed_id, speed ):
        self.__speedsValue[ speed_id ] = speed

    def get( self ):
        __convertToString ( self )
        return self.__command

    def __convertAngleToRote( self ):
        self.__speedsValue[ self.STEERING_VALUE ] *= 0.3
        self.__command[ self.__LEFT_VALUE ] = self.__speedsValue[ self.SPEED_VALUE ]
                                            + self.__speedsValue[ self.STEERING_VALUE ]
        self.__command[ self.__RIGT_VALUE ] = self.__speedsValue[ self.SPEED_VALUE ]
                                            - self.__speedsValue[ self.STEERING_VALUE ]

    def __convertToString( self ):
        self.__command = ''.join(self.__commnad)

