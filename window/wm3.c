#include <iostream>
#include <fstream>
#include <string.h>
#include <stdio.h>
#include <conio.h> //用getch();
using namespace std;

class Goods
{
public:
    Goods()
    {
    }
    int kind;
    char name[20];
    char Id[20];

    float price;

    int amount;
    Goods *Next;
    friend ostream &operator<<(ostream &out, Goods &obj)
    {
        out << obj.Id << obj.name << obj.amount << obj.kind;
    }
    friend istream &operator>>(istream &in, Goods &obj)
    {
        in >> obj.Id >> obj.name >> obj.amount >> obj.kind;
    }
    void InputAll()
    {

        InputName();
        InputKind();
        InputID();
        InputOther();
    }
    void InputKind()
    {
        cout << "\t\t请选择种类：";
        cin >> kind;
    }
    void InputName()
    {
        cout << "\t\t请输入商品的名称：";
        cin >> name;
    }
    void InputID()
    {
        cout << "\t\t请输入商品的编号：";
        cin >> Id;
    }
    void InputBuyprice()
    {
        cout << "\t\t请输入商品单价：";
        cin >> price;
    }

    void InputAmount()
    {
        cout << "\t\t请输入商品库存：";
        cin >> amount;
    }
    void InputOther()
    {
        cout << "\t\t请输入商品价格：";
        cin >> price;
        cout << "\t\t请输入存货数量：";
        cin >> amount;
    }
    void ReadFile(istream &in)
    {
        in >> name >> kind >> Id >> price >> amount;
    }
    void Show()
    {

        cout << "商品名: " << name << endl
             << "种类:" << kind << endl
             << "编号: " << Id << endl
             << "价格 " << price << endl
             << "商品库存: " << amount << endl
             << endl
             << endl;
    }
};

class Goodsmanager : public Goods
{
public:
    Goodsmanager();
    ~Goodsmanager();
    void showMenu(int n);
    void Find();
    void Save();
    void ModifyItem();
    void RemoveItem();
    void Swap(Goods *, Goods *);
    void Sort();
    void delgoods();
    // void Chack();
    int ListCount();
    void Display()
    {
        system("cls");
        i = 0;
        for (Goods *p = Head->Next; p != End; p = p->Next)
        {
            p->Show();
            i++;
        }
        cout << "共有" << i << "个商品"
             << "\n"
             << endl;
        cout << "输入任意字符！继续……";
        getch();
    }
    void AddItem() // 从键盘输入商品信息
    {
        system("cls");
        End->InputName();
        showMenu(1);
        End->InputKind();
        do
        {
            End->InputID();

        } while (FindID(End->Id));

        End->InputOther();

        End->Next = new Goods;
        End = End->Next;
        cout << "添加成功!" << endl;
        Save();
        cout << "输入任意字符！继续……";
        getch();
    }

private:
    Goods *Head, *End;
    int i;
    ifstream in;
    ofstream out;
    Goods *FindItem(char *name)
    {
        for (Goods *p = Head; p->Next != End; p = p->Next) // 匹配成功则返回上一个指针，不成功就返回空
            if (!strcmp(p->Next->name, name))
                return p;
        return NULL;
    }
    Goods *FindID(char *Id)
    {
        for (Goods *p = Head; p->Next != End; p = p->Next) // 匹配成功则返回上一个指针，不成功就返回空
            if (!strcmp(p->Next->Id, Id))
                return p;
        return NULL;
    }
};

void Goodsmanager::Swap(Goods *p1, Goods *p2) // 交换两个商品的数据
{
    Goods *temp = new Goods;
    strcpy(temp->name, p1->name);
    temp->kind = p1->kind;
    strcpy(temp->Id, p1->Id);
    temp->price = p1->price;
    temp->amount = p1->amount;

    strcpy(p1->name, p2->name);
    p1->kind = p2->kind;
    strcpy(p1->Id, p2->Id);

    p1->price = p2->price;
    p1->amount = p2->amount;

    strcpy(p2->name, temp->name);
    p2->kind = temp->kind;
    strcpy(p2->Id, temp->Id);

    p2->price = temp->price;
    p2->amount = temp->amount;
}

