###     UKETORI PROGRAM
###     2014 OyNCT Robocon Aterm Tsushin
###     Designed On 2014.Jul.22 By Komei
###     Update On 2014.Jul.22 By Tokunn make

import make_command


class MakeCommandMecanum( make_command.MakeCommand ):
    pass


def main():
    F710 = get_gamepad.LogicoolGamepad_int()
    Command = MakeCommandMecanum( '$' )

    while True:
        F710.update()
        time.sleep( 0.05 )

if __name__ == '__main__':
    import get_gamepad

    try:
        main()
    except get_gamepad.GamepadError:
        print("\nGamepadDevice not found !!")
    except KeyboardInterrupt:
        print("\nexit")
