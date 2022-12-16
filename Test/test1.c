#include <stdio.h>

int main()
{
    int n=11;
    int a[]={1,2,3,1,2,2,7,4,9,3,5};
    for(int i=0;a[i]!=0;i++)printf("%d ",a[i]);
    printf("\n");
    int mid=n/2,t;
    for(int i=mid-1;i>0;i--)
    {
        for(int j=0;j<i;j++)
        {
            if(a[j]>a[j+1])
            {
                t=a[j];
                a[j]=a[j+1];
                a[j+1]=t;
            }
        }
    }
    if(n%2!=0)mid++;
    for(int i=n-1;i>n/2+1;i--)
    {
        for(int j=mid;j<i;j++)
        {
            if(a[j]<a[j+1])
            {
                t=a[j];
                a[j]=a[j+1];
                a[j+1]=t;
            }
        }
    }
    for(int i=0;i<n;i++)printf("%d ",a[i]);
    return 0;
}