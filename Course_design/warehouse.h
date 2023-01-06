#include <stdio.h>
#include <stdlib.h>

// #ifndef GBK
// #define GBK
// #endif 

//结构体声明

typedef struct _Goods // 货物的结构体
{
    char name[10];     // 货物名称
    char date[11];     // 入库日期
    char place[20];    // 保存位置
    char sup_unit[10]; // 供货单位
    char phone[15];    // 厂家电话
    int num;           // 货物数量
    float price;         // 货物价格
} Goods;

typedef struct Goods_Point // 定义货物链表节点
{
    Goods goods;
    struct Goods_Point *next;
} G_Point;

G_Point *G_head = NULL; // 创建货物链表头指针

typedef struct _Admin // 管理员的结构体
{
    char name[5];      // 管理员名字
    char phone[15];    // 管理员电话/登录账号
    char password[20]; // 登录密码
    char unit[10];     // 所在单位
} Admin;

typedef struct Admin_point // 定义管理员链表节点
{
    Admin admin;
    struct Admin_point *next;
} A_point;

A_point *A_head = NULL; // 创建管理员链表头指针


//函数声明

void Goods_read(G_Point* headpoint);
void Add_point(G_Point* headpoint,Goods point);