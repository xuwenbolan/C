#include "warehouse.h"

int main()
{
    Goods_read();
    Add_Goods();
    show_Goods();
    return 0;
}

void Add_Gpoint(Goods point) // 添加一个货物节点
{
    G_Point *node = (G_Point *)malloc(sizeof(G_Point));
    node->goods = point;
    if (G_head == NULL)
        node->next = NULL;
    else
        node->next = G_head;
    G_head = node;
}

void Goods_read() // 读取货物文件
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

void Goods_write(Goods temp) // 写入货物文件
{
    FILE *fp = NULL;
    fopen_s(&fp, "Goods_data.txt", "a");
    fprintf(fp, "%s %s %s %s %s %d %f\n", temp.name, temp.date, temp.place, temp.sup_unit, temp.phone, temp.num, temp.price);
    fclose(fp);
}

void show_Goods() // 显示货物
{
    G_Point *temp = G_head;
    printf("—————————————————————————————————————————————————————————\n");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    printf("| %-10s | %-10s | %-25s | %-20s | %-11s | %-8s | %-8s |\n", "货物名称", "入库日期", "入库位置", "供货单位", "厂家电话", "货物数量", "货物价格");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    printf("—————————————————————————————————————————————————————————\n");
    while (temp)
    {
        printf("| %-10s | %-10s | %-25s | %-20s | %-11s | %-8d | %-8.3f |\n", temp->goods.name, temp->goods.date, temp->goods.place, temp->goods.sup_unit, temp->goods.phone, temp->goods.num, temp->goods.price);
        temp = temp->next;
        printf("—————————————————————————————————————————————————————————\n");
    }
}

void Add_Goods() // 添加货物
{
    Goods temp;
    printf("请输入货物名称：\n");
    scanf("%s", temp.name);
    get_time(temp.date);
    printf("请输入入库位置：\n");
    scanf("%s", temp.place);
    printf("请输入供货单位：\n");
    scanf("%s", temp.sup_unit);
    printf("请输入厂家电话：\n");
    scanf("%s", temp.phone);
    printf("请输入货物数量：\n");
    scanf("%d", &temp.num);
    printf("请输入货物价格：\n");
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
    time(&t);           // 获取时间戳。
    lt = localtime(&t); // 转为时间结构。
    sprintf(date,"%d-%d-%d", lt->tm_year + 1900, lt->tm_mon + 1, lt->tm_mday);
    return des;
}
