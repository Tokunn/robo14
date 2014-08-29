#!/usr/bin/env python2

### This program is made for DEMAEROBOT and UKETORIROBOT by Tokunn
### 2014 OyNCT Robocon Ateam Tsushin
### H26 Jul. 15

import socket

class Send_UDP():
    def __init__( self, ip_add, port ):
        self.host = ip_add
        self.port = port
        self.sock = socket.socket( socket.AF_INET, socket.SOCK_DGRAM )

    def send( self, command ):
        print( '\t'*4 + command )
        self.sock.sendto( command, ( self.host, self.port ) )

def main():
    ip_add = '127.16.14.227'
    port = 4000
    UDP = Send_UDP( ip_add, port )
    while True:
        command = "$f3s0"
        UDP.send( command )
        time.sleep( 0.1 )

if __name__ == '__main__':
    import time

    try:
        main()
    except KeyboardInterrupt:
        print("\n")
        quit
