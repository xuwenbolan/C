#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ����һ����Ʒ�ṹ��
typedef struct sp
{
    char no[12];     // ��Ʒ���
    char name[40];   // ����
    int workload;    // �����
    struct sp *next; // ָ����һ�ڵ��ָ��
} SP;

// ����������������
void ListCreate(SP *L, int n); // ������Ʒ����ڵ�
void LIstSearch(SP *L);        // ������Ʒ��Ϣ
void ListModify(SP *L);        // �޸���Ʒ��Ϣ
void ListInsert(SP *L);        // ������Ʒ��Ϣ
void ListDelete(SP *L);        // ɾ����Ʒ��Ϣ
void Input(SP *p, int i);      // ������Ʒ��Ϣ
void SumSp(SP *L);             // ͳ����Ʒ�Ŀ������
void Sort(SP *L);              // ��ÿ����Ʒ�Ŀ������������
void Menu();                   // ���Ա�������ϵͳ�Ĳ˵�

// ��Ʒ������ϵͳ�����������
int main()
{
    int item, n;                  // item���ڽ�����������n���ڽ����������Ʒ����
    SP *L = NULL;                 // ��ʼ��һ��ͷ�ڵ�
    L = (SP *)malloc(sizeof(SP)); // Ϊͷ�ڵ㿪���ڴ�ռ�
    L->next = NULL;               // ��ͷ�ڵ��ָ�����ÿ�
    do
    {
        Menu(); // �˵�
        printf("��������Ӧ�����֣�������Ӧ�Ĳ���:\n");
        scanf("%d", &item);
        system("cls");
        switch (item)
        {
        case 1:
            printf("��������Ҫ¼�����Ʒ��Ŀ:");
            scanf("%d", &n);
            ListCreate(L, n);
            getchar();
            printf("\n�밴������������˵�\n");
            getchar();
            system("cls");
            break;
        case 2:
            LIstSearch(L); // ������Ʒ��Ϣ
            getchar();
            printf("\n�밴������������˵�\n");
            getchar();
            system("cls");
            break;
        case 3:
            ListModify(L); // �޸���Ʒ�����Ϣ
            getchar();
            printf("\n�밴������������˵�\n");
            getchar();
            system("cls");
            break;
        case 4:
            ListDelete(L); // ɾ����Ʒ��Ϣ
            getchar();
            printf("\n�밴������������˵�\n");
            getchar();
            system("cls");
            break;
        case 5:
            ListInsert(L); // ������Ʒ��Ϣ
            getchar();
            printf("\n�밴������������˵�\n");
            getchar();
            system("cls");
            break;
        case 6:
            SumSp(L);
            getchar();
            printf("\n�밴������������˵�\n");
            getchar();
            system("cls");
            break;
        case 7:
            Sort(L);
            getchar();
            printf("\n�밴������������˵�\n");
            getchar();
            system("cls");
            break;
        case 0: // �˳���Ʒ������ϵͳ
            printf("�����˳���Ʒ������ϵͳ.....");
            exit(0);
        default:
            printf("�������ָ���ȷ������������");
        }
        printf("\n\n");
    } while (item);
    return 0;
}

// ���������������ɵĽڵ���뵽����ı�ͷ
void ListCreate(SP *L, int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        SP *p;
        // �������ɵĽڵ���뵽������
        p = NULL;
        p = (SP *)malloc(sizeof(SP));
        Input(p, i);
        p->next = L->next;
        L->next = p;
    }
    printf("¼��ɹ���");
}

// ������Ʒ�����
void LIstSearch(SP *L)
{
    char n[40];
    SP *p = L->next;
    if (p == NULL)
        printf("����Ϊ�գ��޷����ң�");
    else
    {
        printf("��������Ҫ���ҵ���Ʒ����:");
        scanf("%s", n);
        while (strcmp(p->name, n) != 0)
        {
            p = p->next;
            if (p == NULL)
            {
                printf("û���ҵ������Ϣ\n");
                return;
            }
        }
        printf("%s�Ŀ����Ϊ%d\n", p->name, p->workload);
    }
}

