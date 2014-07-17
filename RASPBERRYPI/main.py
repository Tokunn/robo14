#!/usr/bin/env python2

###     DEMAEROBOT PROGRAM
###     2014 OyNCT Robocon Aterm Tsushin
###     Designed On 2014.Jul.15 By Tokunn
###     Update On 2014.Jul.15 By Tokunn make

import os
import sys
import time
import math
import serial
import datetime
import subprocess

sys.path.append( 'Include' )
import get_gamepad
import send_udp_command
import send_serial_command


class LogicoolGamepad_int( get_gamepad.LogicoolGamepad ):
    def rounds( self, raw_Axiss ):
        self.__handred_Axis = raw_Axiss * 10
        self.__round_Axiss = int(round( self.__handred_Axis ))
        return self.__round_Axiss

class RecordCommand():
    pass

class MakeCommand():
    def __init__( self, com_id ):
        self.__command = [ com_id, 'S', 0, 'S', 0 ]
        self.__speedsValues = [ 0, 0 ]
        self.__VALUE_MAX = 9
        self.__LEFT_VALUE = 2
        self.__RIGT_VALUE = 4
        self.SPEED_VALUE = 0
        self.STEERING_VALUE = 1

    def set( self, speed_id, speed ):
        self.__speedsValues[ speed_id ] = speed

    def get( self ):
        self.__convertAngleToRote()
        self.__fixOverflow()
        self.__convertToString()
        return self.__joined_command

    def __convertAngleToRote( self ):
        self.__speedsValues[ self.SPEED_VALUE ] =  int( round( self.__speedsValues[ self.SPEED_VALUE ] * 0.9 ) )
        self.__speedsValues[ self.STEERING_VALUE ] =  int( round( self.__speedsValues[ self.STEERING_VALUE ] * 0.3 ) )

        self.__command[ self.__LEFT_VALUE ] =  self.__speedsValues[ self.SPEED_VALUE ] + self.__speedsValues[ self.STEERING_VALUE ]
        self.__command[ self.__RIGT_VALUE ] =  self.__speedsValues[ self.SPEED_VALUE ] - self.__speedsValues[ self.STEERING_VALUE ]

    def __fixOverflow( self ):
        if ( self.__command[ self.__LEFT_VALUE ] > self.__VALUE_MAX ):
            self.__command[ self.__RIGT_VALUE ] -= self.__command[ self.__LEFT_VALUE ] - self.__VALUE_MAX
        elif ( self.__command[ self.__LEFT_VALUE ] < -self.__VALUE_MAX ):
            self.__command[ self.__RIGT_VALUE ] -= self.__command[ self.__LEFT_VALUE ] + self.__VALUE_MAX

        if ( self.__command[ self.__RIGT_VALUE ] > self.__VALUE_MAX ):
            self.__command[ self.__LEFT_VALUE ] -= self.__command[ self.__RIGT_VALUE ] - self.__VALUE_MAX
        elif ( self.__command[ self.__RIGT_VALUE ] < -self.__VALUE_MAX ):
            self.__command[ self.__LEFT_VALUE ] -= self.__command[ self.__RIGT_VALUE ] + self.__VALUE_MAX

        for i in [ self.__LEFT_VALUE, self.__RIGT_VALUE ]:
            if ( self.__command[ i ] > 0 ):
                self.__command[ i - 1 ] = 'F'
            elif ( self.__command[ i ] < 0 ):
                self.__command[ i - 1 ] = 'B'
            else:
                self.__command[ i - 1 ] = 'S'

            self.__command[ i ] = math.fabs( self.__command[ i ] )
            if ( self.__command[ i ] > self.__VALUE_MAX ):
                self.__command[ i ] = self.__VALUE_MAX

    def __convertToString( self ):
        self.__command[ self.__LEFT_VALUE ] = str( int( self.__command[ self.__LEFT_VALUE ] ) )
        self.__command[ self.__RIGT_VALUE ] = str( int( self.__command[ self.__RIGT_VALUE ] ) )
        self.__joined_command = ''.join(self.__command)


def main():
    F710 = LogicoolGamepad_int()
    Command = MakeCommand( '$' )

    while True:
        F710.update()
        Command.set( Command.SPEED_VALUE, F710.left_Axis_Y )
        Command.set( Command.STEERING_VALUE, F710.left_Axis_X )
        print( '\t'*4 + Command.get() )
        time.sleep( 0.05 )

if __name__ == '__main__':
    try:
        main()
    except get_gamepad.GamepadError:
        print("\nGamepadDevice not found !!")
    except KeyboardInterrupt:
        print("\nexit")
