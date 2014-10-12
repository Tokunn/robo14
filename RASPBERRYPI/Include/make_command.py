###     DEMAEROBOT PROGRAM
###     2014 OyNCT Robocon Aterm Tsushin
###     Designed On 2014.Jul.18 By Tokunn
###     Update On 2014.Aug.18 By Tokunn add MakeCommand_button

import time
import math


class MakeCommand_button():
    def __init__( self, com_id ):
        self.__command = [ com_id, '0', '0', '0', '0' ]  #[ com_id, MANUAL, AUTO, FRONT, REAR ]
        self.VALUE_MODE_MANUAL = 1
        self.VALUE_MODE_AUTO = 2
        self.VALUE_FRONT = 3
        self.VALUE_REAR = 4

    def set( self, button_id, value ):
        self.__command[ button_id ] = value

    def get( self ):
        self.__convertToString()
        return self.__joined_command

    def __convertToString( self ):
        self.__command[ self.VALUE_MODE_MANUAL ] = str( self.__command[ self.VALUE_MODE_MANUAL ] )
        self.__command[ self.VALUE_MODE_AUTO   ] = str( self.__command[ self.VALUE_MODE_AUTO   ] )
        self.__command[ self.VALUE_FRONT ] = str( self.__command[ self.VALUE_FRONT ] )
        self.__command[ self.VALUE_REAR ] = str( self.__command[ self.VALUE_REAR ] )
        self.__joined_command = ''.join(self.__command)


class MakeCommand():
    def __init__( self, com_id ):
        self.__command = [ com_id, 'S', 0, 'S', 0, 'S', 0, 'S', 0 ]
        self.__speedsValues = [ 0, 0, 0 ]   # set F710.* ( Speed, Steering, Bdash )
        self.__VALUE_MAX = 9
        self.__VALUE_LEFT = 2
        self.__VALUE_LEFT_REAR = 4
        self.__VALUE_RIGT = 6
        self.__VALUE_RIGT_REAR = 8
        self.VALUE_SPEED = 0
        self.VALUE_STEERING = 1
        self.VALUE_BDASH = 2

    def set( self, speed_id, speed ):
        self.__speedsValues[ speed_id ] = speed

    def get( self ):
        self.__convertAngleToRote()
        self.__fixOverflow()
        self.__4commandConvert()
        self.__convertToString()
        return self.__joined_command

    def __convertAngleToRote( self ):
        # Bdash check
        if (self.__speedsValues[ self.VALUE_BDASH ]):   # In B Dash Mode
            bdash_lenght = 0.9
        else:   # Not In B Dash Mode
            bdash_lenght = 0.5

        self.__speedsValues[ self.VALUE_SPEED ] =  int( round( self.__speedsValues[ self.VALUE_SPEED ] * bdash_lenght ) )
        self.__speedsValues[ self.VALUE_STEERING ] =  int( round( self.__speedsValues[ self.VALUE_STEERING ] * bdash_lenght) )

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
        self.__command[ self.__VALUE_LEFT_REAR ] = str( int( self.__command[ self.__VALUE_LEFT_REAR ] ) )
        self.__command[ self.__VALUE_RIGT_REAR ] = str( int( self.__command[ self.__VALUE_RIGT_REAR ] ) )
        self.__joined_command = ''.join(self.__command)

    def __4commandConvert( self ):
        self.__command[ self.__VALUE_LEFT_REAR ] = self.__command[ self.__VALUE_LEFT ]
        self.__command[ self.__VALUE_RIGT_REAR ] = self.__command[ self.__VALUE_RIGT ]
        self.__command[ self.__VALUE_LEFT_REAR - 1 ] = self.__command[ self.__VALUE_LEFT - 1 ]
        self.__command[ self.__VALUE_RIGT_REAR - 1 ] = self.__command[ self.__VALUE_RIGT - 1 ]


def main():
    F710 = get_gamepad.LogicoolGamepad_int()
    Command = MakeCommand( '$' )
    Command_button = MakeCommand_button( '&' )

    while True:
        F710.update()
        Command.set( Command.VALUE_SPEED, F710.left_Axis_Y )
        Command.set( Command.VALUE_STEERING, F710.left_Axis_X )
        print( '\t'*4 + Command.get() )

        Command_button.set( Command_button.VALUE_BUTTON_A, F710.Button_A )
        Command_button.set( Command_button.VALUE_BUTTON_B, F710.Button_B )
        print( '\t'*6 + Command_button.get() )
        time.sleep( 0.01 )

if __name__ == '__main__':
    import get_gamepad

    try:
        main()
    except get_gamepad.GamepadError:
        print("\nGamepadDevice not found !!")
    except KeyboardInterrupt:
        print("\nexit")
