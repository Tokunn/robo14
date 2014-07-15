#!/usr/bin/env python2

from __future__ import print_function
import socket
import time
from contextlib import closing

class Send_UDP(self):
    
    def __init__(self, ip_add):

        self.host = ip_add
        self.port = 4000
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

    def send_command(command):

        print(command)
        self.sock.sendto(command, (self.host, self.port))

def main1():
    host = '127.0.0.1'
    port = 4000
    count = 0
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    with closing(sock):
        while True:
            message = "Hello world : {0}".format(count).encode('utf-8')
            print(message)
            sock.sendto(message, (host, port))
            count += 1
            time.sleep(1)
        return

def main2():
    host = '127.0.0.1'
    port = 3794
    serversock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    print ('Type massage...')
    send_msg = raw_input()
    serversock.sendto(send_msg, (host, port))

if __name__ == '__main__':
    main1()
    #main2()
