#include <stdio.h>
#include <stdlib.h>
#include <WinSock2.h>
#include <sys/stat.h>
#pragma comment(lib, "ws2_32.lib")
#define MB 1024*1024 //*1024*1024

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
    // 初始化DLL
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);
    // 创建套接字
    SOCKET sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    // 向服务器发起请求
    struct sockaddr_in sockAddr;
    memset(&sockAddr, 0, sizeof(sockAddr)); // 每个字节都用0填充
    sockAddr.sin_family = PF_INET;
    sockAddr.sin_addr.s_addr = inet_addr("192.168.101.155"); // 43.138.161.163
    sockAddr.sin_port = htons(23334);
    connect(sock, (SOCKADDR *)&sockAddr, sizeof(SOCKADDR));
    // //接收服务器传回的数据
    // char szBuffer[MAXBYTE] = {0};
    // recv(sock, szBuffer, MAXBYTE, 0);
    // //输出接收到的数据
    // printf("Message form server: %s\n", szBuffer);
    // char *buf = "hello";
    // send(sock,buf,6,0);
    char buf[MB] = {0};
    char buf2[20] = {0};
    char fsize[20]={0};
    int filesize = file_size(filename);
    FILE *fp = fopen(filename, "rb");
    send(sock, filename, sizeof(filename), 0);
    recv(sock, buf2, sizeof(buf2),0);
	if(strncmp(buf2,"success",8) == 0)memset(buf2, 0, sizeof(buf2));
    sprintf(fsize,"%d",filesize);
    send(sock, fsize,strlen(fsize),0);
    recv(sock, buf2, sizeof(buf2),0);
    if(strncmp(buf2,"success",8) == 0)printf("----------\n");
    int size = 1;
    int sum = 0;
    while (size > 0)
    {
        memset(buf, 0, sizeof(buf));
        size = fread(buf,sizeof(char),MB,fp);
        // printf("%d\n",size);
        send(sock, buf,size,0);
    }
    // int filesize = file_size(filename);
    system("pause");
    // 关闭套接字
    closesocket(sock);
    // 终止使用 DLL
    WSACleanup();
    return 0;
}