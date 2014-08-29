###     DEMAEROBOT PROGRAM
###     2014 OyNCT Robocon Aterm Tsushin
###     Designed On 2014.Jul.15 By Tokunn
###     Update On 2014.Jul.15 By Tokunn make

import os
import datetime


class RecordString():

    def __init__( self ):
        self.file_flag_onoff = False
        self.file_flag_written = True

    def record( self, onoff, command ):
        if( onoff ):
            self.file_flag_onoff = True
            self.file_flag_written = False
            self.file_list = []

        self.__write_add_file( command )

    def off( self ):
        self.file_flag_onoff = False

    def __write_add_file( self, command ):
        if( self.file_flag_onoff ):
            self.file_list.append( command + '\n' )
            print( "Recording" )

        elif( self.file_flag_onoff == False and self.file_flag_written == False ):
            today_file = datetime.datetime.today()
            f = open( os.path.join( 'RecordingData', today_file.strftime( "%Y-%m-%d_%H:%M:%S" ) ), 'w' )
            f.writelines( self.file_list )
            f.close()

            self.file_flag_written = True

def main():
    record = RecordString()
    F710 = get_gamepad.LogicoolGamepad()

    while ( True ):
        F710.update()
        record.record( F710.left_Bumper, "$S0S0" )
        if( F710.rigt_Bumper ):
            record.off()
        if( F710.Button_X ):
            record.off()
            break
        time.sleep(0.1)

if __name__ == '__main__':
    import time
    import sys

    sys.path.append( 'Include' )
    import get_gamepad

    try:
        main()
    except get_gamepad.GamepadError:
        print( "\nGamepadDevice not found !!" )
    except KeyboardInterrupt:
        print( "\nexit" )
