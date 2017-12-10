//
//  main.cpp
//
//  Created by 刘嘉铭 on 2017/12/9.
//  Copyright © 2017年 Kalen Blue. All rights reserved.
//
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "sms4.hpp"

#define MAXLEN 1024*1024*2
#define CHECK_FILE_EXSIT(file, filepath) if (NULL == file) { \
                            std::cout<<"please make sure "<<filepath<<" exist;"<<std::endl; \
                            return 0; \
                            }

//加密文件
int encrypt(const char* inpath, const char* outpath, BYTE* key) {
    FILE *infile, *outfile;
    BYTE inbuf[MAXLEN] = {0};  // 输入流
    BYTE outbuf[MAXLEN] = {0}; // 输出流

    infile = fopen(inpath, "rb"); // 要加密的文件
    outfile = fopen(outpath, "wb"); //加密后的文件

    // 检查文件是否存在
    CHECK_FILE_EXSIT(infile, inpath)
    CHECK_FILE_EXSIT(outfile, outpath)

    int plain_length = fread(inbuf, sizeof(BYTE), MAXLEN, infile); //读取要加密的文件的大小
    int cipher_len; //加密后的大小

    SM4Encrypt(inbuf, plain_length, outbuf, cipher_len, key); //使用SM4加密
    fwrite(outbuf, cipher_len, sizeof(BYTE), outfile); // 写入文件

    std::cout<<"Successfully encrypted "<<inpath<<"!"<<std::endl;
    return 1;
}

//解密文件
int decrypt(const char* inpath, const char* outpath, BYTE* key) {
    FILE *infile, *outfile;
    BYTE inbuf[MAXLEN] = {0};  // 输入流
    BYTE outbuf[MAXLEN] = {0}; // 输出流

    infile = fopen(inpath, "rb"); // 要解密的文件
    outfile = fopen(outpath, "wb"); //解密后的文件

    // 检查文件是否存在
    CHECK_FILE_EXSIT(infile, inpath)
    CHECK_FILE_EXSIT(outfile, outpath)

    int cipher_length = fread(inbuf, sizeof(BYTE), MAXLEN, infile); //读取要解密的文件的大小
    int plain_len; //解密后的大小

    SM4Decrypt(inbuf, cipher_length, outbuf, plain_len, key); //使用SM4解密
    fwrite(outbuf, plain_len, sizeof(BYTE), outfile); // 写入文件

    std::cout<<"Successfully decrypted "<<inpath<<"!"<<std::endl;
    return 1;
}

void print_usage() {
    std::cout<<"Usage: \n\tsm4utils -e <key-path> <unencrypted-path> <encrypted-path>"
        "\n\tsm4utils -d <key-path> <encrypted-path> <decrypted-path>"<<std::endl;
}

int main(int argc, const char * argv[]) {
    if (argc != 5) {
        print_usage();
        return 0;
    }

    FILE *keyfile;
    BYTE key[1024] = {0};

    keyfile = fopen(argv[2], "rb");
    CHECK_FILE_EXSIT(keyfile, argv[2])

    if (strcmp(argv[1], "-e") == 0) {
        encrypt(argv[3], argv[4], key);
    } else if (strcmp(argv[1], "-d") == 0) {
        decrypt(argv[3], argv[4], key);
    } else {
        std::cout<<"Invalid option:"<<argv[1]<<std::endl;
    }

    return 0;
}
