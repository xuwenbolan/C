#include <stdio.h>
#include <pthread.h>

void* myfun()
{
    printf("hello world!");
    return NULL;
}

int main()
{
    pthread_t th;
    pthread_create(&th,NULL,myfun,NULL);
    pthread_join(th,NULL);
    return 0;
}