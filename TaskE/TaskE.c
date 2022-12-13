#include <stdio.h>

int main()
{
    int a[3][4][5] = {0}, *p1 = a, **p2, (*p3)[5], *p4[4];
    for (int i = 1; i <= 60; i++)
        *(p1 + i - 1) = i;

    for (int i = 0; i < 3; i++)
    {
        p1 = a[i];
        p2 = p4;
        p3 = a[i];
        p4[0] = p1;
        p4[1] = p1 + 5;
        p4[2] = p1 + 10;
        p4[3] = p1 + 15;
        for (int k = 0; k < 4; k++)
        {
            for (int j = 0; j < 5; j++)
            {
                printf("%-3d%-3d%-3d%-3d", *(p1++), p2[k][j], p3[k][j], p4[k][j]);
                printf("\n");
            }
        }
    }

    return 0;
}