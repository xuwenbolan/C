#include <stdio.h>
#include <string.h>
int main()
{
    int i, m=0, j;
    char a1[200]={0}, a2[100], a3[50];
    char a4[200] = {0};
    printf("first:\n");
    gets(a1);
    printf("second:\n");
    gets(a2);
    printf("third:\n");
    gets(a3);
    int len1 = strlen(a1);
    int len2 = strlen(a2);
    int len3 = strlen(a3);
    for (i = 0; i <len1; i++)
    {
        for (j = 0; j <len2; j++)
        {
            if (a1[i + j] == a2[j])m++;
            else break;
        }
        if(m==len2)
        {
            strcpy(a4, a1 + i + len2);
            strcpy(a1 + i, a3);
            strcpy(a1 + i + len3, a4);
        }
        m=0;
    }
    printf("result:%s", a1);
    return 0;
}
/*
1.你的程序判断相等的逻辑有严重的问题(比如按照200循环后面的0一直相等m一直增加)
2.无法判断局部相等的情况（例如：1231234，1234，1）
3.无法判断多次相等的情况（例如：123444123，123，1）
4.循环的次数不够灵活，增加了时间复杂度
*/