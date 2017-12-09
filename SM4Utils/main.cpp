//
//  main.cpp
//  SM4Utils
//
//  Created by 刘嘉铭 on 2017/12/9.
//  Copyright © 2017年 Kalen Blue. All rights reserved.
//

#include <stdlib.h>
#include <stdio.h>
#include "sms4.h"


#define MAXLEN 1024*1024*2


int main(int argc, const char * argv[]) {
    FILE *infile, *outfile;
    BYTE inbuf[MAXLEN]={0};
    
    infile = fopen("/Users/kalen/Pictures/001.jpg", "rb");
    outfile = fopen("encrypt.jpg", "wb");
    
    int plain_length = fread(inbuf, sizeof(BYTE), MAXLEN, infile);
    
    printf("%d\n", plain_length);
    
    BYTE outbuff[MAXLEN]={0};
    int cipher_len;
    BYTE a[16] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
    BYTE *key=a;
    
    SM4Encrypt(inbuf, plain_length, outbuff, cipher_len, key);
    
    fwrite(<#const void *__ptr#>, <#size_t __size#>, <#size_t __nitems#>, <#FILE *__stream#>)
    
    printf("%d\n", cipher_len);
    
    for (int i=0; i < cipher_len; i++) {
        printf("%X ", outbuff[i]);
    }
    
    
    
    return 0;
}