Goodsmanager::Goodsmanager() // ﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌构造函数﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌
{
    Head = new Goods;
    Head->Next = new Goods;
    End = Head->Next;
    in.open("cangku.txt");
    if (!in)
        cout << "没有库存" << endl;
    else
    {
        while (!in.eof())
        {
            End->ReadFile(in);
            if (End->name[0] == '\0')
                break;
            End->Next = new Goods;
            End = End->Next;
        }
        in.close();
        cout << "\t\t\t\t读取商品信息成功!"
             << "\n"
             << endl;
    }
}

void Goodsmanager::showMenu(int n) // 菜单      //﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌菜单﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌

{
    switch (n)
    {
    case 1:
    {
        cout << "********************************************************************************\n"
             << "      1. 家电      2. 化妆品      3. 日用品      4. 饮料      \n"
             << "********************************************************************************\n"
             << endl;
        break;
    }
    case 2:
    {
        system("cls");
        cout << "***********************   商 店 仓 库 管 理 系  统     ***********************" << endl;
        cout << "***********************          1.增加商品            ***********************" << endl;
        cout << "***********************          2.显示商品            ***********************" << endl;
        cout << "***********************          3.排序商品            ***********************" << endl;
        cout << "***********************          4.查找商品            ***********************" << endl;
        cout << "***********************          5.删除商品            ***********************" << endl;
        cout << "***********************          6.修改商品            ***********************" << endl;
        cout << "***********************        7.保存商品信息          ***********************" << endl;
        cout << "***********************          0.退出系统            ***********************" << endl;

        cout << "\t\t\n\t\t\t\t  请选择：0-8" << endl;
        break;
    }
    case 3:
    {
        system("cls");
        cout << "********************************************************************************\n"
             << "\t   1. 修改商品名      4. 修改价格\t\t\n"
             << "\t   2. 修改种类        5. 修改剩余商品量\t\t\n"
             << "\t   3. 修改编号         \t\t\n"
             << "\t\t\t\t10.修改全部\n"
             << "********************************************************************************" << endl;
        cout << "\t\t\n\t\t\t\t  请选择：0-10" << endl;

        break;
    }
    case 4:
    {
        system("cls");
        cout << "********************************************************************************\n"
             << "\t   1. 按商品价格排序        2. 按库存量排序 \n"
             << "********************************************************************************" << endl;
        cout << "\t\t\n\t\t\t\t  请选择：0-3" << endl;

        break;
    }
    case 5:
    {
        system("cls");
        cout << "\n\t\t        *********************************\n";
        cout << "\t\t        *****   1.按商品的名称查找  *****\n\t\t        *****    2.按商品编号查找   *****";
        cout << "\n\t\t        *********************************\n请选择：0-2";
        break;
    }
    }
}

Goodsmanager::~Goodsmanager()
{
    // Save();
    for (Goods *temp; Head->Next != End;)
    {
        temp = Head->Next;
        Head->Next = Head->Next->Next;
        delete temp;
    }
    delete Head, End;
}

void Goodsmanager::Find()
{
    system("cls");
    char name[20], Id[10];
    int x;
    Goods *p = NULL;
    showMenu(5);
    cin >> x;
    switch (x)
    {
    case 1:
    {
        cout << "\t\t请输入要查找的商品的名称：";
        cin >> name;
        if (p = FindItem(name))
        {
            p->Next->Show();
            cout << "输入任意字符！继续……";
            getch();
        }
        else
        {
            cout << "\t\t没有找到该名称的商品！" << '\n'
                 << endl;
            cout << "输入任意字符！继续……";
            getch();
        }
    }
    break;
    case 2:
    {
        cout << "\t\t请输入要查找的商品的编号：";
        cin >> Id;
        if (p = FindID(Id))
        {
            p->Next->Show();
            cout << "输入任意字符！继续……";
            getch();
        }
        else
        {
            cout << "\t\t没有找到该编号的商品！" << '\n'
                 << endl;
            cout << "输入任意字符！继续……";
            getch();
        }
    }
    break;
    }
}

