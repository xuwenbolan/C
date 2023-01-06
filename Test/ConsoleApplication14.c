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
	char name[20];
	int number;
	char author[10];
	char place[20];
	float price;
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
	struct point* newpoint= (struct point*)malloc(sizeof(struct point*));
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
void deletepoint(struct point*headpoint, char* bookname)//删除数据
{
	struct point* beforepoint = headpoint;
	struct point* chosepoint = headpoint->next;
	while (strcmp(chosepoint->infor .name ,bookname) && chosepoint != NULL)
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
void showlist(struct point* headpoint)//打印链表
{
	struct point* p = headpoint->next;
	printf("书名\t编号\t作者\t出版社\t价格\n");
	while (p)
	{
		printf("%s\t%d\t%s\t%s\t%.2f", p->infor.name , p->infor.number  , p->infor.author , p->infor.place, p->infor.price );
		p = p->next;
	}
}
void filer(const char* filename, struct point* headpoint)//文件读入
{
	FILE* pf=NULL;
	pf=fopen("bookmess.txt","r");
	if (pf == NULL)//创建文件
	{
	    fopen_s(&pf,filename,"w+");
	}
	struct bookmess* filemess = (struct bookmess*)malloc(sizeof(struct bookmess*));
	while(fscanf(pf, "%s\t;%d\t;%s\t;%s\t;%。2f", filemess->name,&filemess->number,  filemess->author , filemess->place ,&filemess->price ,20,20,20)!=EOF)
	fclose(pf);
}
void filew(const char* filename, struct point* headpoint)//文件写入
{
	FILE* pf;
	fopen_s(&pf, filename, "w");
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
	printf("\t3.浏览记录\n");
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
	scanf("%d", &choose);
	switch (choose)
	{
	case 1:
	{printf("【登记】\n");
	printf("请输入书籍名称 编号 作者 出版社 价格\n");
	//scanf("%s %d %s %s %f",record.name, &record.number, record.author, record.place, &record.price);
	insertpoint(list, record);
	filew("bookmess.txt", list);
	break;}
	case 2:
		printf("【借阅】\n");break;
	case 3:
		printf("【浏览】\n");
		showlist(list);
		break;
	case 4:
		printf("【归还】\n");break;
	case 5:
		printf("【排序】\n");break;
	case 6:
		printf("【删除】\n");break;
	case 7:
		printf("【查找】\n");break;
	case 8:
		printf("【退出】\n");printf("【退出成功】\n");system("pause");exit(0);break;
	default:
		printf("error\n");break;
	}
}

int main()
{
	HideCursor();
	system("color A1");
	//Beep(2000, 250);
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
