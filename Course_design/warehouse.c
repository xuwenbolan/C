#include "warehouse.h"

int main()
{
    Begin();
    return 0;
}

void Add_Gpoint(Goods point)
{
    G_Point *node = (G_Point *)malloc(sizeof(G_Point));
    node->goods = point;
    node->next = NULL;
    if (G_head == NULL)
    {
        G_head = node;
        node->last = NULL;
    }
    else
    {
        G_end->next = node;
        node->last = G_end;
    }
    G_end = node;
}

void Delete_Gpoint(G_Point *node)
{
    node->next->last = node->last;
    node->last->next = node->next;
    free(node);
}

void Admin_read()
{
    FILE *fp = NULL;
    Admin temp;
    fopen_s(&fp, "Admin_data.txt", "r");
    if (fp == NULL)
        fopen_s(&fp, "Admin_data.txt", "w");
    while (fscanf(fp, "%s %s %s %s", temp.name, temp.phone, temp.password, temp.unit) != EOF)
    {
        Add_Apoint(temp);
    }
    fclose(fp);
}

void Add_Apoint(Admin point)
{
    A_Point *node = (A_Point *)malloc(sizeof(A_Point));
    node->admin = point;
    node->next = NULL;
    if (A_head == NULL)
    {
        A_head = node;
        node->last = NULL;
    }
    else
    {
        A_end->next = node;
        node->last = A_end;
    }
    A_end = node;
}

