#include <stdio.h>
#include <string.h>

int f(int m)
{
    static int k = 0;
    int s=0;
    for(;k<=m;k++)s++;
    return s;
}
int main()
{
   printf(" Hello world! ");
   return 0;
}