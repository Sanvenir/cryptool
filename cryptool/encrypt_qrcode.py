#!/usr/bin/python
# -*- coding: utf-8 -*-

import ctypes
import os
import socket
import random
import qrcode
import sys

from qrCodePrinter import QRCodePrinter

# _file = 'libsms4.so'
# _path = os.path.join(*(os.path.split(__file__)[:-1] + (_file,)))
# _mod = ctypes.cdll.LoadLibrary(_path)
#
# _encrypt = _mod.SM4Encrypt
# _decrypt = _mod.SM4Decrypt
#
# _encrypt.argtypes = (
#     ctypes.POINTER(ctypes.c_uint8),
#     ctypes.c_int,
#     ctypes.POINTER(ctypes.c_uint8),
#     ctypes.POINTER(ctypes.c_int),
#     ctypes.POINTER(ctypes.c_uint8)
# )
#
#
# def encrypt(key):
#     assert isinstance(key, bytes)


bufsiz = 129
sock = socket.socket()
host = socket.gethostname()
port = 10028

# print host, port

sock.bind(("172.20.10.13", port))


hostaddr, port = sock.getsockname()


get_char = lambda num: chr(num + 48) if num < 10 else chr(num + 55)

en_code = "4|{}:{}|0|{}".format(hostaddr, port, ''.join([get_char(random.randrange(16)) for _ in range(32)]))

img = qrcode.make(en_code)
img.save("qrcode.png")

print(en_code)
print("String to Qrcode: '{}'".format(en_code))
QRCodePrinter(en_code).printQR()
sock.listen(5)

try:
    sock, addr = sock.accept()
    print("{}:{} is connecting...".format(*addr))
    data = sock.recv(bufsiz)
    print(type(data))

    print("Data {} is received".format(data))

    print("KR(16byte):", data[:16])
    print("PK(16byte):", data[16:])

    with open("KR.b2", "wb") as f:
        f.write(data[:16])

    with open("PK.b2", "wb") as f:
        f.write(data[16:])

    print ('LEN:', len(data))
finally:
    sock.close()