void Goodsmanager::ModifyItem() // 修改商品信息
{

    showMenu(3);
    int x;
    cin >> x;
    switch (x)
    {
    case 1:
    {
        char Id[20];
        Goods *p = NULL;
        cout << "\t\t请输入要修改的商品的编号:";
        cin >> Id;
        if (p = FindID(Id))
        {
            cout << "\t\t已找到商品的信息，请输入新的信息!" << endl;

            p->Next->InputName();
            cout << "修改成功！" << endl;
            cout << "输入任意字符！继续……";
            getch();
        }
        else
        {
            cout << "\t\t没有找到您需要的商品!" << endl;
            cout << "输入任意字符！继续……";
            getch();
        }
        break;
    }
    case 2:
    {
        char Id[20];
        Goods *p = NULL;
        cout << "\t\t请输入要修改的商品的编号:";
        cin >> Id;
        if (p = FindID(Id))
        {
            cout << "\t\t已找到商品的信息，请输入新的信息!" << endl;

            p->Next->InputKind();
            cout << "修改成功！" << endl;
            cout << "输入任意字符！继续……";
            getch();
        }
        else
        {
            cout << "\t\t没有找到您需要的商品!" << endl;
            cout << "输入任意字符！继续……";
            getch();
        }
        break;
    }
    case 3:
    {
        char Id[20];
        Goods *p = NULL;
        cout << "\t\t请输入要修改的商品的编号:";
        cin >> Id;
        if (p = FindID(Id))
        {
            cout << "\t\t已找到商品的信息，请输入新的信息!" << endl;

            p->Next->InputID();
            cout << "修改成功！" << endl;
            cout << "输入任意字符！继续……";
            getch();
        }
        else
        {
            cout << "\t\t没有找到您需要的商品!" << endl;
            cout << "输入任意字符！继续……";
            getch();
        }
        break;
    }
    case 4:
    {
        char Id[20];
        Goods *p = NULL;
        cout << "\t\t请输入要修改的商品的编号:";
        cin >> Id;
        if (p = FindID(Id))
        {
            cout << "\t\t已找到商品的信息，请输入新的信息!" << endl;

            p->Next->InputBuyprice();
            cout << "修改成功！" << endl;
            cout << "输入任意字符！继续……";
            getch();
        }
        else
        {
            cout << "\t\t没有找到您需要的商品!" << endl;
            cout << "输入任意字符！继续……";
            getch();
        }
        break;
    }
    case 5:
    {
        char Id[20];
        Goods *p = NULL;
        cout << "\t\t请输入要修改的商品的编号:";
        cin >> Id;
        if (p = FindID(Id))
        {
            cout << "\t\t已找到商品的信息，请输入新的信息!" << endl;

            p->Next->InputAmount();
            cout << "修改成功！" << endl;
            cout << "输入任意字符！继续……";
            getch();
        }
        else
        {
            cout << "\t\t没有找到您需要的商品!" << endl;
            cout << "输入任意字符！继续……";
            getch();
        }
        break;
    }
    }
}

void Goodsmanager::RemoveItem()
{
    system("cls");
    char Id[20];
    Goods *p = NULL, *temp = NULL;
    cout << "\t\t请输入要删除的商品的编号:" << endl;
    cin >> Id;
    if (p = FindID(Id))
    {
        temp = p->Next;
        p->Next = p->Next->Next;
        delete temp;
        cout << "\t\t删除成功!" << endl;
        cout << "输入任意字符！继续……";
        getch();
    }
    else
    {
        cout << "\t\t没有找到您需要的商品!" << endl;
        cout << "输入任意字符！继续……";
        getch();
    }
}

