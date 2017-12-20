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
QRCodePrinter(en_code).printQR()
sock.listen(5)

try:
    sock, addr = sock.accept()
    print("{}:{} is connecting...".format(*addr))
    data = sock.recv(bufsiz)

    print("Data '{}' is received".format(data))

    print("KR(16byte): {}".format(data[:16]))
    print("PK(113byte): {}".format(data[16:]))

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
    inpath = inpath.strip(" ")  # trim the path
    if os.path.exists(inpath):
        encrypted_path = os.path.basename(inpath) + ".encrypted"
        pipe = os.popen("./sms4 -e K.b2 {} {}".format(inpath, encrypted_path))
        print pipe.read()
    else:
        print inpath, "does not exist!!!"
    os.remove("K.b2")  # delete the temporary key file
finally:
    sock.close()
