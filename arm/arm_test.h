#define _USE_MATH_DEFINES 
#include <math.h>
#include <stdio.h>

typedef unsigned char u8;

typedef struct
{
    float theta1;
    float theta2;
    float theta3;
    float theta4;
    float a1;
    float a2;
    float a3;
    float Bx;
    float By;
    float Gamma;
    float Gamma_r;
    float beta;
    float alpha;
    float L_bo;
    float r_x, r_y, r_z;
    float G_x, G_y, G_z;
    float res_x, res_y, res_z;

} angle;

float Sx, Sy, Sz, T_temp, _S, _G,ROB_R;
int cal_flag=1;

void inti_ROB(void);
int mo_3(float x, float y, float z, float Gamma);
int ROB_GO_STR(angle *state);