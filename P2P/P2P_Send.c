#include <stdio.h>
#include <stdlib.h>
#include <WinSock2.h>
#include <sys/stat.h>
#pragma comment(lib, "ws2_32.lib")

int file_size(char *filename)
{
    struct stat statbuf;
    stat(filename, &statbuf);
    int size = statbuf.st_size;
    return size;
}

int main()
{
    char *filename = "test.pdf";
    // 初始化DLL
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);
    // 创建套接字
    SOCKET sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    // 向服务器发起请求
    struct sockaddr_in sockAddr;
    memset(&sockAddr, 0, sizeof(sockAddr)); // 每个字节都用0填充
    sockAddr.sin_family = PF_INET;
    sockAddr.sin_addr.s_addr = inet_addr("43.138.161.163");
    sockAddr.sin_port = htons(23334);
    connect(sock, (SOCKADDR *)&sockAddr, sizeof(SOCKADDR));
    // //接收服务器传回的数据
    // char szBuffer[MAXBYTE] = {0};
    // recv(sock, szBuffer, MAXBYTE, 0);
    // //输出接收到的数据
    // printf("Message form server: %s\n", szBuffer);
    // char *buf = "hello";
    // send(sock,buf,6,0);
    char buf[1024] = {0};
    int filesize = file_size(filename);
    FILE *fp = fopen(filename, "rb");
    send(sock, filename, sizeof(filename), 0);
    recv(sock, buf, 1024, 0);
    if (strncmp(buf, "OK", 2) == 0)
        printf("%d\n", filesize);
    // if(strncmp(buf, "OK", 2) == 0) send(sock,filesize,sizeof(filesize),0);
    int size = 0;
    int sum=0;
    char buf2[50]={0};
    do
    {
        memset(buf2, 0, sizeof(buf));
        size = fread(buf,sizeof(char),1024,fp);

        send(sock, buf,size,0);
        recv(sock, buf2, sizeof(buf2),0);
        if (strncmp(buf2, "success", 10) == 0)sum+=size;
        else continue;

    } while (size == 1024);
    // int size = fread(buf,sizeof(char),1024,fp);
    // send(sock,buf,strlen(buf),0);
    // int filesize = file_size(filename);
    // write(sock,buf,file_size+1);
    printf("%d\n",sum);
    system("pause");
    // 关闭套接字
    closesocket(sock);
    // 终止使用 DLL
    WSACleanup();
    return 0;
}