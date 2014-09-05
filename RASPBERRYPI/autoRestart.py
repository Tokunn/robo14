#!/usr/bin/env python2

###     AUTORUN SCRIPT
###     2014 OyNCT Robocon Aterm Tsushin
###     Designed On 2014.Sce.5 By Tokunn
###     Update On 2014.Sce.5 By Tokunn make

import os
import time
import subprocess

python_script = './main.py'
cwd = './'

def main():
    while True:
        try:
            p = subprocess.Popen(python_script, shell=True, cwd=cwd, stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.STDOUT, close_fds=True)
            (stdouterr, stdin) = (p.stdout, p.stdin)
            print( '-' * 80 )
            while True:
                line = stdouterr.readline()
                if not line:
                    break
                print line.rstrip()
            print( "Return code: {0}".format( p.wait() ) )
            print( '-' * 80 )
            print('')
        except:
            print("\nstop python_script")
        time.sleep(5)

if __name__ == '__main__':
    try:
        main()
    except KeyboardInterrupt:
        print("\nautoRestart Script exit")
