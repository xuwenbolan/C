#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include<math.h>
#define leapYear(y) ((y % 4 == 0) && (y % 100 != 0) || (y % 400 == 0))
#define N 20
typedef struct info
{
    char name[N];
    char phone_number[N];
    char ground[N];
    char start_time[N];
    char end_time[N];
    int day;
} INFO;

typedef struct appointment
{
    INFO data;        
    struct appointment *next; 
} Appointment;

struct date
{
    int years;
    int months;
    int days;
};
int count = 0, n;
int days_on_month[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}; 
char name[N];
void showMenu();
Appointment *createClass(int n);
void showAppointinfo(Appointment *h);
void Search_Ground(Appointment *h, char name[]);
Appointment *deleteAppointinfo(Appointment *h, char name[]);
void addAppointinfo(Appointment *h);
void changeAppointinfo(Appointment *h, char name[]);
void saveAppointinfo(Appointment *h);
Appointment *loadAppointinfo(Appointment *h);
void Search_personname(Appointment *h, char name[]);
int days_date(struct date s); 
int diff(struct date s1, struct date s2); 

int main()
{
    int command, i, a, b; 
    Appointment *h;
    showMenu();
    printf("请输入相应的数字，进行相应的操作:\n");
    scanf("%d", &command);
    printf("\n");
    while (1) 
    {
        switch (command)
        {
        case 1:
        {
            printf("请输入您要录入的预约信息数目:");
            scanf("%d", &count);
            printf("预约信息数目是%d\n", count);
        };
        break;
        case 2:
        {
            h = createClass(count);
            printf("创建球场安排信息");
        };
        break;
        case 3:
        {
            showAppointinfo(h);
            printf("显示球场安排信息");
        };
        break;
        case 4:
        {
            printf("请输入需要搜索的场地\n");
            scanf("%s", &name);
            Search_Ground(h, name);
        };
        break;
        case 5:
        {
            printf("请输入需要搜索的预约人姓名\n");
            scanf("%s", &name);
            Search_personname(h, name);
        };
        break;
        case 6:
            printf("请输入需删除的预约人信息\n");
            scanf("%s", &name);
            h = deleteAppointinfo(h, name);
            break;
        case 7:
        {
            printf("请输入需要修改的预约人信息\n");
            scanf("%s", &name);
            changeAppointinfo(h, name); 
        };
        break;
        case 0:
            exit(0); 
        }
        printf("操作已完成");
        getch();       
        system("cls"); 
        showMenu();
        printf("请输入相应的数字，进行相应的操作:\n");
        scanf("%d", &command);
    }

    system("pause");
    return 0;
}
void showMenu()
{
    printf("\t\t\t       ---------球场信息预约管理----------               \n");
    printf("\t\t\t*          严永浩 3122010093   2022（4）                *\n");
    printf("\t\t\t*          1>. 输入录入的预约信息数目                   *\n");
    printf("\t\t\t*          2>. 创建球场安排信息                         *\n");
    printf("\t\t\t*          3>. 显示球场安排信息                         *\n");
    printf("\t\t\t*          4>. 搜索场地预约情况                         *\n");
    printf("\t\t\t*          5>. 搜索的预约人姓名                         *\n");
    printf("\t\t\t*          6>. 删除预约信息                             *\n");
    printf("\t\t\t*          7>. 输入需要修改的预约人信息                 *\n");
    printf("\t\t\t*          0>. 退出管理系统                             *\n");
    printf("\t\t\t*              欢迎使用本系统!                          *\n");
    printf("\t\t\t========================================================\n"); 
    printf("\t\t\t输入选项，按回车进入选项:                                 \n");
}

Appointment *createClass(int n)
{
    struct date s1, s2;
    Appointment *p, *q, *h;
    int i;
    for (i = 0; i < n; i++)
    {
        p = (Appointment *)malloc(sizeof(Appointment));
        printf("输入预约人姓名 预约电话 预约场地 预约开始时间 预约结束时间\n");
        printf("输入第%d个预约信息:\n", i + 1);
        scanf("%s%s%s%s%s", &p->data.name, &p->data.phone_number, &p->data.ground, &p->data.start_time, &p->data.end_time);
        sscanf(p->data.start_time, "%d-%d-%d", &s1.years, &s1.months, &s1.days);
        sscanf(p->data.end_time, "%d-%d-%d", &s2.years, &s2.months, &s2.days);
        p->data.day = diff(s1, s2);
        p->next = NULL;
        if (i == 0)
            h = p; 
        else
            q->next = p;
        q = p;
    }
    return h;
}