// �޸���Ʒ�Ŀ����
void ListModify(SP *L)
{
    int a;
    char nam[40];
    SP *p = L->next;
    if (p == NULL)
        printf("����Ϊ�գ��޷��޸ģ�");
    else
    {
        printf("���������޸ĵ���Ʒ����:");
        scanf("%s", nam);
        while (strcmp(p->name, nam) != 0)
        {
            p = p->next;
            if (p == NULL)
            {
                printf("û���ҵ������Ϣ\n");
                return;
            }
        }
        printf("���������޸ĺ�Ŀ����:");
        scanf("%d", &p->workload);
        printf("�޸ĳɹ�");
    }
}

// ɾ����Ʒ��Ϣ
void ListDelete(SP *L)
{
    char n[40];
    SP *p = L->next, *pre = L; // ����pָ��ָ��ͷ�ڵ��ָ�򣬶���preָ��ͷ�ڵ㣬preʼ��ָ��p��ǰ���ڵ�
    if (p == NULL)
        printf("����Ϊ�գ��޷�ɾ����");
    else
    {
        printf("��������Ҫɾ������Ʒ����:");
        scanf("%s", n);
        while (strcmp(p->name, n) != 0)
        {
            pre = p;
            p = pre->next;
            if (p == NULL)
            {
                printf("û���ҵ������Ϣ���޷�ɾ��\n");
                return;
            }
        }
        pre->next = p->next;
        free(p);
        printf("ɾ���ɹ�");
    }
}

// ������Ʒ���������Ϣ
void ListInsert(SP *L)
{
    SP *s = NULL; // ����һ���½ڵ�s
    s = (SP *)malloc(sizeof(SP));
    printf("��������Ʒ����Ʒ���:");
    scanf("%s", s->no);
    printf("��������Ʒ������:");
    scanf("%s", s->name);
    printf("��������Ʒ�Ŀ����:");
    scanf("%d", &s->workload);
    s->next = L->next;
    L->next = s;
    printf("����ɹ�!");
}

// ͳ����Ʒ�Ŀ������
void SumSp(SP *L)
{
    int sum = 0;
    SP *p = L->next;
    while (p != NULL)
    {
        sum += p->workload;
        p = p->next;
    }
    printf("��Ʒ�Ŀ������Ϊ%d\n", sum);
}

// ��ÿ����Ʒ�Ŀ������������
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
    printf("��Ʒ�������С����������:\n");
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
// ������Ʒ���������Ϣ
void Input(SP *p, int i)
{
    printf("�������%d����Ʒ����Ʒ���:", i + 1);
    scanf("%s", p->no);
    printf("�������%d����Ʒ������:", i + 1);
    scanf("%s", p->name);
    printf("�������%d����Ʒ�Ŀ����:", i + 1);
    scanf("%d", &p->workload);
}

// ��Ʒ������ϵͳ�Ĳ˵�
void Menu()
{
    printf("\n\n");
    printf("\t\t\t===================��Ʒ������ϵͳ======================\n");
    printf("\t\t\t* ����:���Ĳ�  �༶:�������ѧ�뼼��4��  ѧ��:3122010092   *\n");
    printf("\t\t\t*                                                       *\n");
    printf("\t\t\t*          1>. ¼����Ʒ�����Ϣ                         *\n");
    printf("\t\t\t*          2>. ����ĳ����Ʒ�Ŀ����                     *\n");
    printf("\t\t\t*          3>. �޸�ĳ����Ʒ�Ŀ����                     *\n");
    printf("\t\t\t*          4>. ɾ��ĳ����Ʒ��������Ϣ                 *\n");
    printf("\t\t\t*          5>. ����ĳ����Ʒ�������Ϣ                   *\n");
    printf("\t\t\t*          6>. ͳ����Ʒ�Ŀ������                       *\n");
    printf("\t\t\t*          7>. ��ÿ����Ʒ�Ŀ��������                   *\n");
    printf("\t\t\t*          0>. �˳�����ϵͳ                             *\n");
    printf("\t\t\t*                                        ��ӭʹ�ñ�ϵͳ!*\n");
    printf("\t\t\t========================================================\n");
    printf("\t\t\t����ѡ����س�����ѡ��:                                 \n");
}
