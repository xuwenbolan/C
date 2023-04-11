#include <stdio.h>
#include <stdlib.h>
#include <WinSock2.h>
#include <sys/stat.h>
#pragma comment(lib, "ws2_32.lib")

int main()
{
    // 初始化DLL
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);
    
    //初始化地址
    struct sockaddr_in localAddr, cltAddr;
    memset(&localAddr, 0, sizeof(localAddr));
    localAddr.sin_family = AF_INET;
    localAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    localAddr.sin_port = htons(8086);

    int opt=1;
    SOCKET sock,clpd;
    sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (const void *)&opt, sizeof(opt));
    if (bind(sock, (struct sockaddr *)(&localAddr), sizeof(struct sockaddr)) < 0)
    {
        perror("Bind");
        exit(1);
    }
    else
    {
        printf("bind success!\n");
    }
    while(1)
    {
        // listen   监听  最大4个用户
        if (listen(sock, 4) < 0)
        {
            perror("Listen");
            exit(1);
        }
        else
        {
            printf("listen success!\n");
        }
        int len = sizeof(struct sockaddr_in);
        if ((clpd = accept(sock, (struct sockaddr *)&cltAddr,&len)) < 0)
        {
            perror("Accept");
            exit(1);
        }
        else
        {
            printf("accept success!\n");
        }
        printf("%s\n",inet_ntoa(cltAddr.sin_addr));
        printf("%d\n",ntohs(cltAddr.sin_port));
    }
    closesocket(sock);
    system("pause");
    // 关闭套接字
    // 终止使用 DLL
    WSACleanup();
    return 0;

}