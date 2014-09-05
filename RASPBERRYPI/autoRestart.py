#!/usr/bin/env python2

###     AUTORUN SCRIPT
###     2014 OyNCT Robocon Aterm Tsushin
###     Designed On 2014.Sce.5 By Tokunn
###     Update On 2014.Sce.5 By Tokunn make

import time
import subprocess


if __name__ == '__main__':
    while True:
        try:
            subprocess.call( './main.py' )
        except:
            pass
