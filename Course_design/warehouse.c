#include "warehouse.h"

int main()
{
    Goods_read();
    Add_Goods();
    show_Goods();
    return 0;
}

void Add_Gpoint(Goods point) // ���һ������ڵ�
{
    G_Point *node = (G_Point *)malloc(sizeof(G_Point));
    node->goods = point;
    if (G_head == NULL)
        node->next = NULL;
    else
        node->next = G_head;
    G_head = node;
}

void Goods_read() // ��ȡ�����ļ�
{
    FILE *fp = NULL;
    Goods temp;
    fopen_s(&fp, "Goods_data.txt", "r");
    if (fp == NULL)
        fopen_s(&fp, "Goods_data.txt", "w");
    while (fscanf(fp, "%s %s %s %s %s %d %f", temp.name, temp.date, temp.place, temp.sup_unit, temp.phone, &temp.num, &temp.price) != EOF)
    {
        Add_Gpoint(temp);
    }
    fclose(fp);
}

void Goods_write(Goods temp) // д������ļ�
{
    FILE *fp = NULL;
    fopen_s(&fp, "Goods_data.txt", "a");
    fprintf(fp, "%s %s %s %s %s %d %f\n", temp.name, temp.date, temp.place, temp.sup_unit, temp.phone, temp.num, temp.price);
    fclose(fp);
}

void show_Goods() // ��ʾ����
{
    G_Point *temp = G_head;
    printf("������������������������������������������������������������������������������������������������������������������\n");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    printf("| %-10s | %-10s | %-25s | %-20s | %-11s | %-8s | %-8s |\n", "��������", "�������", "���λ��", "������λ", "���ҵ绰", "��������", "����۸�");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    printf("������������������������������������������������������������������������������������������������������������������\n");
    while (temp)
    {
        printf("| %-10s | %-10s | %-25s | %-20s | %-11s | %-8d | %-8.3f |\n", temp->goods.name, temp->goods.date, temp->goods.place, temp->goods.sup_unit, temp->goods.phone, temp->goods.num, temp->goods.price);
        temp = temp->next;
        printf("������������������������������������������������������������������������������������������������������������������\n");
    }
}

void Add_Goods() // ��ӻ���
{
    Goods temp;
    printf("������������ƣ�\n");
    scanf("%s", temp.name);
    get_time(temp.date);
    printf("���������λ�ã�\n");
    scanf("%s", temp.place);
    printf("�����빩����λ��\n");
    scanf("%s", temp.sup_unit);
    printf("�����볧�ҵ绰��\n");
    scanf("%s", temp.phone);
    printf("���������������\n");
    scanf("%d", &temp.num);
    printf("���������۸�\n");
    scanf("%f", &temp.price);
    system("cls");
    Add_Gpoint(temp);
    Goods_write(temp);
}

char* get_time(char *des)
{
    time_t t;
    struct tm *lt;
    char *date=des;
    time(&t);           // ��ȡʱ�����
    lt = localtime(&t); // תΪʱ��ṹ��
    sprintf(date,"%d-%d-%d", lt->tm_year + 1900, lt->tm_mon + 1, lt->tm_mday);
    return des;
}
