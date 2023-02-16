#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <arpa/inet.h>
#define MB 1024*1024

void file_server()
{
    int skfd, cnfd;
    struct sockaddr_in sockAddr, cltAddr;
    socklen_t addrLen;
    int size, netSize;
    char buf[MB]={0};
 
    //创建tcp socket
    if((skfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket");
        exit(1);
    } else {
        printf("socket success!\n");
    }
 
    //创建结构  绑定地址端口号
    memset(&sockAddr, 0, sizeof(struct sockaddr_in));
    sockAddr.sin_family = AF_INET;
    sockAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    sockAddr.sin_port = htons(23334);
 
    //bind
    if(bind(skfd, (struct sockaddr *)(&sockAddr), sizeof(struct sockaddr)) < 0) {
        perror("Bind");
        exit(1);
    } else {
        printf("bind success!\n");
    }
 
    //listen   监听  最大4个用户
    if(listen(skfd, 4) < 0) {
        perror("Listen");
        exit(1);
    } else {
        printf("listen success!\n");
    }
 
    /* 调用accept,服务器端一直阻塞，直到客户程序与其建立连接成功为止*/
    addrLen = sizeof(struct sockaddr_in);
    if((cnfd = accept(skfd, (struct sockaddr *)(&cltAddr), &addrLen)) < 0) {
        perror("Accept");
        exit(1);
    } else {
        printf("accept success!\n");
    }
    int r_size = 0;
    int sum = 0,fsize;
    char filename[50]={0};
    char filesize[20]={0};
    char s_size[6];
    read(cnfd,filename,50);
    printf("%s\n",filename);
    write(cnfd, "success", 8);
    FILE *pf = fopen(filename,"wb");
    read(cnfd,filesize,20);
    write(cnfd, "success", 8);
    sscanf(filesize,"%d",&fsize);
    printf("%s\n",filesize);
    do
	{
		memset(buf, 0, sizeof(buf));
		r_size = read(cnfd, buf, sizeof(buf));
        // sprintf(s_size,"%d",r_size);
        
        fwrite(buf,sizeof(char),MB,pf);
		// write(cnfd, "success", 8);
        sum+=r_size;
        printf("%.0f%%\n",((float)sum/(float)fsize)*100);
	} while (sum<fsize);

    printf("%d\n",sum);
    // char *str = "Hello World!";
    // send(cnfd, str, strlen(str)+sizeof(char),0);
    close(skfd);
    close(cnfd);
}

int main()
{
    file_server();
    return 0;
}