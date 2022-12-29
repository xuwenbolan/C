#include <stdio.h>

int main()
{
    char *p1, *p2;
    int a = -1;
    p1 = (char *)&a;
    p2 = p1 + 2;
    printf("%p\n",p1);
    printf("%p\n",&a);
}

