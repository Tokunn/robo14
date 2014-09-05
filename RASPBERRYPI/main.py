#!/usr/bin/env python2

###     DEMAEROBOT PROGRAM
###     2014 OyNCT Robocon Aterm Tsushin
###     Designed On 2014.Jul.15 By Tokunn
###     Update On 2014.Jul.15 By Tokunn make

import time
import sys

sys.path.append( 'Include' )
import get_gamepad
import send_udp_command
import send_serial_command
import make_command
import record_string


def main():
    ip_add = '172.16.14.200'
    port = 4000

    F710 = get_gamepad.LogicoolGamepad_int()
    Command_tire = make_command.MakeCommand( '$' )
    Command_cata = make_command.MakeCommand( '%' )
    Command_button = make_command.MakeCommand_button( '&' )
    UDP = send_udp_command.Send_UDP( ip_add, port )

    while True:
        F710.update()

        if ( F710.rigt_Axis_Y == 0 and F710.rigt_Axis_X == 0 ):
            Command_tire.set( Command_tire.VALUE_SPEED, F710.left_Axis_Y )          # Set Tire Value
            Command_tire.set( Command_tire.VALUE_STEERING, F710.left_Axis_X )

            UDP.send( Command_tire.get() )
        else:
            Command_cata.set( Command_cata.VALUE_SPEED, F710.rigt_Axis_Y )
            Command_cata.set( Command_cata.VALUE_STEERING, F710.rigt_Axis_X )
            UDP.send( Command_cata.get() )

        if ( F710.Button_A or F710.Button_B ):
            Command_button.set( Command_button.VALUE_BUTTON_A, F710.Button_A )
            Command_button.set( Command_button.VALUE_BUTTON_B, F710.Button_B )
            UDP.send( Command_button.get() )

        time.sleep( 0.03 )

if __name__ == '__main__':
    while True:
        try:
            main()
        except get_gamepad.GamepadError:
            print("\nGamepadDevice not found !!")
            sys.exit(0)
        except KeyboardInterrupt:
            print("\nexit")
            sys.exit(0)
        except socket.error:
            print("socket.error")
