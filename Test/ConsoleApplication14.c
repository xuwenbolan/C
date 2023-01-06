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
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);// ��ȡ��׼����豸��� 
	SetConsoleCursorPosition(hOut, pos);//���������ֱ���ָ���ĸ����壬����λ�� 
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
struct point//�ṹ�������ʽ
{
	struct bookmess infor;
	struct point* next;
};
struct point* sethead()//����ͷ�ڵ�
{
	struct point* headpoint = (struct point*)malloc(sizeof(struct point*));
	headpoint->next = NULL;
	return headpoint;
}
struct point* setpoint(struct bookmess infor)//�����ڵ�
{
	struct point* newpoint= (struct point*)malloc(sizeof(struct point*));
	newpoint->infor = infor;
	newpoint->next = NULL;
	return newpoint;
}
void insertpoint(struct point* headpoint, struct bookmess infor)//������Ϣ
{
	struct point* insertpoint = setpoint(infor);
	insertpoint->next = headpoint->next;
	headpoint->next = insertpoint;
}
void deletepoint(struct point*headpoint, char* bookname)//ɾ������
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
void showlist(struct point* headpoint)//��ӡ����
{
	struct point* p = headpoint->next;
	printf("����\t���\t����\t������\t�۸�\n");
	while (p)
	{
		printf("%s\t%d\t%s\t%s\t%.2f", p->infor.name , p->infor.number  , p->infor.author , p->infor.place, p->infor.price );
		p = p->next;
	}
}
void filer(const char* filename, struct point* headpoint)//�ļ�����
{
	FILE* pf=NULL;
	pf=fopen("bookmess.txt","r");
	if (pf == NULL)//�����ļ�
	{
	    fopen_s(&pf,filename,"w+");
	}
	struct bookmess* filemess = (struct bookmess*)malloc(sizeof(struct bookmess*));
	while(fscanf(pf, "%s\t;%d\t;%s\t;%s\t;%��2f", filemess->name,&filemess->number,  filemess->author , filemess->place ,&filemess->price ,20,20,20)!=EOF)
	fclose(pf);
}
void filew(const char* filename, struct point* headpoint)//�ļ�д��
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
	printf("    ��ӭʹ��ͼ�����ϵͳ\n");
	printf("\t1.�Ǽ��鼮\n");
	printf("\t2.�����鼮\n");
	printf("\t3.�����¼\n");
	printf("\t4.�黹�鼮\n");
	printf("\t5.�鼮����\n");
	printf("\t6.ɾ���鼮\n");
	printf("\t7.�����鼮\n");
	printf("\t8.�˳�����\n");
	printf("-------------------------------------------\n");
	printf("    ������1-8��ѡ����\n");
	
}  
void select()
{
	int choose = 0;
	struct bookmess record;
	scanf("%d", &choose);
	switch (choose)
	{
	case 1:
	{printf("���Ǽǡ�\n");
	printf("�������鼮���� ��� ���� ������ �۸�\n");
	//scanf("%s %d %s %s %f",record.name, &record.number, record.author, record.place, &record.price);
	insertpoint(list, record);
	filew("bookmess.txt", list);
	break;}
	case 2:
		printf("�����ġ�\n");break;
	case 3:
		printf("�������\n");
		showlist(list);
		break;
	case 4:
		printf("���黹��\n");break;
	case 5:
		printf("������\n");break;
	case 6:
		printf("��ɾ����\n");break;
	case 7:
		printf("�����ҡ�\n");break;
	case 8:
		printf("���˳���\n");printf("���˳��ɹ���\n");system("pause");exit(0);break;
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
