#include "video_prase_win.h"

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

    #if defined(__WIN32__)

    SYSTEM_INFO sysInfo;
    GetSystemInfo(&sysInfo); // 获取物理 CPU 数量
    DWORD num_cpus = sysInfo.dwNumberOfProcessors;

    #endif

    #if defined(__LINUX__)
    long num_cpus = sysconf( _SC_NPROCESSORS_ONLN);
    #endif
    
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