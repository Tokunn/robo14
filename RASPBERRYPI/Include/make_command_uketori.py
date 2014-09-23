###     DEMAEROBOT PROGRAM
###     2014 OyNCT Robocon Aterm Tsushin
###     Designed On 2014.Jul.18 By Tokunn
###     Update On 2014.Aug.18 By Tokunn add MakeCommand_button

import time
import math


class MakeCommand_button():

    def __init__( self, com_id ):
        self.__command = [ com_id, '0', '0', '0' ]      # [ com_id, A, B, HAT ]
        self.VALUE_BUTTON_A = 1
        self.VALUE_BUTTON_B = 2
        self.VALUE_HAT = 3

    def set( self, button_id, value ):
        self.__command[ button_id ] = value

    def get( self ):
        self.__convertHatValue()
        self.__convertToString()
        return self.__joined_command

    def __convertHatValue( self ):
        if ( self.__command[ self.VALUE_HAT ] == -1 ):
            self.__command[ self.VALUE_HAT ] = 2

    def __convertToString( self ):
        self.__command[ self.VALUE_BUTTON_A ] = str( self.__command[ self.VALUE_BUTTON_A ] )
        self.__command[ self.VALUE_BUTTON_B ] = str( self.__command[ self.VALUE_BUTTON_B ] )
        self.__command[ self.VALUE_HAT ] = str( self.__command[ self.VALUE_HAT ] )
        self.__joined_command = ''.join(self.__command)


class MakeCommandTurn():
    def __init__( self, com_id ):
        self.__command = [ com_id, 'S', 0, 'S', 0, 'S', 0, 'S', 0 ]     # [ com_id, LF, LR, RF, RR ]
        self.__speedsValues = 0
        self.__VALUE_LEFT_FRONT = 2
        self.__VALUE_LEFT_REAR = 4
        self.__VALUE_RIGT_FRONT = 6
        self.__VALUE_RIGT_REAR = 8

    def set( self, value ):
        self.__speedsValues = value

    def get( self ):
        if ( self.__speedsValues > 0 ):
            self.__command[ self.__VALUE_LEFT_FRONT ] = 1
            self.__command[ self.__VALUE_LEFT_REAR ] = 1
            self.__command[ self.__VALUE_RIGT_FRONT ] = -1
            self.__command[ self.__VALUE_RIGT_REAR ] = -1
        else:
            self.__command[ self.__VALUE_LEFT_FRONT ] = -1
            self.__command[ self.__VALUE_LEFT_REAR ] = -1
            self.__command[ self.__VALUE_RIGT_FRONT ] = 1
            self.__command[ self.__VALUE_RIGT_REAR ] = 1

        for i in range( 2, 9, 2 ):
            self.__command[ i ] *= abs( self.__speedsValues )
            self.__command[ i ] *= 0.9

        self.__setString()
        self.__convertToString()

        return self.__joined_command

    def __setString( self ):
        for i in range( 2, 9, 2 ):
            if ( self.__command[ i ] > 0 ):
                self.__command[ i -1 ] = 'F'
            elif ( self.__command[ i ] < 0 ):
                self.__command[ i - 1 ] = 'B'
            else:
                self.__command[ i - 1 ] = 'S'

            self.__command[ i ] = abs( self.__command[ i ] )

    def __convertToString( self ):
        self.__command[ self.__VALUE_LEFT_FRONT ] = str( int( self.__command[ self.__VALUE_LEFT_FRONT ] ) )
        self.__command[ self.__VALUE_LEFT_REAR ] = str( int( self.__command[ self.__VALUE_LEFT_REAR ] ) )
        self.__command[ self.__VALUE_RIGT_FRONT ] = str( int( self.__command[ self.__VALUE_RIGT_FRONT ] ) )
        self.__command[ self.__VALUE_RIGT_REAR ] = str( int( self.__command[ self.__VALUE_RIGT_REAR ] ) )
        self.__joined_command = ''.join(self.__command)


