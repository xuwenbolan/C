#include "warehouse.h"

int main()
{
    Goods_read();
    Pick_Goods(G_head);
    return 0;
}

void Add_Gpoint(Goods point) // ���һ������ڵ�
{
    G_Point *node = (G_Point *)malloc(sizeof(G_Point));
    node->goods = point;
    node->last = NULL;
    if (G_head == NULL)
        node->next = NULL;
    else
    {
        G_head->last = node;
        node->next = G_head;
    }
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

void Goods_write() // д������ļ�
{
    FILE *fp = NULL;
    G_Point* temp=G_head;
    fopen_s(&fp, "Goods_data.txt", "w");
    while(temp)
    {
        fprintf(fp, "%s %s %s %s %s %d %f\n", temp->goods.name, temp->goods.date, temp->goods.place, temp->goods.sup_unit, temp->goods.phone, temp->goods.num, temp->goods.price);
        temp=temp->next;
    }
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
    printf("������������ƣ�");
    scanf("%s", temp.name);
    if(Find_tar(temp.name)!=NULL)
    {
        printf("��ǰ�����Ѵ��ڣ�");
        printf("qin");//
    }
    else
    {
        get_time(temp.date);
        printf("���������λ�ã�");
        scanf("%s", temp.place);
        printf("�����빩����λ��");
        scanf("%s", temp.sup_unit);
        printf("�����볧�ҵ绰��");
        scanf("%s", temp.phone);
        printf("���������������");
        scanf("%d", &temp.num);
        printf("���������۸�");
        scanf("%f", &temp.price);
        system("cls");
        Add_Gpoint(temp);
        Goods_write();
    }
    
}

char *get_time(char *des)
{
    time_t t;
    struct tm *lt;
    char *date = des;
    time(&t);           // ��ȡʱ�����
    lt = localtime(&t); // תΪʱ��ṹ��
    sprintf(date, "%d-%d-%d", lt->tm_year + 1900, lt->tm_mon + 1, lt->tm_mday);
    return des;
}

G_Point *Find_tar(char *target) // ����Ŀ��
{
    G_Point *temp = G_head;
    while (temp)
    {
        if (strcmp(temp->goods.name, target) == 0)
        {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

void Find_Goods() // ���һ���
{
    char *target;
    printf("��������ҵĻ������ƣ�");
    scanf("%s", target);
    G_Point *temp = Find_tar(target);
    if (temp == NULL)
        printf("��Ǹ��δ���ҵ���%s", target);
    else
    {
        printf("������������������������������������������������������������������������������������������������������������������\n");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
        printf("| %-10s | %-10s | %-25s | %-20s | %-11s | %-8s | %-8s |\n", "��������", "�������", "���λ��", "������λ", "���ҵ绰", "��������", "����۸�");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
        printf("������������������������������������������������������������������������������������������������������������������\n");
        printf("| %-10s | %-10s | %-25s | %-20s | %-11s | %-8d | %-8.3f |\n", temp->goods.name, temp->goods.date, temp->goods.place, temp->goods.sup_unit, temp->goods.phone, temp->goods.num, temp->goods.price);
        printf("������������������������������������������������������������������������������������������������������������������\n");
    }
}

void Pick_Goods(G_Point* temp)
{
    int kind=0;
    while (1)
    {
        system("cls");
        if (GetAsyncKeyState(VK_SPACE))
            break;
        else if (GetAsyncKeyState(VK_UP))
        {
            if (temp->last == NULL)
                printf("�Ѿ��ǵ�һ����Ӵ��\n");
            else
                temp=temp->last;       
        }
        else if (GetAsyncKeyState(VK_DOWN))
        {
            if (temp->next == NULL)
                printf("�Ѿ������һ����Ӵ��\n");
            else
                temp=temp->next;     
        }
        else if(GetAsyncKeyState(VK_LEFT))
        {
            if(kind==0)kind=6;
            else kind--;
        }
        else if(GetAsyncKeyState(VK_RIGHT))
        {
            if(kind==6)kind=0;
            else kind++;
        }
        else if(GetAsyncKeyState(VK_RETURN))Change_Goods(temp,kind);
        printf("\033[36m�������Ҽ����п���!\n");
        printf("�ո���˳�!\033[37m\n");
        printf("������������������������������������������������������������������������������������������������������������������\n");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
        printf("| %-10s | %-10s | %-25s | %-20s | %-11s | %-8s | %-8s |\n", "��������", "�������", "���λ��", "������λ", "���ҵ绰", "��������", "����۸�");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
        printf("������������������������������������������������������������������������������������������������������������������\n");
        if(kind==0)
        printf("| \033[32m%-10s\033[37m | %-10s | %-25s | %-20s | %-11s | %-8d | %-8.3f |\n", temp->goods.name, temp->goods.date, temp->goods.place, temp->goods.sup_unit, temp->goods.phone, temp->goods.num, temp->goods.price);
        else if(kind==1)
        printf("| %-10s | \033[32m%-10s\033[37m | %-25s | %-20s | %-11s | %-8d | %-8.3f |\n", temp->goods.name, temp->goods.date, temp->goods.place, temp->goods.sup_unit, temp->goods.phone, temp->goods.num, temp->goods.price);
        else if(kind==2)
        printf("| %-10s | %-10s | \033[32m%-25s\033[37m | %-20s | %-11s | %-8d | %-8.3f |\n", temp->goods.name, temp->goods.date, temp->goods.place, temp->goods.sup_unit, temp->goods.phone, temp->goods.num, temp->goods.price);
        else if(kind==3)
        printf("| %-10s | %-10s | %-25s | \033[32m%-20s\033[37m | %-11s | %-8d | %-8.3f |\n", temp->goods.name, temp->goods.date, temp->goods.place, temp->goods.sup_unit, temp->goods.phone, temp->goods.num, temp->goods.price);
        else if(kind==4)
        printf("| %-10s | %-10s | %-25s | %-20s | \033[32m%-11s\033[37m | %-8d | %-8.3f |\n", temp->goods.name, temp->goods.date, temp->goods.place, temp->goods.sup_unit, temp->goods.phone, temp->goods.num, temp->goods.price);
        else if(kind==5)
        printf("| %-10s | %-10s | %-25s | %-20s | %-11s | \033[32m%-8d\033[37m | %-8.3f |\n", temp->goods.name, temp->goods.date, temp->goods.place, temp->goods.sup_unit, temp->goods.phone, temp->goods.num, temp->goods.price);
        else if(kind==6)
        printf("| %-10s | %-10s | %-25s | %-20s | %-11s | %-8d | \033[32m%-8.3f\033[37m |\n", temp->goods.name, temp->goods.date, temp->goods.place, temp->goods.sup_unit, temp->goods.phone, temp->goods.num, temp->goods.price);
        printf("������������������������������������������������������������������������������������������������������������������\n");
        system("pause>>nul");
    }
    Goods_write();
}

void Change_Goods(G_Point* temp,int kind)
{
    if(kind==0)
    {
        printf("������������ƣ�");
        scanf("%s",temp->goods.name);
        printf("\033[36m���ĳɹ���\033[37m\n");
    }
    else if(kind==1)
    {
        printf("\033[36m������ڲ��ɸ��ģ�\033[37m\n");
    }
    else if(kind==2)
    {
        printf("���������λ�ã�");
        scanf("%s",temp->goods.place);
        printf("\033[36m���ĳɹ���\033[37m\n");
    }
    else if(kind==3)
    {
        printf("�����빩����λ��");
        scanf("%s",temp->goods.sup_unit);
        printf("\033[36m���ĳɹ���\033[37m\n");
    }
    else if(kind==4)
    {
        printf("�����볧�ҵ绰��");
        scanf("%s",temp->goods.phone);
        printf("\033[36m���ĳɹ���\033[37m\n");
    }
    else if(kind==5)
    {
        printf("���������������");
        scanf("%d",&temp->goods.num);
        printf("\033[36m���ĳɹ���\033[37m\n");
    }
    else if(kind==6)
    {
        printf("���������۸�");
        scanf("%f",&temp->goods.price);
        printf("\033[36m���ĳɹ���\033[37m\n");
    }
    system("pause");
    system("cls");
}
