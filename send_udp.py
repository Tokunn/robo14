#!/usr/bin/env python2

### This program is made for DEMAEROBOT and UKETORIROBOT by Tokunn
### 2014 OyNCT Robocon Ateam Tsushin
### H26 Jul. 15

from __future__ import print_function
import time
import socket
from contextlib import closing

class Send_UDP():

    def __init__(self, ip_add, port):
        self.host = ip_add
        self.port = port
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

    def send_command(self, command):
        print(command)
        self.sock.sendto(command, (self.host, self.port))

if __name__ == '__main__':
    ip_add = "127.0.0.1"
    port = 4000
    UDP = Send_UDP(ip_add, port)

    while True:
        udp_command = "$f3s0"
        UDP.send_command(udp_command)
        time.sleep(0.05)
