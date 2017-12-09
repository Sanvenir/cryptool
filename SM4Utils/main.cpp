//
//  main.cpp
//
//  Created by 刘嘉铭 on 2017/12/9.
//  Copyright © 2017年 Kalen Blue. All rights reserved.
//

#include <stdlib.h>
#include <stdio.h>
#include "sms4.hpp"

#define MAXLEN 1024*1024*2

//加密文件
void encrypt(const char* inpath, const char* outpath, BYTE* key) {
    FILE *infile, *outfile;
    BYTE inbuf[MAXLEN] = {0};  // 输入流
    BYTE outbuf[MAXLEN] = {0}; // 输出流

    infile = fopen(inpath, "rb"); // 要加密的文件
    outfile = fopen(outpath, "wb"); //加密后的文件

    int plain_length = fread(inbuf, sizeof(BYTE), MAXLEN, infile); //读取要加密的文件的大小
    int cipher_len; //加密后的大小

    SM4Encrypt(inbuf, plain_length, outbuf, cipher_len, key); //使用SM4加密
    fwrite(outbuf, cipher_len, sizeof(BYTE), outfile); // 写入文件
}

//解密文件
void decrypt(const char* inpath, const char* outpath, BYTE* key) {
    FILE *infile, *outfile;
    BYTE inbuf[MAXLEN] = {0};  // 输入流
    BYTE outbuf[MAXLEN] = {0}; // 输出流

    infile = fopen(inpath, "rb"); // 要解密的文件
    outfile = fopen(outpath, "wb"); //解密后的文件

    int cipher_length = fread(inbuf, sizeof(BYTE), MAXLEN, infile); //读取要解密的文件的大小
    int plain_len; //解密后的大小

    SM4Decrypt(inbuf, cipher_length, outbuf, plain_len, key); //使用SM4解密
    fwrite(outbuf, plain_len, sizeof(BYTE), outfile); // 写入文件
}

int main(int argc, const char * argv[]) {
    BYTE a[16] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
    BYTE *key=a;



    return 0;
}
