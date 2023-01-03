#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 定义一个商品结构体
typedef struct sp
{
    char no[12];     // 商品编号
    char name[40];   // 名称
    int workload;    // 库存量
    struct sp *next; // 指向下一节点的指针
} SP;

// 函数声明放在这里
void ListCreate(SP *L, int n); // 创建商品链表节点
void LIstSearch(SP *L);        // 查找商品信息
void ListModify(SP *L);        // 修改商品信息
void ListInsert(SP *L);        // 插入商品信息
void ListDelete(SP *L);        // 删除商品信息
void Input(SP *p, int i);      // 输入商品信息
void SumSp(SP *L);             // 统计商品的库存总量
void Sort(SP *L);              // 对每类商品的库存量进行排名
void Menu();                   // 考试报名管理系统的菜单

// 商品库存管理系统的主函数入口
int main()
{
    int item, n;                  // item用于接收输入的命令，n用于接收输入的商品人数
    SP *L = NULL;                 // 初始化一个头节点
    L = (SP *)malloc(sizeof(SP)); // 为头节点开辟内存空间
    L->next = NULL;               // 将头节点的指针域置空
    do
    {
        Menu(); // 菜单
        printf("请输入相应的数字，进行相应的操作:\n");
        scanf("%d", &item);
        system("cls");
        switch (item)
        {
        case 1:
            printf("请输入您要录入的商品数目:");
            scanf("%d", &n);
            ListCreate(L, n);
            getchar();
            printf("\n请按任意键返回主菜单\n");
            getchar();
            system("cls");
            break;
        case 2:
            LIstSearch(L); // 查找商品信息
            getchar();
            printf("\n请按任意键返回主菜单\n");
            getchar();
            system("cls");
            break;
        case 3:
            ListModify(L); // 修改商品库存信息
            getchar();
            printf("\n请按任意键返回主菜单\n");
            getchar();
            system("cls");
            break;
        case 4:
            ListDelete(L); // 删除商品信息
            getchar();
            printf("\n请按任意键返回主菜单\n");
            getchar();
            system("cls");
            break;
        case 5:
            ListInsert(L); // 插入商品信息
            getchar();
            printf("\n请按任意键返回主菜单\n");
            getchar();
            system("cls");
            break;
        case 6:
            SumSp(L);
            getchar();
            printf("\n请按任意键返回主菜单\n");
            getchar();
            system("cls");
            break;
        case 7:
            Sort(L);
            getchar();
            printf("\n请按任意键返回主菜单\n");
            getchar();
            system("cls");
            break;
        case 0: // 退出商品库存管理系统
            printf("即将退出商品库存管理系统.....");
            exit(0);
        default:
            printf("您输入的指令不正确，请重新输入");
        }
        printf("\n\n");
    } while (item);
    return 0;
}

// 创建链表，将新生成的节点插入到链表的表头
void ListCreate(SP *L, int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        SP *p;
        // 将新生成的节点插入到链表中
        p = NULL;
        p = (SP *)malloc(sizeof(SP));
        Input(p, i);
        p->next = L->next;
        L->next = p;
    }
    printf("录入成功！");
}

// 查找商品库存量
void LIstSearch(SP *L)
{
    char n[40];
    SP *p = L->next;
    if (p == NULL)
        printf("数据为空，无法查找！");
    else
    {
        printf("请输入您要查找的商品名称:");
        scanf("%s", n);
        while (strcmp(p->name, n) != 0)
        {
            p = p->next;
            if (p == NULL)
            {
                printf("没有找到相关信息\n");
                return;
            }
        }
        printf("%s的库存量为%d\n", p->name, p->workload);
    }
}

// 修改商品的库存量
void ListModify(SP *L)
{
    int a;
    char nam[40];
    SP *p = L->next;
    if (p == NULL)
        printf("数据为空，无法修改！");
    else
    {
        printf("请输入您修改的商品名称:");
        scanf("%s", nam);
        while (strcmp(p->name, nam) != 0)
        {
            p = p->next;
            if (p == NULL)
            {
                printf("没有找到相关信息\n");
                return;
            }
        }
        printf("请输入您修改后的库存量:");
        scanf("%d", &p->workload);
        printf("修改成功");
    }
}

