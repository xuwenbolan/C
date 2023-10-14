#include <stdio.h>

typedef struct Dot
{
    float x;
    float y;
    float z;
}Dot;

Dot dot_init(int x,int y,int z)
{
    Dot dot;
    dot.x = x;
    dot.y = y;
    dot.z = z;
    return dot;
}

int main()
{
    Dot A,B,tmp;
    A=dot_init(0, 0, 1);
    B=dot_init(2, 5, 6);
    // printf("%d %d %d", A.x, A.y, A.z);
    float m, n, p;
    m = B.x - A.x;
    n = B.y - A.y;
    p = B.z - A.z;
    float diff;
    for (float t = 0;; t += 0.01)
    {
        if(tmp.x!=B.x)
            tmp.x = A.x + m * t;
        if(tmp.y!=B.y)
            tmp.y = A.y + n * t;
        if(tmp.z!=B.z)
            tmp.z = A.z + p * t;
        printf("%f %f %f\n", tmp.x, tmp.y, tmp.z);
        diff = (tmp.x - B.x) + (tmp.y - B.y) + (tmp.z - B.z);
        if(-0.0005 <= diff && diff <= 0.0005)break;
    }
    return 0;
}