#include <stdio.h>
#include <pthread.h>

void* myfun(void *a)
{
    int b = *((int *)a);
    printf("%d",b);
    return NULL;
}

int main()
{
    pthread_t th;
    int a = 1;
    pthread_create(&th,NULL,myfun,&a);
    pthread_join(th,NULL);
    return 0;
}