###     DEMAEROBOT PROGRAM
###     2014 OyNCT Robocon Aterm Tsushin
###     Designed On 2014.Jul.18 By Tokunn
###     Update On 2014.Jul.15 By Tokunn make

import time
import math


class MakeCommand():
    def __init__( self, com_id ):
        self.__command = [ com_id, 'S', 0, 'S', 0 ]
        self.__speedsValues = [ 0, 0 ]
        self.__VALUE_MAX = 9
        self.__VALUE_LEFT = 2
        self.__VALUE_RIGT = 4
        self.VALUE_SPEED = 0
        self.VALUE_STEERING = 1

    def set( self, speed_id, speed ):
        self.__speedsValues[ speed_id ] = speed

    def get( self ):
        self.__convertAngleToRote()
        self.__fixOverflow()
        self.__convertToString()
        return self.__joined_command

    def __convertAngleToRote( self ):
        self.__speedsValues[ self.VALUE_SPEED ] =  int( round( self.__speedsValues[ self.VALUE_SPEED ] * 0.9 ) )
        self.__speedsValues[ self.VALUE_STEERING ] =  int( round( self.__speedsValues[ self.VALUE_STEERING ] * 0.3 ) )

        self.__command[ self.__VALUE_LEFT ] =  self.__speedsValues[ self.VALUE_SPEED ] + self.__speedsValues[ self.VALUE_STEERING ]
        self.__command[ self.__VALUE_RIGT ] =  self.__speedsValues[ self.VALUE_SPEED ] - self.__speedsValues[ self.VALUE_STEERING ]

    def __fixOverflow( self ):
        if ( self.__command[ self.__VALUE_LEFT ] > self.__VALUE_MAX ):
            self.__command[ self.__VALUE_RIGT ] -= self.__command[ self.__VALUE_LEFT ] - self.__VALUE_MAX
        elif ( self.__command[ self.__VALUE_LEFT ] < -self.__VALUE_MAX ):
            self.__command[ self.__VALUE_RIGT ] -= self.__command[ self.__VALUE_LEFT ] + self.__VALUE_MAX

        if ( self.__command[ self.__VALUE_RIGT ] > self.__VALUE_MAX ):
            self.__command[ self.__VALUE_LEFT ] -= self.__command[ self.__VALUE_RIGT ] - self.__VALUE_MAX
        elif ( self.__command[ self.__VALUE_RIGT ] < -self.__VALUE_MAX ):
            self.__command[ self.__VALUE_LEFT ] -= self.__command[ self.__VALUE_RIGT ] + self.__VALUE_MAX

        for i in [ self.__VALUE_LEFT, self.__VALUE_RIGT ]:
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
        self.__command[ self.__VALUE_LEFT ] = str( int( self.__command[ self.__VALUE_LEFT ] ) )
        self.__command[ self.__VALUE_RIGT ] = str( int( self.__command[ self.__VALUE_RIGT ] ) )
        self.__joined_command = ''.join(self.__command)


def main():
    F710 = get_gamepad.LogicoolGamepad_int()
    Command = MakeCommand( '$' )

    while True:
        F710.update()
        Command.set( Command.VALUE_SPEED, F710.left_Axis_Y )
        Command.set( Command.VALUE_STEERING, F710.left_Axis_X )
        print( '\t'*4 + Command.get() )
        time.sleep( 0.05 )

if __name__ == '__main__':
    import get_gamepad

    try:
        main()
    except get_gamepad.GamepadError:
        print("\nGamepadDevice not found !!")
    except KeyboardInterrupt:
        print("\nexit")
