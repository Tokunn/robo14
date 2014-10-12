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
#import send_serial_command
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
        if ( F710.left_Axis_Y == 0 and F710.left_Axis_X == 0 ):     # Doesn't use cata
            Command_tire.set( Command_tire.VALUE_SPEED, F710.rigt_Axis_Y )          # Set Tire Value
            Command_tire.set( Command_tire.VALUE_STEERING, F710.rigt_Axis_X )
            BDash_Hat = F710.Hat_X + F710.Hat_Y
            Command_tire.set( Command_tire.VALUE_BDASH, BDash_Hat )      # B Dash
            UDP.send( Command_tire.get() )
        else:   # Use cata
            Command_cata.set( Command_cata.VALUE_SPEED, F710.left_Axis_Y )
            Command_cata.set( Command_cata.VALUE_STEERING, F710.left_Axis_X )
            BDash_Hat = F710.Hat_X + F710.Hat_Y
            Command_cata.set( Command_cata.VALUE_BDASH, BDash_Hat )
            UDP.send( Command_cata.get() )

        Command_button.set( Command_button.VALUE_MODE_MANUAL, F710.Button_Strt )
        Command_button.set( Command_button.VALUE_MODE_AUTO  , F710.Button_Back )
        Command_button.set( Command_button.VALUE_FRONT, F710.Button_Y )
        Command_button.set( Command_button.VALUE_REAR, F710.Button_X )
	time.sleep( 0.01 )
        UDP.send( Command_button.get() )

        #time.sleep( 0.04 )
	time.sleep( 0.06 )

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
        except send_udp_command.socket.error:
            print("socket.error")
            time.sleep(2)
