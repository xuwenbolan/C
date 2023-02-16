#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

int file_size(char* filename)
{
    struct stat statbuf;
    stat(filename,&statbuf);
    int size=statbuf.st_size;
    return size;
}

int main()
{
    FILE *fp = fopen("test.pdf","rb");
    char buf[1024];
    int size=file_size("test.pdf");
    printf("%d\n",size);
    size = 0;
    int sum=0;
    do
    {
        size = fread(buf,sizeof(char),1024,fp);
        sum+=size;
        printf("%d\n",size);
    }while(size==1024);
    printf("%d",sum);
    return 0;
}

