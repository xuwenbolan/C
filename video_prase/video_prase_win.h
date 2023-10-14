//
// Created by xuwenbo on 23-8-29.
//

#ifndef C_VIDEO_PRASE_WIN_H
#define C_VIDEO_PRASE_WIN_H
#define PY_SSIZE_T_CLEAN

// extern "C"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <windows.h>
#include "../Example/Thread_Pool.h"
// #include <Python.h>

typedef struct but_t
{
    size_t size;
    uint8_t *buf;
}buf_t;

#endif //C_VIDEO_PRASE_WIN_H
