#include <stdio.h>
int main()
{
    int a[4][5] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
    int *p1;
    int **p2;
    int(*p3)[5];
    int *p4[4];

    p1 = a[0];
    p2 = p4;
    p3 = a;
    p4[0] = a[0];
    p4[1] = a[1];
    p4[2] = a[2];
    p4[3] = a[3];

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j <5; j++)
        {
            printf("%-3d%-3d%-3d%-3d", *(p1++), p2[i][j], p3[i][j], p4[i][j]);
            printf("\n");
        }
    }
}