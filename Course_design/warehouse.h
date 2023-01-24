#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <conio.h>

//宏定义
#define insert_goods 0
#define input_goods 1
#define out_goods 2
#define pick_goods 3
#define delete_goods 4
#define view_goods 5
#define sort_goods 6

//结构体声明

typedef struct _Goods // 货物的结构体
{
    char name[20];     // 货物名称
    char date[11];     // 入库日期
    char place[25];    // 入库位置
    char sup_unit[20]; // 供货单位
    char phone[12];    // 厂家电话
    int num;           // 货物数量
    float price;         // 货物价格
} Goods;

typedef struct Goods_Point // 定义货物链表节点
{
    struct Goods_Point *last;
    Goods goods;
    struct Goods_Point *next;
} G_Point;

G_Point *G_head = NULL; // 创建货物链表头指针
G_Point *G_end = NULL;  // 创建货物链表尾指针

typedef struct _Admin // 管理员的结构体
{
    char name[10];      // 管理员名字
    char phone[15];    // 管理员电话
    char password[20]; // 登录密码
    char unit[20];     // 所在单位
} Admin;

typedef struct Admin_point // 定义管理员链表节点
{
    struct Admin_point *last;
    Admin admin;
    struct Admin_point *next;
} A_Point;

A_Point *A_head = NULL; // 创建管理员链表头指针
A_Point *A_end  = NULL; // 创建管理员链表头指针


//函数声明

void Goods_read(); // 读取货物文件
void Goods_write(); // 写入货物文件
void Add_Gpoint(Goods point); // 添加一个货物节点c
Goods Add_Goods(); // 添加货物
void show_Goods(G_Point *node); // 显示货物
char* get_time(char *des); // 获取当前时间
int Find_Goods(char *target); // 查找货物
G_Point* Find_tar(char* target); // 查找目标
void Pick_Goods(G_Point* temp); // 选择货物
void Change_Goods(G_Point* temp,int kind); // 更改货物信息
void Operate_Menu(G_Point *node); // 操作菜单
void Select(int kind,G_Point* node); //操作选择
void Sort_Goods();
void Insert_Point(G_Point* node,Goods temp); //插入一个货物节点
void HideCursor(); //隐藏光标
void gotoxy(int x, int y);  //显示字符的位置
void Begin(); //初始化界面
void Sign_in(); //登录界面
void Admin_read(); //读取管理员信息
void Add_Apoint(Admin node); //添加管理员列表节点