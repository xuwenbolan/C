#include "Thread_Pool_WIN.h"
#include <windows.h>
#include <stdio.h>

/* ========================== STRUCTURES ============================ */


/* Binary semaphore */
typedef struct bsem {
    HANDLE mutex; // LINUX pthread_mutex_t mutex
    HANDLE  cond; // LINUX pthread_cond_t   cond
    int v;
} bsem;

