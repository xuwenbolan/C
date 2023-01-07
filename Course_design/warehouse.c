#include "warehouse.h"

int main()
{
    Goods_read();
    // Add_Goods();
    show_Goods(G_head);
    // Pick_Goods();
    return 0;
}

void Add_Gpoint(Goods point)
{
    G_Point *node = (G_Point *)malloc(sizeof(G_Point));
    node->goods = point;
    node->next = NULL;
    if (G_head == NULL)
    {
        G_head=node;
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
    int kind=7;
    while (1)
    {
        Sleep(25);
        system("cls");
        if (GetAsyncKeyState(VK_SPACE))
            break;
        else if (GetAsyncKeyState(VK_UP))
        {
            if(temp->last!=NULL && temp2 == temp)temp2=temp2->last;
            if (temp->last == NULL)
                printf("已经是第一个了哟！\n");
            else
                temp = temp->last;
        }
        else if (GetAsyncKeyState(VK_DOWN))
        {
            if(temp!=NULL && temp3->last == temp)temp2=temp2->next;         
            if (temp->next == NULL)
                printf("已经是最后一个了哟！\n");
            else
                temp = temp->next;
        }
        else if (GetAsyncKeyState(VK_RETURN) && kind != 7)
        {
            Operate_Menu(temp);
            kind=7;
        }
        if (kind == 7)
            kind = 0;
        printf("\033[36m上下键进行控制!\n");
        printf("空格键退出!\033[37m\n");
        printf("—————————————————————————————————————————————————————————\n");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
        printf("| %-10s | %-10s | %-25s | %-20s | %-11s | %-8s | %-8s |\n", "货物名称", "入库日期", "入库位置", "供货单位", "厂家电话", "货物数量", "货物价格");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
        printf("—————————————————————————————————————————————————————————\n");
        temp3=temp2;
        for(int i=0;i<10;i++)
        {
            if(temp3==temp)
            printf("\033[32m| %-10s | %-10s | %-25s | %-20s | %-11s | %-8d | %-8.3f |\033[37m\n", temp3->goods.name, temp3->goods.date, temp3->goods.place, temp3->goods.sup_unit, temp3->goods.phone, temp3->goods.num, temp3->goods.price);
            else
            printf("| %-10s | %-10s | %-25s | %-20s | %-11s | %-8d | %-8.3f |\n", temp3->goods.name, temp3->goods.date, temp3->goods.place, temp3->goods.sup_unit, temp3->goods.phone, temp3->goods.num, temp3->goods.price);
            printf("—————————————————————————————————————————————————————————\n");
            if(temp3==G_end)break;
            temp3=temp3->next;
        }
        system("pause>>nul");
    }
    
}

void Add_Goods()
{
    Goods temp;
    printf("请输入货物名称：");
    scanf("%s", temp.name);
    if (Find_tar(temp.name) != NULL)
    {
        printf("当前货物已存在！");
        Find_Goods(temp.name);
    }
    else
    {
        get_time(temp.date);
        printf("请输入入库位置：");
        scanf("%s", temp.place);
        printf("请输入供货单位：");
        scanf("%s", temp.sup_unit);
        printf("请输入厂家电话：");
        scanf("%s", temp.phone);
        printf("请输入货物数量：");
        scanf("%d", &temp.num);
        printf("请输入货物价格：");
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
    time(&t);           // 获取时间戳。
    lt = localtime(&t); // 转为时间结构。
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
            printf("\033[36m发现货物\033[37m\n\n");
            printf("————————————————————\n");
            if (kind == 0)
                printf("|        \033[32m返回\033[37m       |       查看       |\n");
            else
                printf("|        返回       |       \033[32m查看\033[37m       |\n");
            printf("————————————————————\n");
            system("pause>>nul");
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
        Sleep(25);
        system("cls");
        if (GetAsyncKeyState(VK_SPACE))
            break;
        else if (GetAsyncKeyState(VK_UP))
        {
            if (temp->last == NULL)
                printf("已经是第一个了哟！\n");
            else
                temp = temp->last;
        }
        else if (GetAsyncKeyState(VK_DOWN))
        {
            if (temp->next == NULL)
                printf("已经是最后一个了哟！\n");
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
        printf("\033[36m上下左右键进行控制!\n");
        printf("空格键退出!\033[37m\n");
        printf("—————————————————————————————————————————————————————————\n");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
        printf("| %-10s | %-10s | %-25s | %-20s | %-11s | %-8s | %-8s |\n", "货物名称", "入库日期", "入库位置", "供货单位", "厂家电话", "货物数量", "货物价格");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
        printf("—————————————————————————————————————————————————————————\n");
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
        printf("—————————————————————————————————————————————————————————\n");
        system("pause>>nul");
    }
    Goods_write();
}

void Change_Goods(G_Point *temp, int kind)
{
    if (kind == 0)
    {
        printf("请输入货物名称：");
        scanf("%s", temp->goods.name);
        printf("\033[36m更改成功！\033[37m\n");
    }
    else if (kind == 1)
    {
        printf("\033[36m入库日期不可更改！\033[37m\n");
    }
    else if (kind == 2)
    {
        printf("请输入入库位置：");
        scanf("%s", temp->goods.place);
        printf("\033[36m更改成功！\033[37m\n");
    }
    else if (kind == 3)
    {
        printf("请输入供货单位：");
        scanf("%s", temp->goods.sup_unit);
        printf("\033[36m更改成功！\033[37m\n");
    }
    else if (kind == 4)
    {
        printf("请输入厂家电话：");
        scanf("%s", temp->goods.phone);
        printf("\033[36m更改成功！\033[37m\n");
    }
    else if (kind == 5)
    {
        printf("请输入货物数量：");
        scanf("%d", &temp->goods.num);
        printf("\033[36m更改成功！\033[37m\n");
    }
    else if (kind == 6)
    {
        printf("请输入货物价格：");
        scanf("%f", &temp->goods.price);
        printf("\033[36m更改成功！\033[37m\n");
    }
    system("pause");
    system("cls");
}

void Operate_Menu(G_Point *node)
{
    int kind = 7;
    while (1)
    {
        Sleep(25);
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
            Select(kind,node);
            break;
        }
        if (kind == 7)
            kind = 0;
        printf("\033[36m左右键进行控制!\n");
        printf("空格键退出!\033[37m\n");
        printf("—————————————————————————————————————————————————————————\n");
        if (kind == 0)
            printf("| \033[32m%-10s\033[37m | %-10s | %-25s | %-20s | %-11s | %-8s | %-8s |\n","插入", "入库", "出库", "更改信息", "删除", "查看", "排序");
        else if (kind == 1)
            printf("| %-10s | \033[32m%-10s\033[37m | %-25s | %-20s | %-11s | %-8s | %-8s |\n","插入", "入库", "出库", "更改信息", "删除", "查看", "排序");
        else if (kind == 2)
            printf("| %-10s | %-10s | \033[32m%-25s\033[37m | %-20s | %-11s | %-8s | %-8s |\n","插入", "入库", "出库", "更改信息", "删除", "查看", "排序");
        else if (kind == 3)
            printf("| %-10s | %-10s | %-25s | \033[32m%-20s\033[37m | %-11s | %-8s | %-8s |\n","插入", "入库", "出库", "更改信息", "删除", "查看", "排序");
        else if (kind == 4)
            printf("| %-10s | %-10s | %-25s | %-20s | \033[32m%-11s\033[37m | %-8s | %-8s |\n","插入", "入库", "出库", "更改信息", "删除", "查看", "排序");
        else if (kind == 5)
            printf("| %-10s | %-10s | %-25s | %-20s | %-11s | \033[32m%-8s\033[37m | %-8s |\n","插入", "入库", "出库", "更改信息", "删除", "查看", "排序");
        else if (kind == 6)
            printf("| %-10s | %-10s | %-25s | %-20s | %-11s | %-8s | \033[32m%-8.3s\033[37m |\n","插入", "入库", "出库", "更改信息", "删除", "查看", "排序");
        printf("—————————————————————————————————————————————————————————\n");
        system("pause>>nul");
    }
}

void Select(int kind,G_Point* node)
{
    int num;
    if(kind==insert_goods)
    {
        char *tar;
        printf("请输入查找的货物：\n");
        scanf("%s",tar);
        if(Find_Goods(tar)==0)printf("抱歉未查找到货物\n");
    }
    else if(kind==input_goods)
    {
        num=0;
        printf("请输入存入的数量：\n");
        scanf("%d",&num);
        node->goods.num+=num;
    }
    else if(kind==out_goods)
    {
        num=0;
        printf("请输入取出的数量：\n");
        scanf("%d",&num);
        if(num>node->goods.num)printf("取出的数量超过库存的数量\n");
        else node->goods.num-=num;
    }
    else if(kind==pick_goods)Pick_Goods(node);
    else if(kind==delete_goods)Delete_Gpoint(node);
    else if(kind==view_goods)
    {

    }
    else Sort_Goods();
}

void Sort_Goods()
{

}