//
// Created by xuwenbo on 23-8-28.
//
//#define PY_SSIZE_T_CLEAN
#include "video_prase.h"
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/stat.h>
#include <malloc.h>
#include <sys/time.h>
#include "../Example/Thread_Pool.h"
//#include <python3.10/Python.h>


typedef struct
{
    size_t size;
    uint8_t *buf;
}buf_t;

void xor_encrypt(uint8_t *block, size_t block_size);
size_t get_file_size(char* filename);
buf_t *split_file(char* filename,size_t block_size);
void free_buf_t(buf_t *file_blocks);
void join_file(buf_t *blocks,char *filename);
void xor_multi(void *arg);

int main()
{
    struct timeval start, end;
    double elapsed;

    gettimeofday(&start, NULL);  // 记录开始时间
///media/xuwenbo/Data/ubuntu-22.04.2-desktop-amd64.iso
    char *input_file = "/media/xuwenbo/Data/ubuntu-22.04.2-desktop-amd64.iso";// /home/xuwenbo/data/video.m3u8

    char output_file[strlen(input_file)+ strlen(".encode")+1];
    strcat(output_file,input_file);
    strcat(output_file,".encode");

    long num_cpus = sysconf( _SC_NPROCESSORS_ONLN); // 获取物理 CPU 数量

    size_t file_size = get_file_size(input_file);// get filesize

    printf("Total size: %ld\n",file_size);

    size_t block_size = file_size / num_cpus;

    buf_t *blocks = split_file(input_file,block_size);

    size_t sum=0;
    threadpool thpool = thpool_init(num_cpus-1);
    for(int i=0;i<=num_cpus;i++)
    {
        thpool_add_work(thpool,xor_multi,&(blocks[i]));
//        xor_encrypt(blocks[i].buf,blocks[i].size);
        sum+=blocks[i].size;
    }

    thpool_wait(thpool);

    printf("Sum size: %ld\n",sum);

    join_file(blocks,output_file);

    free_buf_t(blocks);

    thpool_destroy(thpool);

    gettimeofday(&end, NULL);    // 记录结束时间
    elapsed = (end.tv_sec - start.tv_sec) + ((end.tv_usec - start.tv_usec) / 1000000.0);  // 计算运行时间



    printf("Time used: %f seconds\n", elapsed);

    return 0;
}

// 定义异或加密函数
void xor_multi(void *arg)
{
    buf_t block = *((buf_t *)arg);
    // 对每个字节进行异或运算
    for (size_t i = 0; i < block.size; i++)
    {
        block.buf[i] ^= 88;
    }
}

// 定义异或加密函数
void xor_encrypt(uint8_t *block, size_t block_size)
{
    // 对每个字节进行异或运算
    for (size_t i = 0; i < block_size; i++)
    {
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

buf_t *split_file(char* filename,size_t block_size)
{
    FILE *fd;
    size_t size=0;
//    uint8_t buf[block_size];
    uint8_t *buf = (uint8_t *)malloc(block_size);
    buf_t *file_blocks = (buf_t *)malloc((sysconf( _SC_NPROCESSORS_ONLN) +1)* sizeof(buf_t));
    int i =0;
    fd = fopen(filename,"rb");
    do
    {
        size = fread(buf,sizeof(uint8_t),block_size,fd);
        file_blocks[i].buf = (uint8_t *)malloc(size);
        file_blocks[i].size = size;
        memcpy(file_blocks[i++].buf,buf,size);
    }while(size==block_size);
    fclose(fd);
    free(buf);
    return file_blocks;
}

void free_buf_t(buf_t *file_blocks)
{
    for(int i=0;file_blocks[i].size!=0;i++)
    {
        free(file_blocks[i].buf);
    }
    free(file_blocks);
}

void join_file(buf_t *blocks,char *filename)
{
    FILE *fd;
    fd = fopen(filename,"wb");
    for(int i=0;blocks[i].size!=0;i++)
    {
        fwrite(blocks[i].buf,sizeof(uint8_t),blocks[i].size,fd);
    }
    fclose(fd);
}