int Goodsmanager::ListCount() // 统计当前链表的记录总数，返回一个整数
{
    if (!Head)
        return 0;
    int n = 0;
    for (Goods *p = Head->Next; p != End; p = p->Next)
    {
        n++;
    }
    return n;
}

void Goodsmanager::Sort()
{
    showMenu(4);
    int x;
    cin >> x;
    switch (x)
    {
    case 1:
    {
        system("cls");
        cout << "\t\t排序中..." << endl;
        cout << "\n";
        Goods *p = NULL, *p1 = NULL, *k = NULL;
        int n = Goodsmanager::ListCount();
        if (n < 2)
            return;
        for (p = Head->Next; p != End; p = p->Next)
            for (k = p->Next; k != End; k = k->Next)
            {
                if (p->price > k->price)
                {
                    Goodsmanager::Swap(p, k);
                }
            }
        Display();
        out.open("售价.txt");
        for (Goods *q = Head->Next; q != End; q = q->Next)
            out << q->name << "\t" << q->kind << "\t" << q->Id << "\t" << q->price << "\t" << q->amount << '\n';
        out.close();
        cout << "保存信息成功" << endl;
        cout << "排序完成！" << endl;
        getch();
        return;
    }
    case 2:
    {
        system("cls");
        cout << "\t\t排序中..." << endl;
        cout << "\n";
        Goods *p = NULL, *p1 = NULL, *k = NULL;
        int n = Goodsmanager::ListCount();
        if (n < 2)
            return;
        for (p = Head->Next; p != End; p = p->Next)
            for (k = p->Next; k != End; k = k->Next)
            {
                if (p->amount > k->amount)
                {
                    Goodsmanager::Swap(p, k);
                }
            }
        Display();
        out.open("库存量.txt");
        for (Goods *q = Head->Next; q != End; q = q->Next)
            out << q->name << "\t" << q->kind << "\t" << q->Id << "\t" << q->price << "\t" << q->amount << '\n';
        out.close();
        cout << "保存信息成功" << endl;
        cout << "排序完成！" << endl;
        getch();
        return;
    }
    }
}

void Goodsmanager::Save()
{
    out.open("cangku.txt");
    for (Goods *p = Head->Next; p != End; p = p->Next)
        out << p->name << "\t" << p->kind << "\t" << p->Id << "\t" << p->price << "\t" << p->amount << '\n';

    out.close();
    cout << "保存信息成功" << endl;
}

int main() // ﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌主函数﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌
{
    cout << "\t\t*****************************************" << endl;
    for (int i = 0; i < 3; i++)
        cout << "\t\t******************\t\t\t\t\t\t  ******************" << endl;
    cout << "\t\t******************  欢迎进入仓库商品管理系统  ******************" << endl;
    for (int i = 0; i < 3; i++)
        cout << "\t\t******************\t\t\t\t\t\t  ******************" << endl;
    cout << "\t\t*****************************************\n"
         << endl;
    ;
    Goodsmanager Grade;
    cout << "\t\t\t\t按任意键开始……";
    getch();
    int x;
    bool quit = false;
    while (!quit)
    {

        Grade.showMenu(2);
        cin >> x;
        switch (x)
        {
        case 0:
        {
            quit = true;
            break;
        }
        case 1:
        {
            Grade.AddItem();
            break;
        }
        case 2:
        {
            Grade.Display();
            break;
        }
        case 3:
        {
            Grade.Sort();
            break;
        }
        case 4:
        {
            Grade.Find();
            break;
        }
        case 5:
        {
            Grade.RemoveItem();
            break;
        }
        case 6:
        {
            Grade.ModifyItem();
            break;
        }
        case 7:
        {
            Grade.Save();
            break;
        }
        }
    }

    return 0;
}