void showAppointinfo(Appointment *h) 
{
    Appointment *p;
    p = h;
    printf("球场安排信息\n");
    while (p != NULL)
    {
        printf("|%-6s|%-18s|%-15s|%-12s|%-12s|%-12d|", p->data.name, p->data.phone_number, p->data.ground,p->data.start_time,p->data.end_time,p->data.day);
        printf("\n");
        p = p->next;
    }
}


void Search_Ground(Appointment *h, char name[])
{
    int i = 0;
    Appointment *p;
    p = h;
    int flag = 0;
    while (p != NULL)
    {
        if (strcmp(p->data.ground, name) == 0)
        {
            printf("该场地的预约情况\n");
            printf("|%-6s|%-18s|%-15s|%-12s|%-12s|%-12d|\n", p->data.name, p->data.phone_number, p->data.ground, p->data.start_time, p->data.end_time, p->data.day);
            flag = 1;
            p = p->next;
        }
        else
            p = p->next;
        i++;
        if (i == count)
        {
            break;
        }
    }
    if (flag) 
        printf("该场地已被预约");
    else
        printf("该场地未被预约");
}

void Search_personname(Appointment *h, char name[])
{
    int i = 0;
    Appointment *p;
    p = h;
    int flag = 0;
    while (p != NULL)
    {

        if (strcmp(p->data.name, name) == 0)
        {
            printf("预约人预约情况\n");
            printf("|%-6s|%-18s|%-15s|%-12s|%-12s|%-12d|\n", p->data.name, p->data.phone_number, p->data.ground, p->data.start_time, p->data.end_time, p->data.day);
            flag = 1;
            p = p->next;
        }
        else
            p = p->next;
        i++;
        if (i == count)
        {
            break;
        }
    }
    if (flag) 
        printf("该预约人已预约场地\n");
    else
        printf("该预约人未预约场地\n");
}

Appointment *deleteAppointinfo(Appointment *h, char name[])
{
    Appointment *p = h;
    Appointment *head = h;
    Appointment *pPrev; 
    if (count == 0)
    {
        printf("未有预约\n");
        return head;
    }
    if (head == NULL)
        printf("未有预约\n");
    else
    {
        p = head;
        while ((p != NULL) && (strcmp(p->data.name, name) != 0))
        {
            pPrev = p;
            p = p->next;
        }
        if (p != NULL)
        {
            if (p == head)
            {
                head = p->next;
            }
            else
                pPrev->next = p->next;
            printf("信息已经删除\n");
            free(p);
        }
        else
            printf("信息已经删除\n");
    }
    return head;
}

void changeAppointinfo(Appointment *h, char name[]) 
{
    struct date s1, s2;
    int flag = 0;
    Appointment *p;
    p = h;
    while (p != NULL)
    {
        if (strcmp(p->data.name, name) == 0)
        {
            printf("请输入修改后的信息\n");
            scanf("%s%s%s%s%s", &p->data.name, &p->data.phone_number, &p->data.ground, &p->data.start_time, &p->data.end_time);
            sscanf(p->data.start_time, "%d-%d-%d", &s1.years, &s1.months, &s1.days);
            sscanf(p->data.end_time, "%d-%d-%d", &s2.years, &s2.months, &s2.days);
            p->data.day = diff(s1, s2);
            printf("信息已修改\n");
            flag = 1;
            break;
        }
        else
            p = p->next;
    }
    if (flag == 0)
        printf("信息未修改\n");
}



int days_date(struct date s) 
{
    int sum=0,i,k; 
    for (i = 0; i < s.years; i++) 
    {
        if (leapYear(i)) 
            sum += 366;
        else
            sum += 365;
    }
    if (leapYear(i))
        days_on_month[2] = 29; 
    else
        days_on_month[2] = 28; 
    for (k = 1; k < s.months; k++)
        sum += days_on_month[k];
    return sum + s.days;
}

int diff(struct date s1, struct date s2) 
{
    return abs(days_date(s1) - days_date(s2));
}
