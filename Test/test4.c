#include <stdio.h>

int main()
{
    FILE *fp = NULL;
    char data[255]={0};

    fopen_s(&fp,"test.txt", "r");
    fscanf(fp, "%s", data);//读取一段字符串以空格结束
    printf("1: %s\n",data);
    fclose(fp);

    return 0;
}