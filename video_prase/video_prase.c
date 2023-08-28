//
// Created by xuwenbo on 23-8-28.
//

#include "video_prase.h"
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/stat.h>
#include <malloc.h>

#define MAX_SIZE 1024

void xor_encrypt(uint8_t *block, size_t block_size);
size_t get_file_size(char* filename);
void split_file(char* filename,size_t block_size,uint8_t **file_blocks);

int main()
{
    char *path = "/home/xuwenbo/data/video.m3u8";

    long num_cpus = sysconf( _SC_NPROCESSORS_ONLN); // 获取物理 CPU 数量

    size_t file_size = get_file_size(path);

    int block_size = file_size / num_cpus;

    uint8_t **file_blocks[num_cpus+1];

    split_file(path,block_size,file_blocks);

    printf("%s",file_blocks[0]);

    return 0;
}

// 定义异或加密函数
void xor_encrypt(uint8_t *block, size_t block_size)
{
    // 对每个字节进行异或运算
    for (size_t i = 0; i < block_size; i++) {
        block[i] ^= 88;
    }
}

size_t get_file_size(char* filename)
{
    struct stat statbuf;
    stat(filename,&statbuf);
    size_t size=statbuf.st_size;
    return size;
}

void split_file(char* filename,size_t block_size,uint8_t **file_blocks)
{
    FILE *fd;
    size_t size=0;
    uint8_t buf[block_size];
    int i =0;
    fd = fopen(filename,"rb");
    do
    {
        size = fread(buf,sizeof(char),block_size,fd);
        file_blocks[i] = (uint8_t *)malloc(size);
        memcpy(file_blocks[i++],buf,size);
    }while(size==block_size);
    fclose(fd);
}
