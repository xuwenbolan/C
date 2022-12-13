#include <stdio.h>

void strncpy1(char *dest, const char *src, size_t n);
int strcmp1(const char *_Str1,const char *_Str2);
void fun(char str[],char a);
int sum1(int n);
int sum2(int n);
int calc(char s[]);

int main()
{
    char a[5]={"12345"};
    printf("%c",(&a[1])[0]);
}

int calc(char s[])
{
    int num1=0,num2=0,d=0,sum=0;
    for(int i=0;s[i]!=0;i++)
    {
        if(s[i]==' ')continue;
        if(s[i]>47 && s[i]<58)
        {
            if(d==0)num1=num1*10+(s[i]-'0');
            else num2=num2*10+(s[i]-'0');
        }
        else d=i;
    }
    if(d==0)
    {
        printf("Error!");
        return 0;
    }
    if(s[d]=='+')sum=num1+num2;
    else if(s[d]=='-')sum=num1-num2;
    else if(s[d]=='*' || s[d]=='x' || s[d]=='X')sum=num1*num2;
    else if(s[d]=='/')sum=num1/num2;
    return sum;
}

int sum1(int n)
{
    if(n==0) return 0;
    else return n+sum1(n-1);
}

int sum2(int n)
{
    static int i=0;
    i+=n;
    return i;
}

void fun(char str[],char a)
{
    int point = 0;
    for (int i = 0;str[i]!=0; i++) 
    {
        if (str[i] == a) continue;
        else 
        {
            str[point] = str[i];
            point++; 
        }
    }
    str[point] = '\0';
}

void strncpy1(char *dest, const char *src, size_t n)
{
    while(n--) dest[n]=src[n];
}

int strcmp1(const char *_Str1,const char *_Str2)
{
    for(int i=0;_Str1[i]!=0;i++)
    {
        if(_Str1[i+1]==0 && _Str2[i+1]==0)return 0;
        if(_Str1[i+1]==0 && _Str2[i+1]!=0)return -1;
        if(_Str1[i+1]!=0 && _Str2[i+1]==0)return 1;
    }
    return -1;
}
