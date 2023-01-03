#include <iostream>
#include <fstream>
#include <string.h>
#include <stdio.h>
#include <conio.h> //��getch();
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
        cout << "\t\t��ѡ�����ࣺ";
        cin >> kind;
    }
    void InputName()
    {
        cout << "\t\t��������Ʒ�����ƣ�";
        cin >> name;
    }
    void InputID()
    {
        cout << "\t\t��������Ʒ�ı�ţ�";
        cin >> Id;
    }
    void InputBuyprice()
    {
        cout << "\t\t��������Ʒ���ۣ�";
        cin >> price;
    }

    void InputAmount()
    {
        cout << "\t\t��������Ʒ��棺";
        cin >> amount;
    }
    void InputOther()
    {
        cout << "\t\t��������Ʒ�۸�";
        cin >> price;
        cout << "\t\t��������������";
        cin >> amount;
    }
    void ReadFile(istream &in)
    {
        in >> name >> kind >> Id >> price >> amount;
    }
    void Show()
    {

        cout << "��Ʒ��: " << name << endl
             << "����:" << kind << endl
             << "���: " << Id << endl
             << "�۸� " << price << endl
             << "��Ʒ���: " << amount << endl
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
        cout << "����" << i << "����Ʒ"
             << "\n"
             << endl;
        cout << "���������ַ�����������";
        getch();
    }
    void AddItem() // �Ӽ���������Ʒ��Ϣ
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
        cout << "��ӳɹ�!" << endl;
        Save();
        cout << "���������ַ�����������";
        getch();
    }

private:
    Goods *Head, *End;
    int i;
    ifstream in;
    ofstream out;
    Goods *FindItem(char *name)
    {
        for (Goods *p = Head; p->Next != End; p = p->Next) // ƥ��ɹ��򷵻���һ��ָ�룬���ɹ��ͷ��ؿ�
            if (!strcmp(p->Next->name, name))
                return p;
        return NULL;
    }
    Goods *FindID(char *Id)
    {
        for (Goods *p = Head; p->Next != End; p = p->Next) // ƥ��ɹ��򷵻���һ��ָ�룬���ɹ��ͷ��ؿ�
            if (!strcmp(p->Next->Id, Id))
                return p;
        return NULL;
    }
};

void Goodsmanager::Swap(Goods *p1, Goods *p2) // ����������Ʒ������
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

Goodsmanager::Goodsmanager() // �k�k�k�k�k�k�k�k�k�k�k�k���캯���k�k�k�k�k�k�k�k�k�k�k�k
{
    Head = new Goods;
    Head->Next = new Goods;
    End = Head->Next;
    in.open("cangku.txt");
    if (!in)
        cout << "û�п��" << endl;
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
        cout << "\t\t\t\t��ȡ��Ʒ��Ϣ�ɹ�!"
             << "\n"
             << endl;
    }
}

void Goodsmanager::showMenu(int n) // �˵�      //�k�k�k�k�k�k�k�k�k�k�k�k�˵��k�k�k�k�k�k�k�k�k�k�k�k

