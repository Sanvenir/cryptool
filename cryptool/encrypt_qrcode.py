#!/usr/bin/python
# -*- coding: utf-8 -*-

import socket
import os
from config import rnd
from qrCodePrinter import QRCodePrinter

bufsiz = 129
sock = socket.socket()
host = socket.gethostname()
port = 10028

# print host, port

sock.bind((socket.gethostbyname(host), port))

hostaddr, port = sock.getsockname()

en_code = "4|{}:{}|0|{}".format(hostaddr, port, rnd)

print("String to Qrcode: '{}'".format(en_code))
QRCodePrinter(en_code)
sock.listen(5)

try:
    sock, addr = sock.accept()
    print("{}:{} is connecting...".format(*addr))
    data = sock.recv(bufsiz)
finally:
    sock.close()

with open("PK.b2", "wb") as f:
    f.write(data[16:])

kr_list = map(ord, data[:16])

key = ""
for i in range(16):
    rnd_ch = int(rnd[2 * i:2 * i + 2], 16)
    key += chr(rnd_ch ^ kr_list[i])

with open("K.b2", "wb") as f:
    f.write(key)

# choose the file
inpath = raw_input("\nPlease input the file you want to encrypted: ")
inpath = inpath.strip(" ").strip("'").strip('"')  # trim the path
if os.path.exists(inpath):
    encrypted_path = inpath + ".encrypted"
    print("output: ", encrypted_path)
    pipe = os.system("Project1.exe -e K.b2 {} {}".format(inpath, encrypted_path))
    if os.path.exists(encrypted_path):
        os.remove(inpath)
    # print pipe.read()
else:
    print inpath, "does not exist!!!"
os.remove("K.b2")  # delete the temporary key file
