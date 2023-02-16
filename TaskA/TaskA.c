#include <stdio.h>

int main()
{
    //99乘法表
    for (int a = 1; a <= 9; a++)
    {
        for (int b = 1; b <= a; b++)
        {
            printf(" % d * %d = % d\t", b, a, a * b);
        }
        printf("\n");
    }
    return 0;

    // long al = 1234567890;
    // float af1 = 1234567890;
    // float af2 = 9234567890;
    // double ad = 1234567890;
    // double ad2 = 12345678901234567;
    // printf(" al =%d\n", al);
    // printf(" af1 =%f\n", af1); // float类型只支持6位有效数
    // printf(" af2 =%f \n", af2);
    // printf(" ad =%f\n", ad); // double类型只支持15位有效数
    // printf(" ad2 =%f\n", ad2);

    // int a = -200, b = 324;
    // char c = 254;
    // printf("%d,%d,%d\n", a, b, c); // %d打印整型十进制数据
    // printf("%u,%u,%u\n", a, b, c); // %u输出无符号十进制 数据
    // printf("%x,%x,%x\n", a, b, c); // %x打印十六进制数据
    // printf("%c,%c,%c\n", a, b, c); // %c打印字符格式数据
}