{
    switch (n)
    {
    case 1:
    {
        cout << "********************************************************************************\n"
             << "      1. �ҵ�      2. ��ױƷ      3. ����Ʒ      4. ����      \n"
             << "********************************************************************************\n"
             << endl;
        break;
    }
    case 2:
    {
        system("cls");
        cout << "***********************   �� �� �� �� �� �� ϵ  ͳ     ***********************" << endl;
        cout << "***********************          1.������Ʒ            ***********************" << endl;
        cout << "***********************          2.��ʾ��Ʒ            ***********************" << endl;
        cout << "***********************          3.������Ʒ            ***********************" << endl;
        cout << "***********************          4.������Ʒ            ***********************" << endl;
        cout << "***********************          5.ɾ����Ʒ            ***********************" << endl;
        cout << "***********************          6.�޸���Ʒ            ***********************" << endl;
        cout << "***********************        7.������Ʒ��Ϣ          ***********************" << endl;
        cout << "***********************          0.�˳�ϵͳ            ***********************" << endl;

        cout << "\t\t\n\t\t\t\t  ��ѡ��0-8" << endl;
        break;
    }
    case 3:
    {
        system("cls");
        cout << "********************************************************************************\n"
             << "\t   1. �޸���Ʒ��      4. �޸ļ۸�\t\t\n"
             << "\t   2. �޸�����        5. �޸�ʣ����Ʒ��\t\t\n"
             << "\t   3. �޸ı��         \t\t\n"
             << "\t\t\t\t10.�޸�ȫ��\n"
             << "********************************************************************************" << endl;
        cout << "\t\t\n\t\t\t\t  ��ѡ��0-10" << endl;

        break;
    }
    case 4:
    {
        system("cls");
        cout << "********************************************************************************\n"
             << "\t   1. ����Ʒ�۸�����        2. ����������� \n"
             << "********************************************************************************" << endl;
        cout << "\t\t\n\t\t\t\t  ��ѡ��0-3" << endl;

        break;
    }
    case 5:
    {
        system("cls");
        cout << "\n\t\t        *********************************\n";
        cout << "\t\t        *****   1.����Ʒ�����Ʋ���  *****\n\t\t        *****    2.����Ʒ��Ų���   *****";
        cout << "\n\t\t        *********************************\n��ѡ��0-2";
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
        cout << "\t\t������Ҫ���ҵ���Ʒ�����ƣ�";
        cin >> name;
        if (p = FindItem(name))
        {
            p->Next->Show();
            cout << "���������ַ�����������";
            getch();
        }
        else
        {
            cout << "\t\tû���ҵ������Ƶ���Ʒ��" << '\n'
                 << endl;
            cout << "���������ַ�����������";
            getch();
        }
    }
    break;
    case 2:
    {
        cout << "\t\t������Ҫ���ҵ���Ʒ�ı�ţ�";
        cin >> Id;
        if (p = FindID(Id))
        {
            p->Next->Show();
            cout << "���������ַ�����������";
            getch();
        }
        else
        {
            cout << "\t\tû���ҵ��ñ�ŵ���Ʒ��" << '\n'
                 << endl;
            cout << "���������ַ�����������";
            getch();
        }
    }
    break;
    }
}

