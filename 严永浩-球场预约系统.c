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
    printf("��������Ӧ�����֣�������Ӧ�Ĳ���:\n");
    scanf("%d", &command);
    printf("\n");
    while (1) 
    {
        switch (command)
        {
        case 1:
        {
            printf("��������Ҫ¼���ԤԼ��Ϣ��Ŀ:");
            scanf("%d", &count);
            printf("ԤԼ��Ϣ��Ŀ��%d\n", count);
        };
        break;
        case 2:
        {
            h = createClass(count);
            printf("�����򳡰�����Ϣ");
        };
        break;
        case 3:
        {
            showAppointinfo(h);
            printf("��ʾ�򳡰�����Ϣ");
        };
        break;
        case 4:
        {
            printf("��������Ҫ�����ĳ���\n");
            scanf("%s", &name);
            Search_Ground(h, name);
        };
        break;
        case 5:
        {
            printf("��������Ҫ������ԤԼ������\n");
            scanf("%s", &name);
            Search_personname(h, name);
        };
        break;
        case 6:
            printf("��������ɾ����ԤԼ����Ϣ\n");
            scanf("%s", &name);
            h = deleteAppointinfo(h, name);
            break;
        case 7:
        {
            printf("��������Ҫ�޸ĵ�ԤԼ����Ϣ\n");
            scanf("%s", &name);
            changeAppointinfo(h, name); 
        };
        break;
        case 0:
            exit(0); 
        }
        printf("���������");
        getch();       
        system("cls"); 
        showMenu();
        printf("��������Ӧ�����֣�������Ӧ�Ĳ���:\n");
        scanf("%d", &command);
    }

    system("pause");
    return 0;
}
void showMenu()
{
    printf("\t\t\t       ---------����ϢԤԼ����----------               \n");
    printf("\t\t\t*          ������ 3122010093   2022��4��                *\n");
    printf("\t\t\t*          1>. ����¼���ԤԼ��Ϣ��Ŀ                   *\n");
    printf("\t\t\t*          2>. �����򳡰�����Ϣ                         *\n");
    printf("\t\t\t*          3>. ��ʾ�򳡰�����Ϣ                         *\n");
    printf("\t\t\t*          4>. ��������ԤԼ���                         *\n");
    printf("\t\t\t*          5>. ������ԤԼ������                         *\n");
    printf("\t\t\t*          6>. ɾ��ԤԼ��Ϣ                             *\n");
    printf("\t\t\t*          7>. ������Ҫ�޸ĵ�ԤԼ����Ϣ                 *\n");
    printf("\t\t\t*          0>. �˳�����ϵͳ                             *\n");
    printf("\t\t\t*              ��ӭʹ�ñ�ϵͳ!                          *\n");
    printf("\t\t\t========================================================\n"); 
    printf("\t\t\t����ѡ����س�����ѡ��:                                 \n");
}

Appointment *createClass(int n)
{
    struct date s1, s2;
    Appointment *p, *q, *h;
    int i;
    for (i = 0; i < n; i++)
    {
        p = (Appointment *)malloc(sizeof(Appointment));
        printf("����ԤԼ������ ԤԼ�绰 ԤԼ���� ԤԼ��ʼʱ�� ԤԼ����ʱ��\n");
        printf("�����%d��ԤԼ��Ϣ:\n", i + 1);
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
    printf("�򳡰�����Ϣ\n");
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
            printf("�ó��ص�ԤԼ���\n");
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
        printf("�ó����ѱ�ԤԼ");
    else
        printf("�ó���δ��ԤԼ");
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
            printf("ԤԼ��ԤԼ���\n");
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
        printf("��ԤԼ����ԤԼ����\n");
    else
        printf("��ԤԼ��δԤԼ����\n");
}

Appointment *deleteAppointinfo(Appointment *h, char name[])
{
    Appointment *p = h;
    Appointment *head = h;
    Appointment *pPrev; 
    if (count == 0)
    {
        printf("δ��ԤԼ\n");
        return head;
    }
    if (head == NULL)
        printf("δ��ԤԼ\n");
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
            printf("��Ϣ�Ѿ�ɾ��\n");
            free(p);
        }
        else
            printf("��Ϣ�Ѿ�ɾ��\n");
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
            printf("�������޸ĺ����Ϣ\n");
            scanf("%s%s%s%s%s", &p->data.name, &p->data.phone_number, &p->data.ground, &p->data.start_time, &p->data.end_time);
            sscanf(p->data.start_time, "%d-%d-%d", &s1.years, &s1.months, &s1.days);
            sscanf(p->data.end_time, "%d-%d-%d", &s2.years, &s2.months, &s2.days);
            p->data.day = diff(s1, s2);
            printf("��Ϣ���޸�\n");
            flag = 1;
            break;
        }
        else
            p = p->next;
    }
    if (flag == 0)
        printf("��Ϣδ�޸�\n");
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