class MakeCommand():
    def __init__( self, com_id ):
        self.__com_id = com_id
        self.__command = [ self.__com_id, 'S', 0, 'S', 0, 'S', 0, 'S', 0 ]
        self.__speedsValues = [ 0, 0, 0 ]
        self.__VALUE_MAX = 9
        self.__VALUE_LEFT_FRONT = 2
        self.__VALUE_LEFT_REAR = 4
        self.__VALUE_RIGT_FRONT = 6
        self.__VALUE_RIGT_REAR = 8
        self.VALUE_SPEED = 0
        self.VALUE_STEERING = 1
        self.VALUE_BDASH = 2

    def set( self, speed_id, speed ):
        self.__speedsValues[ speed_id ] = speed

    def get( self ):
        if ( self.__speedsValues[ self.VALUE_SPEED ] or self.__speedsValues[ self.VALUE_STEERING ] ):
            self.__makeAngle()
            self.__makeVariable()
            self.__setVariable()
        else:
            self.__noAction()
        self.__setSpeedLevel()
        self.__setString()
        self.__fixOverflow()
        self.__convertToString()
        return self.__joined_command

    def __clear( self ):
        self.__command = [ self.__com_id, 'S', 0, 'S', 0, 'S', 0, 'S', 0 ]
        self.__speedsValues = [ 0, 0, 0 ]

    def __makeAngle( self ):
        self.__rawAngle = math.atan2( self.__speedsValues[ self.VALUE_SPEED ], self.__speedsValues[ self.VALUE_STEERING ] )
        self.__angle = self.__rawAngle = ( self.__rawAngle * 180 ) / ( math.atan2(1, 1) * 4 )     # Convert Rad to Deg
        #print( self.__angle )
        if ( self.__angle > 90 ) and ( self.__angle < 180 ):    # 2
            self.__angle = 180 - self.__angle
        elif ( self.__angle < 0 ) and ( self.__angle > -90 ):
            self.__angle = 90 + self.__angle
        elif ( self.__angle < -90 ) and ( self.__angle > -180 ):
            self.__angle = -90 - self.__angle

    def __makeVariable( self ):
        self.__variable = -1 + self.__angle / 45 

    def __setVariable( self ):
        if ( self.__rawAngle > 0 ) and ( self.__rawAngle < 90 ):
            self.__command[ self.__VALUE_LEFT_FRONT ] = 1
            self.__command[ self.__VALUE_LEFT_REAR ] = self.__variable
            self.__command[ self.__VALUE_RIGT_FRONT ] = self.__variable
            self.__command[ self.__VALUE_RIGT_REAR ] = 1

        elif ( self.__rawAngle > 90 ) and ( self.__rawAngle < 180 ):
            self.__command[ self.__VALUE_LEFT_FRONT ] = self.__variable
            self.__command[ self.__VALUE_LEFT_REAR ] = 1
            self.__command[ self.__VALUE_RIGT_FRONT ] = 1
            self.__command[ self.__VALUE_RIGT_REAR ] = self.__variable

        elif ( self.__rawAngle < 0 ) and ( self.__rawAngle > -90 ):
            self.__command[ self.__VALUE_LEFT_FRONT ] = self.__variable
            self.__command[ self.__VALUE_LEFT_REAR ] = -1
            self.__command[ self.__VALUE_RIGT_FRONT ] = -1
            self.__command[ self.__VALUE_RIGT_REAR ] = self.__variable

        elif ( self.__rawAngle > -180 ) and ( self.__rawAngle < -90 ):
            self.__command[ self.__VALUE_LEFT_FRONT ] = -1
            self.__command[ self.__VALUE_LEFT_REAR ] = self.__variable
            self.__command[ self.__VALUE_RIGT_FRONT ] = self.__variable
            self.__command[ self.__VALUE_RIGT_REAR ] = -1

        elif ( self.__rawAngle == 0 ):
            self.__command[ self.__VALUE_LEFT_FRONT ] = 1
            self.__command[ self.__VALUE_LEFT_REAR ] = -1
            self.__command[ self.__VALUE_RIGT_FRONT ] = -1
            self.__command[ self.__VALUE_RIGT_REAR ] = 1

        elif ( self.__rawAngle == 90 ):
            self.__command[ self.__VALUE_LEFT_FRONT ] = 1
            self.__command[ self.__VALUE_LEFT_REAR ] = 1
            self.__command[ self.__VALUE_RIGT_FRONT ] = 1
            self.__command[ self.__VALUE_RIGT_REAR ] = 1

        elif ( self.__rawAngle == 180 ):
            self.__command[ self.__VALUE_LEFT_FRONT ] = -1
            self.__command[ self.__VALUE_LEFT_REAR ] = 1
            self.__command[ self.__VALUE_RIGT_FRONT ] = 1
            self.__command[ self.__VALUE_RIGT_REAR ] = -1

        elif ( self.__rawAngle == -90 ):
            self.__command[ self.__VALUE_LEFT_FRONT ] = -1
            self.__command[ self.__VALUE_LEFT_REAR ] = -1
            self.__command[ self.__VALUE_RIGT_FRONT ] = -1
            self.__command[ self.__VALUE_RIGT_REAR ] = -1

        self.__command[ self.__VALUE_LEFT_FRONT ] =   self.__command[ self.__VALUE_LEFT_FRONT ] 
        self.__command[ self.__VALUE_LEFT_REAR ] =    self.__command[ self.__VALUE_LEFT_REAR ] 
        self.__command[ self.__VALUE_RIGT_FRONT ] =   self.__command[ self.__VALUE_RIGT_FRONT ] 
        self.__command[ self.__VALUE_RIGT_REAR ] =    self.__command[ self.__VALUE_RIGT_REAR ] 
        #print( self.__angle )

        #print( str( self.__command[ self.__VALUE_LEFT_FRONT ] ) + "\t" +  str( self.__command[ self.__VALUE_LEFT_REAR ] ) + "\t" +  str( self.__command[ self.__VALUE_RIGT_FRONT ] ) + "\t" + str( self.__command[ self.__VALUE_RIGT_REAR ] ) )

    def __noAction( self ):
        self.__command[ self.__VALUE_LEFT_FRONT - 1 ] = 'S'
        self.__command[ self.__VALUE_LEFT_REAR -1 ] = 'S'
        self.__command[ self.__VALUE_RIGT_FRONT - 1 ] = 'S'
        self.__command[ self.__VALUE_RIGT_REAR - 1 ] = 'S'

        self.__command[ self.__VALUE_LEFT_FRONT ] = 0
        self.__command[ self.__VALUE_LEFT_REAR ] = 0
        self.__command[ self.__VALUE_RIGT_FRONT ] = 0
        self.__command[ self.__VALUE_RIGT_REAR ] = 0

    def __setSpeedLevel( self ):
        self.__lenght = math.sqrt( ( self.__speedsValues[ self.VALUE_SPEED ] * self.__speedsValues[ self.VALUE_SPEED ] ) + ( self.__speedsValues[ self.VALUE_STEERING ] * self.__speedsValues[ self.VALUE_STEERING ] ) )
        self.__lenght = int( round( self.__lenght ) )

        self.__command[ self.__VALUE_LEFT_FRONT ] *= self.__lenght
        self.__command[ self.__VALUE_LEFT_REAR ] *= self.__lenght
        self.__command[ self.__VALUE_RIGT_FRONT ] *= self.__lenght
        self.__command[ self.__VALUE_RIGT_REAR ] *= self.__lenght

    def __setString( self ):
        for i in range( 2, 9, 2 ):
            if ( self.__command[ i ] > 0 ):
                self.__command[ i -1 ] = 'F'
            elif ( self.__command[ i ] < 0 ):
                self.__command[ i - 1 ] = 'B'
            else:
                self.__command[ i - 1 ] = 'S'

            self.__command[ i ] = abs( self.__command[ i ] )

    def __fixOverflow( self ):
        if ( self.__speedsValues[ self.VALUE_SPEED ] or self.__speedsValues[ self.VALUE_STEERING ] ):
            if ( self.__rawAngle != 0 and self.__rawAngle != 90 and self.__rawAngle != 180 and self.__rawAngle != -90 ):
                for i in range( 2, 9, 2 ):
                    self.__command[ i ] = self.__command[ i ] * 4 / 13
            else:
                for i in range( 2, 9, 2 ):
                    self.__command[ i ] *= 0.4

    def __convertToString( self ):
        self.__command[ self.__VALUE_LEFT_FRONT ] = str( int( self.__command[ self.__VALUE_LEFT_FRONT ] ) )
        self.__command[ self.__VALUE_LEFT_REAR ] = str( int( self.__command[ self.__VALUE_LEFT_REAR ] ) )
        self.__command[ self.__VALUE_RIGT_FRONT ] = str( int( self.__command[ self.__VALUE_RIGT_FRONT ] ) )
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