void Goodsmanager::ModifyItem() // �޸���Ʒ��Ϣ
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
        cout << "\t\t������Ҫ�޸ĵ���Ʒ�ı��:";
        cin >> Id;
        if (p = FindID(Id))
        {
            cout << "\t\t���ҵ���Ʒ����Ϣ���������µ���Ϣ!" << endl;

            p->Next->InputName();
            cout << "�޸ĳɹ���" << endl;
            cout << "���������ַ�����������";
            getch();
        }
        else
        {
            cout << "\t\tû���ҵ�����Ҫ����Ʒ!" << endl;
            cout << "���������ַ�����������";
            getch();
        }
        break;
    }
    case 2:
    {
        char Id[20];
        Goods *p = NULL;
        cout << "\t\t������Ҫ�޸ĵ���Ʒ�ı��:";
        cin >> Id;
        if (p = FindID(Id))
        {
            cout << "\t\t���ҵ���Ʒ����Ϣ���������µ���Ϣ!" << endl;

            p->Next->InputKind();
            cout << "�޸ĳɹ���" << endl;
            cout << "���������ַ�����������";
            getch();
        }
        else
        {
            cout << "\t\tû���ҵ�����Ҫ����Ʒ!" << endl;
            cout << "���������ַ�����������";
            getch();
        }
        break;
    }
    case 3:
    {
        char Id[20];
        Goods *p = NULL;
        cout << "\t\t������Ҫ�޸ĵ���Ʒ�ı��:";
        cin >> Id;
        if (p = FindID(Id))
        {
            cout << "\t\t���ҵ���Ʒ����Ϣ���������µ���Ϣ!" << endl;

            p->Next->InputID();
            cout << "�޸ĳɹ���" << endl;
            cout << "���������ַ�����������";
            getch();
        }
        else
        {
            cout << "\t\tû���ҵ�����Ҫ����Ʒ!" << endl;
            cout << "���������ַ�����������";
            getch();
        }
        break;
    }
    case 4:
    {
        char Id[20];
        Goods *p = NULL;
        cout << "\t\t������Ҫ�޸ĵ���Ʒ�ı��:";
        cin >> Id;
        if (p = FindID(Id))
        {
            cout << "\t\t���ҵ���Ʒ����Ϣ���������µ���Ϣ!" << endl;

            p->Next->InputBuyprice();
            cout << "�޸ĳɹ���" << endl;
            cout << "���������ַ�����������";
            getch();
        }
        else
        {
            cout << "\t\tû���ҵ�����Ҫ����Ʒ!" << endl;
            cout << "���������ַ�����������";
            getch();
        }
        break;
    }
    case 5:
    {
        char Id[20];
        Goods *p = NULL;
        cout << "\t\t������Ҫ�޸ĵ���Ʒ�ı��:";
        cin >> Id;
        if (p = FindID(Id))
        {
            cout << "\t\t���ҵ���Ʒ����Ϣ���������µ���Ϣ!" << endl;

            p->Next->InputAmount();
            cout << "�޸ĳɹ���" << endl;
            cout << "���������ַ�����������";
            getch();
        }
        else
        {
            cout << "\t\tû���ҵ�����Ҫ����Ʒ!" << endl;
            cout << "���������ַ�����������";
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
    cout << "\t\t������Ҫɾ������Ʒ�ı��:" << endl;
    cin >> Id;
    if (p = FindID(Id))
    {
        temp = p->Next;
        p->Next = p->Next->Next;
        delete temp;
        cout << "\t\tɾ���ɹ�!" << endl;
        cout << "���������ַ�����������";
        getch();
    }
    else
    {
        cout << "\t\tû���ҵ�����Ҫ����Ʒ!" << endl;
        cout << "���������ַ�����������";
        getch();
    }
}

int Goodsmanager::ListCount() // ͳ�Ƶ�ǰ����ļ�¼����������һ������
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
        cout << "\t\t������..." << endl;
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
        out.open("�ۼ�.txt");
        for (Goods *q = Head->Next; q != End; q = q->Next)
            out << q->name << "\t" << q->kind << "\t" << q->Id << "\t" << q->price << "\t" << q->amount << '\n';
        out.close();
        cout << "������Ϣ�ɹ�" << endl;
        cout << "������ɣ�" << endl;
        getch();
        return;
    }
    case 2:
    {
        system("cls");
        cout << "\t\t������..." << endl;
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
        out.open("�����.txt");
        for (Goods *q = Head->Next; q != End; q = q->Next)
            out << q->name << "\t" << q->kind << "\t" << q->Id << "\t" << q->price << "\t" << q->amount << '\n';
        out.close();
        cout << "������Ϣ�ɹ�" << endl;
        cout << "������ɣ�" << endl;
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
    cout << "������Ϣ�ɹ�" << endl;
}

int main() // �k�k�k�k�k�k�k�k�k�k�k�k�������k�k�k�k�k�k�k�k�k�k�k�k
{
    cout << "\t\t*****************************************" << endl;
    for (int i = 0; i < 3; i++)
        cout << "\t\t******************\t\t\t\t\t\t  ******************" << endl;
    cout << "\t\t******************  ��ӭ����ֿ���Ʒ����ϵͳ  ******************" << endl;
    for (int i = 0; i < 3; i++)
        cout << "\t\t******************\t\t\t\t\t\t  ******************" << endl;
    cout << "\t\t*****************************************\n"
         << endl;
    ;
    Goodsmanager Grade;
    cout << "\t\t\t\t���������ʼ����";
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
