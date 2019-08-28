import socket
i=3000
while i < 3056:
    s=socket.socket(socket.AF_INET,socket.SOCK_STREAM)
    s.connect(("117.156.51.102",i))
    s.close()
    i=i + 500

