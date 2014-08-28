#!/usr/bin/env python2

from hello import LogicoolGamepad
from hello import LogicoolGamepad_int
from hello import GamepadError
import time

if __name__ == '__main__':
    try:
        F710 = LogicoolGamepad()
        while True:
            F710.update()
            F710.prints()
            time.sleep(0.05)
    except GamepadError:
        print("\nGamepadDevice not found !!")
        print("Please connect GamepadDevice\n")
        quit
    except KeyboardInterrupt:
        print("\nInput ctrl+C\nquit q(-_-)")
        quit
