#include <stdio.h>

int main()
{
    int n=5;
    int i,j,k,t=0;
    for (i=0;i<=n/10;i++)
    {
        k=(n-i*10)/5;
        for (j=0;j<=k;j++)
        {
        t++;
        }
    }
    printf("%d",t);
}

