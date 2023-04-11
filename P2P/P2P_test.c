#include <stdio.h>
#include <stdlib.h>
#include <WinSock2.h>
#include <sys/stat.h>
#include <time.h>
#pragma comment(lib, "ws2_32.lib")
#define SIZE 10240

int file_size(char *filename)
{
    struct stat statbuf;
    stat(filename, &statbuf);
    int size = statbuf.st_size;
    return size;
}

int main()
{
    char *filename = "test.zip";
    int filesize = file_size(filename);
    FILE *fp = fopen(filename, "rb");
    int mode=0,size=1;
    char buf[SIZE]={0};
    // 初始化DLL
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    // 初始化地址
    struct sockaddr_in remoteAddr;

    memset(&remoteAddr, 0, sizeof(remoteAddr));
    remoteAddr.sin_family = AF_INET;
    remoteAddr.sin_addr.s_addr = inet_addr("43.138.161.163"); // 43.138.161.163 125.93.148.63
    remoteAddr.sin_port = htons(23334);
    SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    connect(sock, (SOCKADDR *)&remoteAddr, sizeof(SOCKADDR));
    
    mode =1;
    send(sock,&mode,sizeof(mode),0);
    recv(sock,&mode,sizeof(mode),0);
    if(mode==2)send(sock,filename,sizeof(filename),0);
    recv(sock,&mode,sizeof(mode),0);
    if(mode==3)send(sock,&filesize,sizeof(filesize),0);
    recv(sock,&mode,sizeof(mode),0);
    if(mode==4)printf("------------\n");
    while (size > 0)
    {
        memset(buf, 0, sizeof(buf));
        size = fread(buf,sizeof(char),SIZE,fp);
        send(sock, buf,size,0);
    }
    system("pause");
    closesocket(sock);
    // 关闭套接字
    // 终止使用 DLL
    WSACleanup();
    return 0;
}
