#include <iostream>
#include<windows.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
void HideCursor()
{
	HANDLE fd = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cinfo;
	cinfo.bVisible = 0;
	cinfo.dwSize = 1;
	SetConsoleCursorInfo(fd, &cinfo);
}
void gotoxy(int x, int y) {
	COORD pos = { x,y };
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);// 获取标准输出设备句柄 
	SetConsoleCursorPosition(hOut, pos);//两个参数分别是指定哪个窗体，具体位置 
}
/*-----------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------*/
struct point* list = NULL;
struct bookmess
{
	char name[20] = { 0 };
	int number = 0;
	char author[10] = { 0 };
	char place[20] = { 0 };
	float price = 0;

};
struct point//结构体变量格式
{
	struct bookmess infor;
	struct point* next;
};
struct point* sethead()//创建头节点
{
	struct point* headpoint = (struct point*)malloc(sizeof(struct point*));
	headpoint->next = NULL;
	return headpoint;
}
struct point* setpoint(struct bookmess infor)//创建节点
{
	struct point* newpoint = (struct point*)malloc(sizeof(struct point*));
	newpoint->infor = infor;
	newpoint->next = NULL;
	return newpoint;
}
void insertpoint(struct point* headpoint, struct bookmess infor)//插入信息
{
	struct point* insertpoint = setpoint(infor);
	insertpoint->next = headpoint->next;
	headpoint->next = insertpoint;
}
void deletepoint(struct point* headpoint, char* bookname)//删除数据
{
	struct point* beforepoint = headpoint;
	struct point* chosepoint = headpoint->next;
	while (strcmp(chosepoint->infor.name, bookname) && chosepoint != NULL)
	{
		beforepoint = chosepoint;
		chosepoint = chosepoint->next;
	}
	if (chosepoint == NULL)
		return;
	else
	{
		chosepoint->next = beforepoint->next;
		free(chosepoint);
		chosepoint = NULL;
	}
}
void linepoint(struct point* headpoint)
{
	for (struct point* p1 = headpoint->next; p1 != NULL; p1 = p1->next)
	{
		for (struct point* p2 = headpoint->next; p2 != NULL; p2 = p2->next)
		{
			if (p2->infor.price > p1->infor.price)
			{
				struct bookmess teminfor = p2->infor;
				p2->infor = p1->infor;
				p1->infor = teminfor;
			}

		}

	}
}
void showlist(struct point* headpoint)//打印链表
{
	struct point* p = headpoint->next;
	printf("书名\t编号\t作者\t出版社\t价格\n");
	while (p)
	{
		printf("%s\t%d\t%s\t%s\t%.2f\n", p->infor.name, p->infor.number, p->infor.author, p->infor.place, p->infor.price);
		p = p->next;
	}
}
void filer(const char* filename, struct point* headpoint)//文件读入
{
	FILE* pf;
	fopen_s(&pf, filename, "r");

	if (pf == NULL)//创建文件
	{
		fopen_s(&pf, filename, "w+");

	}
	struct bookmess filemess;
	while (fscanf_s(pf, "%s %d %s %s %f", filemess.name, 20, &filemess.number, filemess.author, 20, filemess.place, 20, &filemess.price)!=EOF)
	{
		insertpoint(headpoint, filemess);
	}
	fclose(pf);
}
void filew(const char* filename, struct point* headpoint)//文件写入
{
	FILE* pf;
	fopen_s(&pf, filename, "a");
	struct point* p = headpoint->next;
	while (p)
	{
		fprintf(pf, "%s\t%d\t%s\t%s\t%.2f", p->infor.name, p->infor.number, p->infor.author, p->infor.place, p->infor.price);
		p = p->next;
	}
	fclose(pf);
}
void makemenu()
{
	printf("-------------------------------------------\n");
	printf("    欢迎使用图书管理系统\n");
	printf("\t1.登记书籍\n");
	printf("\t2.借阅书籍\n");
	printf("\t3.浏览所有\n");
	printf("\t4.归还书籍\n");
	printf("\t5.书籍排序\n");
	printf("\t6.删除书籍\n");
	printf("\t7.查找书籍\n");
	printf("\t8.退出程序\n");
	printf("-------------------------------------------\n");
	printf("    请输入1-8以选择功能\n");

}
void select()
{
	int choose = 0;
	struct bookmess record;
	scanf_s("%d", &choose);
	switch (choose)
	{
	case 1:
	{printf("【登记】\n");
	printf("请输入书籍名称 编号 作者 出版社 价格\n");
	scanf_s("%s %d %s %s %f", record.name, 20, &record.number, record.author, 20, record.place, 20, &record.price);
	insertpoint(list, record);
	filew("bookmess.txt", list);
	break; }
	case 2:
		printf("【借阅】\n"); break;
	case 3:
		printf("【浏览】\n");
		showlist(list);
		break;
	case 4:
		printf("【归还】\n"); break;
	case 5:
		printf("【排序】\n"); break;
	case 6:
		printf("【删除】\n"); break;
	case 7:
		printf("【查找】\n"); break;
	case 8:
		printf("【退出】\n"); printf("【退出成功】\n"); system("pause"); exit(0); break;
	default:
		printf("error\n"); break;
	}
}

int main()
{
	HideCursor();
	system("color A1");
	Beep(2000, 250);

	list = sethead();
	filer("bookmess.txt", list);
	while (1)
	{
		makemenu();
		select();
		system("pause");
		system("cls");
	}


	system("pause");


}