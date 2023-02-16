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

void file_server()
{
    int skfd, cnfd;
    struct sockaddr_in sockAddr, cltAddr;
    socklen_t addrLen;
    int size, netSize;
    char buf[1024]={0};
 
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
    int sum = 0;
    char filename[50]={0};
    read(cnfd,filename,50);
    printf("%s\n",filename);
    FILE *pf = fopen(filename,"rb+");
    send(cnfd,"OK",2,0);
    do
	{
		memset(buf, 0, sizeof(buf));
		r_size = read(cnfd, buf, sizeof(buf));
		// usleep(10000);	
		write(cnfd, "success", 8);
        sum+=r_size;
	} while (r_size == 1024);

    printf("%d\n",sum);
    // char *str = "Hello World!";
    // send(cnfd, str, strlen(str)+sizeof(char),0);
    close(cnfd);
    close(skfd);
}

int main()
{
    file_server();
    return 0;
}