// 删除商品信息
void ListDelete(SP *L)
{
    char n[40];
    SP *p = L->next, *pre = L; // 定义p指针指向头节点的指向，定义pre指向头节点，pre始终指向p的前驱节点
    if (p == NULL)
        printf("数据为空，无法删除！");
    else
    {
        printf("请输入您要删除的商品名称:");
        scanf("%s", n);
        while (strcmp(p->name, n) != 0)
        {
            pre = p;
            p = pre->next;
            if (p == NULL)
            {
                printf("没有找到相关信息，无法删除\n");
                return;
            }
        }
        pre->next = p->next;
        free(p);
        printf("删除成功");
    }
}

// 插入商品库存的相关信息
void ListInsert(SP *L)
{
    SP *s = NULL; // 生成一个新节点s
    s = (SP *)malloc(sizeof(SP));
    printf("请输入商品的商品编号:");
    scanf("%s", s->no);
    printf("请输入商品的名称:");
    scanf("%s", s->name);
    printf("请输入商品的库存量:");
    scanf("%d", &s->workload);
    s->next = L->next;
    L->next = s;
    printf("插入成功!");
}

// 统计商品的库存总量
void SumSp(SP *L)
{
    int sum = 0;
    SP *p = L->next;
    while (p != NULL)
    {
        sum += p->workload;
        p = p->next;
    }
    printf("商品的库存总量为%d\n", sum);
}

// 对每类商品的库存量进行排名
void Sort(SP *L)
{
    SP *p, *q, *tail, *l;
    tail = NULL;
    while ((L->next->next) != tail)
    {
        p = L;
        q = L->next;
        while (q->next != tail)
        {
            if ((q->workload) > (q->next->workload))
            {
                p->next = q->next;
                q->next = q->next->next;
                p->next->next = q;
                q = p->next;
            }
            q = q->next;
            p = p->next;
        }
        tail = q;
    }
    printf("商品库存量从小到大结果如下:\n");
    l = L->next;
    while (l != NULL)
    {
        if (l->next != NULL)
        {
            printf("%s(%d)->", l->name, l->workload);
            l = l->next;
        }
        else
        {
            printf("%s(%d)", l->name, l->workload);
            l = l->next;
        }
    }
}
// 输入商品库存的相关信息
void Input(SP *p, int i)
{
    printf("请输入第%d个商品的商品编号:", i + 1);
    scanf("%s", p->no);
    printf("请输入第%d个商品的名称:", i + 1);
    scanf("%s", p->name);
    printf("请输入第%d个商品的库存量:", i + 1);
    scanf("%d", &p->workload);
}

// 商品库存管理系统的菜单
void Menu()
{
    printf("\n\n");
    printf("\t\t\t===================商品库存管理系统======================\n");
    printf("\t\t\t* 作者:许文博  班级:计算机科学与技术4班  学号:3122010092   *\n");
    printf("\t\t\t*                                                       *\n");
    printf("\t\t\t*          1>. 录入商品库存信息                         *\n");
    printf("\t\t\t*          2>. 查找某个商品的库存量                     *\n");
    printf("\t\t\t*          3>. 修改某个商品的库存量                     *\n");
    printf("\t\t\t*          4>. 删除某个商品库存相关信息                 *\n");
    printf("\t\t\t*          5>. 插入某个商品的相关信息                   *\n");
    printf("\t\t\t*          6>. 统计商品的库存总量                       *\n");
    printf("\t\t\t*          7>. 对每类商品的库存量排名                   *\n");
    printf("\t\t\t*          0>. 退出管理系统                             *\n");
    printf("\t\t\t*                                        欢迎使用本系统!*\n");
    printf("\t\t\t========================================================\n");
    printf("\t\t\t输入选项，按回车进入选项:                                 \n");
}
