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
    Command = make_command.MakeCommand( '$' )
    UDP = send_udp_command.Send_UDP( ip_add, port )

    while True:
        F710.update()

        Command.set( Command.VALUE_SPEED, F710.left_Axis_Y )
        Command.set( Command.VALUE_STEERING, F710.left_Axis_X )

        UDP.send( Command.get() )

        time.sleep( 0.05 )

if __name__ == '__main__':
    try:
        main()
    except get_gamepad.GamepadError:
        print("\nGamepadDevice not found !!")
    except KeyboardInterrupt:
        print("\nexit")
