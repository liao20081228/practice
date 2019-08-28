#!/usr/bin/python3
from multiprocessing import Process
import time
import socket
import os

def see(port):
    server=socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    host=socket.gethostname()
    server.bind((host,port))
    server.listen(5)
    while True:
        clientsocket,addr=server.accept()
        print("client address is : " % str(addr) )
        clientsocket.close()


if __name__=='__main__':
    port = 5000
    p_list=[]
    while port<= 5005 :
        p=Process(target=see, args=(port,))
        p_list.append(p)
        p.start()
        port=port+1

