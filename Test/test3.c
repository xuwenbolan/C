#include <stdio.h>
#include <string.h>


struct abc
{
    int num;
}ab;

void swap(int a,int b)
{
    int t=a;
    a = b;
    b = t;
}

int main()
{
    int a =178;
    int b = 132;
    // a <<= 1;
    swap(a, b);
    printf("%d %d\n", a,b);
    // char str[5] = "hello";
    // printf("%s",str);
    // a.num=1;
    // if(a.num==12)printf("1111");
    // else printf("2222");
    //printf("%d",p-a);
    // char *p1, *p2; //定义char型的指针：p1,p2
    // int a = -1;    //定义了int型变量a：FF FF FF FF
    // p1 = (char *)&a; //将p1指向a的地址并强制转换为char*型(char只能读取一个字节) p1指向a的首地址(第一个字节)
    // p2 = p1+2;       //p2指向a的第3个地址(第3个字节)
    // printf("%d\n",p1);//读取a的一个字节进行输出：FF 因为是(int)有符号型则输出-1 如果为(unsigned int)无符号型则为15
    // printf("%d\n",p2);//读取a+2的一个字节进行输出：FF
}