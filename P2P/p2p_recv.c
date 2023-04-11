#include <stdio.h>
#include <stdlib.h>
#include <WinSock2.h>
#include <sys/stat.h>
#pragma comment(lib, "ws2_32.lib")
#define SIZE 10240

int main()
{
    char buf[SIZE]={0};
     // 初始化DLL
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    // 初始化地址
    struct sockaddr_in remoteAddr;

    memset(&remoteAddr, 0, sizeof(remoteAddr));
    remoteAddr.sin_family = AF_INET;
    remoteAddr.sin_addr.s_addr = inet_addr("125.93.148.63"); // 43.138.161.163
    remoteAddr.sin_port = htons(23334);
    SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    connect(sock, (SOCKADDR *)&remoteAddr, sizeof(SOCKADDR));

    int mode = -1;
    send(sock,&mode,sizeof(mode),0);
    char filename[100]={0};
    recv(sock,filename,sizeof(filename),0);
    FILE *fp = fopen(filename,"wb");
    int filesize = 0,size=1,sum=0;
    recv(sock,&filesize,sizeof(filesize),0);
    while (sum < filesize)
    {
        memset(buf, 0, sizeof(buf));
        size = recv(sock,buf,SIZE,0);
        fwrite(buf,sizeof(char),size,fp);
        sum += size;
        printf("%.0f%%\n", ((float)sum / (float)filesize) * 100);
    }
    system("pause");
    closesocket(sock);
    return 0;
}