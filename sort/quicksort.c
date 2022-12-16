#include <stdio.h>


int main()
{
    char s[200]={"W_SINMO`JbBZAYE^QdDfSaQS[PCShFeWfPaJ^FBghFWA`^"};
    int c[26]={0};
    for(int i=0;s[i]!=0;i++)
    {
        c[s[i]-97]++;
    }
     for (int i = 0; i < 26; i++) 
    {
        printf("c[%d]=%d ", i, c[i]);
    }
    return 0;
}

int quicksort(int *nums)
{
   int left=0,middle=0,right=0;
   
}