A_Point *Find_Admin(char *target)
{
    A_Point *temp = A_head;
    while (temp)
    {
        if (strcmp(temp->admin.name, target) == 0)
        {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

void Goods_read()
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

void Goods_write()
{
    FILE *fp = NULL;
    G_Point *temp = G_head;
    fopen_s(&fp, "Goods_data.txt", "w");
    while (temp)
    {
        fprintf(fp, "%s %s %s %s %s %d %f\n", temp->goods.name, temp->goods.date, temp->goods.place, temp->goods.sup_unit, temp->goods.phone, temp->goods.num, temp->goods.price);
        temp = temp->next;
    }
    fclose(fp);
}

void show_Goods(G_Point *node)
{
    G_Point *temp = node;
    G_Point *temp2 = temp;
    G_Point *temp3 = temp;
    int kind = 7;
    HideCursor();
    while (1)
    {
        if (GetAsyncKeyState(VK_TAB))
        {
            system("cls");
            Add_Gpoint(Add_Goods());
            kind = 7;
        }
        else if (GetAsyncKeyState(VK_SPACE))
            break;
        else if (GetAsyncKeyState(VK_UP))
        {
            if (temp->last != NULL && temp2 == temp)
                temp2 = temp2->last;
            if (temp->last == NULL)
            {
                printf("\033[31m�Ѿ��ǵ�һ����Ӵ��\033[37m\n");
                Beep(1000, 300);
                Beep(1000, 300);
            }

            else
                temp = temp->last;
        }
        else if (GetAsyncKeyState(VK_DOWN))
        {
            if (temp != NULL && temp3->last == temp)
                temp2 = temp2->next;
            if (temp->next == NULL)
            {
                printf("\033[31m�Ѿ������һ����Ӵ��\033[37m\n");
                Beep(1000, 300);
                Beep(1000, 300);
            }
            else
                temp = temp->next;
        }
        else if (GetAsyncKeyState(VK_RETURN) && kind != 7)
        {
            if (temp == G_head)
            {
                G_Point *p = temp->next;
                Operate_Menu(temp);
                temp = p->last;
            }
            else
            {
                G_Point *p = temp->last;
                Operate_Menu(temp);
                temp = p->next;
            }
            kind = 7;
        }
        system("cls");
        if (kind == 7)
            kind = 0;
        printf("\033[36m���ϡ��¡�\tѡ��\n");
        printf("��Enter��\tѡ�в���\n");
        printf("��TAB��\t��ӻ���\n");
        printf("���ո�\t�˳�\033[37m\n");
        printf("������������������������������������������������������������������������������������������������������������������\n");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
        printf("| %-10s | %-10s | %-25s | %-20s | %-11s | %-8s | %-8s |\n", "��������", "�������", "���λ��", "������λ", "���ҵ绰", "��������", "����۸�");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
        printf("������������������������������������������������������������������������������������������������������������������\n");
        temp3 = temp2;
        for (int i = 0; i < 10; i++)
        {
            if (temp3 == temp)
                printf("\033[32m| %-10s | %-10s | %-25s | %-20s | %-11s | %-8d | %-8.3f |\033[37m\n", temp3->goods.name, temp3->goods.date, temp3->goods.place, temp3->goods.sup_unit, temp3->goods.phone, temp3->goods.num, temp3->goods.price);
            else
                printf("| %-10s | %-10s | %-25s | %-20s | %-11s | %-8d | %-8.3f |\n", temp3->goods.name, temp3->goods.date, temp3->goods.place, temp3->goods.sup_unit, temp3->goods.phone, temp3->goods.num, temp3->goods.price);
            printf("������������������������������������������������������������������������������������������������������������������\n");
            if (temp3 == G_end)
                break;
            temp3 = temp3->next;
        }
        system("pause>>nul");
        Beep(800, 400);
    }
    Goods_write();
}

Goods Add_Goods()
{
    printf("\n");
    Goods temp;
    printf("������������ƣ�");
    scanf("%s", temp.name);
    if (Find_tar(temp.name) != NULL)
    {
        printf("��ǰ�����Ѵ��ڣ�");
        Find_Goods(temp.name);
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
        return temp;
    }
    system("cls");
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

G_Point *Find_tar(char *target)
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

int Find_Goods(char *target)
{
    G_Point *temp = Find_tar(target);
    if (temp == NULL)
        return 0;
    else
    {
        int kind = 3;
        system("cls");
        while (1)
        {
            if (GetAsyncKeyState(VK_LEFT))
            {
                if (kind == 0)
                    kind = 1;
                else
                    kind = 0;
            }
            else if (GetAsyncKeyState(VK_RIGHT))
            {
                if (kind == 0)
                    kind = 1;
                else
                    kind = 0;
            }
            else if (GetAsyncKeyState(VK_RETURN) && kind != 3)
            {
                if (kind == 1)
                    show_Goods(temp);
                break;
            }
            if (kind == 3)
                kind = 0;
            printf("\033[36m���ֻ���\033[37m\n\n");
            printf("����������������������������������������\n");
            if (kind == 0)
                printf("|        \033[32m����\033[37m       |       ����       |\n");
            else
                printf("|        ����       |       \033[32m����\033[37m       |\n");
            printf("����������������������������������������\n");
            system("pause>>nul");
            Beep(800, 400);
            system("cls");
        }
        return 1;
    }
}

void Pick_Goods(G_Point *temp)
{
    int kind = 7;
    while (1)
    {
        Sleep(100);
        system("cls");
        if (GetAsyncKeyState(VK_SPACE))
            break;
        else if (GetAsyncKeyState(VK_UP))
        {
            if (temp->last == NULL)
                printf("�Ѿ��ǵ�һ����Ӵ��\n");
            else
                temp = temp->last;
        }
        else if (GetAsyncKeyState(VK_DOWN))
        {
            if (temp->next == NULL)
                printf("�Ѿ������һ����Ӵ��\n");
            else
                temp = temp->next;
        }
        else if (GetAsyncKeyState(VK_LEFT))
        {
            if (kind == 0)
                kind = 6;
            else
                kind--;
        }
        else if (GetAsyncKeyState(VK_RIGHT))
        {
            if (kind == 6)
                kind = 0;
            else
                kind++;
        }
        else if (GetAsyncKeyState(VK_RETURN) && kind != 7)
            Change_Goods(temp, kind);
        if (kind == 7)
            kind = 0;
        printf("\033[36m���ϡ��¡����ҡ�\tѡ��\n");
        printf("��Enter��\tѡ�в���\n");
        printf("���ո�\t�˳�!\033[37m\n");
        printf("������������������������������������������������������������������������������������������������������������������\n");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
        printf("| %-10s | %-10s | %-25s | %-20s | %-11s | %-8s | %-8s |\n", "��������", "�������", "���λ��", "������λ", "���ҵ绰", "��������", "����۸�");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
        printf("������������������������������������������������������������������������������������������������������������������\n");
        if (kind == 0)
            printf("| \033[32m%-10s\033[37m | %-10s | %-25s | %-20s | %-11s | %-8d | %-8.3f |\n", temp->goods.name, temp->goods.date, temp->goods.place, temp->goods.sup_unit, temp->goods.phone, temp->goods.num, temp->goods.price);
        else if (kind == 1)
            printf("| %-10s | \033[32m%-10s\033[37m | %-25s | %-20s | %-11s | %-8d | %-8.3f |\n", temp->goods.name, temp->goods.date, temp->goods.place, temp->goods.sup_unit, temp->goods.phone, temp->goods.num, temp->goods.price);
        else if (kind == 2)
            printf("| %-10s | %-10s | \033[32m%-25s\033[37m | %-20s | %-11s | %-8d | %-8.3f |\n", temp->goods.name, temp->goods.date, temp->goods.place, temp->goods.sup_unit, temp->goods.phone, temp->goods.num, temp->goods.price);
        else if (kind == 3)
            printf("| %-10s | %-10s | %-25s | \033[32m%-20s\033[37m | %-11s | %-8d | %-8.3f |\n", temp->goods.name, temp->goods.date, temp->goods.place, temp->goods.sup_unit, temp->goods.phone, temp->goods.num, temp->goods.price);
        else if (kind == 4)
            printf("| %-10s | %-10s | %-25s | %-20s | \033[32m%-11s\033[37m | %-8d | %-8.3f |\n", temp->goods.name, temp->goods.date, temp->goods.place, temp->goods.sup_unit, temp->goods.phone, temp->goods.num, temp->goods.price);
        else if (kind == 5)
            printf("| %-10s | %-10s | %-25s | %-20s | %-11s | \033[32m%-8d\033[37m | %-8.3f |\n", temp->goods.name, temp->goods.date, temp->goods.place, temp->goods.sup_unit, temp->goods.phone, temp->goods.num, temp->goods.price);
        else if (kind == 6)
            printf("| %-10s | %-10s | %-25s | %-20s | %-11s | %-8d | \033[32m%-8.3f\033[37m |\n", temp->goods.name, temp->goods.date, temp->goods.place, temp->goods.sup_unit, temp->goods.phone, temp->goods.num, temp->goods.price);
        printf("������������������������������������������������������������������������������������������������������������������\n");
        system("pause>>nul");
        Beep(800, 400);
    }
    Goods_write();
}

void Change_Goods(G_Point *temp, int kind)
{
    if (kind == 0)
    {
        printf("������������ƣ�");
        scanf("%s", temp->goods.name);
        printf("\033[36m���ĳɹ���\033[37m\n");
    }
    else if (kind == 1)
    {
        printf("\033[36m������ڲ��ɸ��ģ�\033[37m\n");
    }
    else if (kind == 2)
    {
        printf("���������λ�ã�");
        scanf("%s", temp->goods.place);
        printf("\033[36m���ĳɹ���\033[37m\n");
    }
    else if (kind == 3)
    {
        printf("�����빩����λ��");
        scanf("%s", temp->goods.sup_unit);
        printf("\033[36m���ĳɹ���\033[37m\n");
    }
    else if (kind == 4)
    {
        printf("�����볧�ҵ绰��");
        scanf("%s", temp->goods.phone);
        printf("\033[36m���ĳɹ���\033[37m\n");
    }
    else if (kind == 5)
    {
        printf("���������������");
        scanf("%d", &temp->goods.num);
        printf("\033[36m���ĳɹ���\033[37m\n");
    }
    else if (kind == 6)
    {
        printf("���������۸�");
        scanf("%f", &temp->goods.price);
        printf("\033[36m���ĳɹ���\033[37m\n");
    }
    system("pause");
    system("cls");
}

void Operate_Menu(G_Point *node)
{
    int kind = 7;
    while (1)
    {
        Sleep(100);
        system("cls");
        if (GetAsyncKeyState(VK_SPACE))
            break;
        else if (GetAsyncKeyState(VK_LEFT))
        {
            if (kind == 0)
                kind = 6;
            else
                kind--;
        }
        else if (GetAsyncKeyState(VK_RIGHT))
        {
            if (kind == 6)
                kind = 0;
            else
                kind++;
        }
        else if (GetAsyncKeyState(VK_RETURN) && kind != 7)
        {
            Select(kind, node);
            break;
        }
        if (kind == 7)
            kind = 0;
        printf("\033[36m�����ҡ�\tѡ��\n");
        printf("��Enter��\tѡ�в���\n");
        printf("���ո�\t�˳�!\033[37m\n");
        printf("������������������������������������������������������������������������������������������������������������������\n");
        if (kind == 0)
            printf("| \033[32m%-10s\033[37m | %-10s | %-25s | %-20s | %-11s | %-8s | %-8s |\n", "�����»���", "���", "����", "������Ϣ", "ɾ��", "����", "����");
        else if (kind == 1)
            printf("| %-10s | \033[32m%-10s\033[37m | %-25s | %-20s | %-11s | %-8s | %-8s |\n", "�����»���", "���", "����", "������Ϣ", "ɾ��", "����", "����");
        else if (kind == 2)
            printf("| %-10s | %-10s | \033[32m%-25s\033[37m | %-20s | %-11s | %-8s | %-8s |\n", "�����»���", "���", "����", "������Ϣ", "ɾ��", "����", "����");
        else if (kind == 3)
            printf("| %-10s | %-10s | %-25s | \033[32m%-20s\033[37m | %-11s | %-8s | %-8s |\n", "�����»���", "���", "����", "������Ϣ", "ɾ��", "����", "����");
        else if (kind == 4)
            printf("| %-10s | %-10s | %-25s | %-20s | \033[32m%-11s\033[37m | %-8s | %-8s |\n", "�����»���", "���", "����", "������Ϣ", "ɾ��", "����", "����");
        else if (kind == 5)
            printf("| %-10s | %-10s | %-25s | %-20s | %-11s | \033[32m%-8s\033[37m | %-8s |\n", "�����»���", "���", "����", "������Ϣ", "ɾ��", "����", "����");
        else if (kind == 6)
            printf("| %-10s | %-10s | %-25s | %-20s | %-11s | %-8s | \033[32m%-8s\033[37m |\n", "�����»���", "���", "����", "������Ϣ", "ɾ��", "����", "����");
        printf("������������������������������������������������������������������������������������������������������������������\n");
        system("pause>>nul");
        Beep(800, 400);
    }
}

void Select(int kind, G_Point *node)
{
    int num;
    if (kind == insert_goods)
    {
        Goods temp = Add_Goods();
        Insert_Point(node, temp);
    }
    else if (kind == input_goods)
    {
        num = 0;
        printf("��ǰ%s�Ŀ����Ϊ��%d\n", node->goods.name, node->goods.num);
        printf("����������������\n");
        scanf("%d", &num);
        node->goods.num += num;
        printf("����%s�Ŀ����Ϊ��%d\n", node->goods.name, node->goods.num);
        system("pause>>nul");
        system("cls");
    }
    else if (kind == out_goods)
    {
        num = 0;
        printf("��ǰ%s�Ŀ����Ϊ��%d\n", node->goods.name, node->goods.num);
        printf("������ȡ����������\n");
        scanf("%d", &num);
        if (num > node->goods.num)
            printf("ȡ��������������������\n");
        else
            node->goods.num -= num;
        printf("����%s�Ŀ����Ϊ��%d\n", node->goods.name, node->goods.num);
        system("pause>>nul");
        system("cls");
    }
    else if (kind == pick_goods)
        Pick_Goods(node);
    else if (kind == delete_goods)
        Delete_Gpoint(node);
    else if (kind == view_goods)
    {
        char name[20] = {0};
        printf("������Ҫ���ҵĻ�Ʒ��\n");
        scanf("%s", name);
        Find_Goods(name);
    }
    else if (kind == sort_goods)
        Sort_Goods();
}

void Insert_Point(G_Point *front, Goods temp)
{
    G_Point *node = (G_Point *)malloc(sizeof(G_Point));
    node->goods = temp;
    node->last = front;
    node->next = front->next;
    if (front == G_end)
        G_end = node;
    else
        front->next->last = node;
    front->next = node;
}

void Change_point(G_Point *change1, G_Point *change2)
{
    if(change1->last!=NULL)change1->last->next=change2;
    if(change2->next!=NULL)change2->next->last=change1;
    change1->next = change2->next;
    change2->next = change1;
    change2->last = change1->last;
    change1->last = change2;
    if(change2->last==NULL)G_head=change2;
}

void Sort_Goods()
{
    int kind = 3;
    system("cls");
    while (1)
    {
        if (GetAsyncKeyState(VK_LEFT))
        {
            if (kind == 0)
                kind = 1;
            else
                kind = 0;
        }
        else if (GetAsyncKeyState(VK_RIGHT))
        {
            if (kind == 0)
                kind = 1;
            else
                kind = 0;
        }
        else if (GetAsyncKeyState(VK_RETURN) && kind != 3)
            break;
        if (kind == 3)
            kind = 0;
        printf("\033[36m��ѡ���������\033[37m\n\n");
        printf("����������������������������������������\n");
        if (kind == 0)
            printf("|      \033[32m��������\033[37m      |     ����۸�     |\n");
        else
            printf("|      ��������      |     \033[32m����۸�\033[37m     |\n");
        printf("����������������������������������������\n");
        system("pause>>nul");
        Beep(800, 400);
        system("cls");
    }
    int a, i, cou = 0;
    G_Point *p, *q, *tail,*head;
    p = G_head;
    if (G_head->next != NULL)
    {
        printf("����Ŵ�С��������\n");
        while (p->next != NULL) // ��������
        {
            cou++;
            p = p->next;
        }
        for (i = 0; i < cou - 1; i++)
        {
            a = cou - i - 1; // ��ѭ������
            q = G_head->next;      // qָ���һ�����
            p = q->next;     // pָ��p��һ�����
            tail = G_head;
            while (a--) // ��ѭ��
            {
                if (q->goods.num > p->goods.num && kind == 0)
                {
                    Change_point(q, p);
                    tail->next=p;
                }
                else if (q->goods.price > p->goods.price && kind == 1)
                {
                    Change_point(q, p);
                    tail->next=p;
                }
                if(q->next==NULL)G_end=q;
                if(tail->last==NULL)G_head=tail;
                tail = tail->next;
                q = tail->next;
                p = q->next;
            }
        }
        printf("����ɹ�\n");
    }
    else
    {
        printf("�޻�����Ϣ\n");
    }
}
// ��Ļ120 40
void Begin()
{
    HideCursor();
    gotoxy(50, 18);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    printf("��ӭ��¼�ֿ����ϵͳ��");
    gotoxy(55, 20);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    printf("���ڽ���ϵͳ");
    for (int i = 0; i < 5; i++)
    {
        gotoxy(60, 22);
        printf("|");
        Sleep(100);
        gotoxy(60, 22);
        printf("/");
        Sleep(100);
        gotoxy(60, 22);
        printf("-");
        Sleep(100);
        gotoxy(60, 22);
        printf("\\");
        Sleep(100);
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    system("cls");
    Sign_in();
}

void Sign_in()
{
    Admin_read();
    char name[10] = {0};
    char password[20] = {0};
    A_Point *admin;
    while (1)
    {
        for (int i = 0; i < 9; i++)
        {
            gotoxy(40, i);
            printf("|");
        }
        for (int i = 0; i < 9; i++)
        {
            gotoxy(69, i);
            printf("|");
        }
        gotoxy(40, 0);
        for (int i = 0; i < 30; i++)
            printf("-");
        gotoxy(48, 1);
        printf("����Ա��¼����");
        gotoxy(40, 3);
        for (int i = 0; i < 30; i++)
            printf("-");
        gotoxy(53, 4);
        printf("�û���");
        gotoxy(40, 6);
        for (int i = 0; i < 30; i++)
            printf("-");
        gotoxy(53, 7);
        printf("����");
        gotoxy(40, 9);
        for (int i = 0; i < 30; i++)
            printf("-");

        gotoxy(41, 5);
        scanf("%s", name);
        admin = Find_Admin(name);
        if (admin == NULL)
        {
            gotoxy(52, 11);
            printf("���û��������ڣ�");
            system("pause");
            system("cls");
            continue;
        }
        gotoxy(41, 8);
        scanf("%s", password);
        if (strcmp(admin->admin.password, password) == 0)
            break;
        else
        {
            gotoxy(52, 11);
            printf("�������\n");
            system("pause");
            system("cls");
            continue;
        }
    }
    Goods_read();
    show_Goods(G_head);
}

void HideCursor()
{
    HANDLE fd = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cinfo;
    cinfo.bVisible = 0;
    cinfo.dwSize = 1;
    SetConsoleCursorInfo(fd, &cinfo);
}

void gotoxy(int x, int y)
{
    COORD pos = {x, y};
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE); // ��ȡ��׼����豸���
    SetConsoleCursorPosition(hOut, pos);           // ���������ֱ���ָ���ĸ����壬����λ��
}