//�������Ϣ�������������Զ����浽�ļ�
//��������Ϣ�����ܲ������Զ����棬���渲��.txt 
//���޸���Ϣ����������л�����Ϣ���ٽ����޸�   �޸����ڲ����浽.txt���������޸�
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void page() { //ҳ�濪ʼ
	system("color 3E");
	printf("\t\t\t\t\t**********************************\n");
	printf("\t\t\t\t\t\t��ӭ����ֿ�������ϵͳ\n");
	printf("\t\t\t\t\t**********************************\n");
	printf("\n");
	printf("\t\t\t\t\t\t��enter������\n");
}
void menu() { //Ŀ¼
	printf("\t\t\t\t\t|________________________________________|\n");
	printf("\t\t\t\t\t|________________������Ϣ________________|\n");
	printf("\t\t\t\t\t|   1. ����������Ϣ| 2. ���������Ϣ|\n");
	printf("\t\t\t\t\t|----------------------------------------|\n");
	printf("\t\t\t\t\t|   3. ���һ�����Ϣ| 4. �޸Ļ�����Ϣ|\n");
	printf("\t\t\t\t\t|----------------------------------------|\n");
	printf("\t\t\t\t\t|   5. ɾ��������Ϣ| 6. ���������Ϣ|\n");
	printf("\t\t\t\t\t|----------------------------------------|\n");
	printf("\t\t\t\t\t|   7. �����Ϣ    | 8. ����|\n");
	printf("\t\t\t\t\t|----------------------------------------|\n");
	printf("\t\t\t\t\t    9. ������Ϣ    | 0. �˳�����\n");
	printf("\t\t\t\t\t|________________________________________|");
	printf("\n");
	printf("\n\t\t\t\t\t��������Ĳ�������(0--8):\n");
}
//����ṹ��
typedef struct object {
	int number;
	char name[100];
	float price;
	int count;
	struct object * next;
} a1; //��a1����ṹ����object
a1 * head;//����ͷָ��
a1 * creat() { //1.������Ϣ���ܣ�����һ��ͷָ��
	a1 *po=NULL;
	a1 *p=NULL;//��ʼ��ָ��
	po=head=(a1*)malloc(sizeof(a1));//����һ���µ�Ԫ,���������ڴ��ʼ��ַ
	int n;
	int ret;
	//����һ����ѭ������ε��ú���
	while(1) {
		p=(a1*)malloc(sizeof(a1));//���ٶ�̬�洢��������ʼ��ַ����p
		printf("���������ı�š����ơ��۸�����:\n");
		printf("���:");
		scanf("%d",&p->number);
		//���������Ƚ��ظ�
		if(p->number==po->number) {
			printf("����������ظ�\n");
			break;
		}
		if(p->number<0) {
			printf("�����Ÿ�ʽ����\n");
			break;
		}
		printf("����:");
		scanf("%s",&p->name);
		printf("�۸�:");
		ret=scanf("%f",&p->price);
		//��ȡ��һ�����ͣ�ret=1������ѭ��������ret=0  ���������ݷŵ������� 
		while(ret!=1)
		{
			while(getchar()!='\n');//== fflush(stdin)  ��ջ������Ƿ��ַ� 
			printf("����۸��ʽ����,����������\n");
			ret=scanf("%f",&p->price);
			if(getchar()=='\n')
			{
				break;
			}
		}
		if(p->price<0)
		{
			printf("����۸����\n");
			break;
		}
		printf("����:");
		scanf("%d",&p->count);
			if(p->count<0) {
				printf("����������ʽ����\n");
				break;
			}
		printf("\n");
		po->next=p;
		po=p;//ʵ����poָ��p�Ŀռ�
		printf("===============================================\n");
		printf("�Ƿ��˳�����������Ϣ �˳�: ����1 ����: ����2\n");
		scanf("%d",&n);
		if(n==1) {
			po->next=NULL;//���ٴ�����Ϣ����Ϊβ���
			p=NULL;
			return (head);
		}
		printf("\n");
		if(n>2) {
			printf("�������!\n");
			system("pause");//��ͣ
			break;
		}
	}
	po->next=NULL;
	free(p);
	p=NULL;//��p����ָ���
	return (head);
}
//������Ϣ����
void baocun(a1 *head) { //��ͷָ�뿪ʼ
	int m;//���
	m=0;
	a1 *p=NULL;
	FILE *z;//�ļ�ָ��
	p=head->next;//p ��һ��� 
	if(p==NULL) {
		printf("δ����������Ϣ,�޷�����\n");
	} else if(p!=NULL) {
		p=head->next;//p�ӵ�һ����㿪ʼ
		if((z=fopen("������Ϣ.txt","w"))==NULL) { //����������Ϣ�ļ��� ֻд
			printf("�޷��򿪴˻����ļ�\n");
			exit(0);//���գ���ֹ
		}
		while(p!=NULL) {
			fprintf(z,"���:%d\t",p->number);//��ʽ�����  ���ļ�Ϊ���� 
			fprintf(z,"����:%s\t",p->name);
			fprintf(z,"�۸�:%f\t",p->price);
			fprintf(z,"����:%d\n",p->count);
			p=p->next;//p����
			m++;//�������
		}
		printf("����ɹ�! ������%d��������Ϣ\n",m);
		fclose(z);//�ر��ļ�;
	}
}
//���ҹ���
void search(a1 *head) {
	a1 *p=NULL;
	char name0[100];
	p=head->next;
	int n;
	int x;
	if(p!=NULL) {
		printf("\t\t\t��ѡ����ҷ�ʽ\n");//���ҷ�ʽ
		printf("\t\t\t1.ͨ�������Ų���  2.ͨ���������Ʋ���\n");
		printf("========================================\n");
		printf("��������ҷ�ʽ:1��2\n");
		scanf("%d",&n);
		switch(n) {
			case 1:
				printf("��������ҵĻ�����:\n");
				scanf("%d",&x);
				while(p!=NULL) {
					if(x==p->number) {
						printf("Ҫ���ҵĻ������ϢΪ:\n");
						printf("���: %d\n",p->number);
						printf("����: %s\n",p->name);
						printf("�۸�: %f\n",p->price);
						printf("����: %d\n",p->count);
						printf("���ҳɹ�\n");
						break;//��ֹ���޲���
					}
					printf("\n");
					p=p->next;
				}
				break;//case1��break
			case 2:
				printf("������Ҫ���ҵĻ�������:\n");
				scanf("%s",&name0);
				while(p!=NULL) {
					if(strcmp(name0,p->name)==0) {
						printf("Ҫ���ҵĻ�����ϢΪ:\n");
						printf("���: %d\n",p->number);
						printf("����: %s\n",p->name);
						printf("�۸�: %f\n",p->price);
						printf("����: %d\n",p->count);
						printf("���ҳɹ�!\n");
						break;
					}
					printf("\n");
					p=p->next;
				}
				break;//case2��break
			default:
				printf("���ҷ�ʽ����!\n");
		}
	} else
		printf("δ¼����Ϣ���޷�����\n");
}
//�����Ϣ����
void add(a1 *head) {
	a1 *p=NULL;
	a1 *p1=NULL;
	p=head;//p ͷָ��
	while(p->next!=NULL) {
		p=p->next;
	}
	p1=(a1*)malloc(sizeof(a1));//���ٿռ䣬��p1�ڴ��׵�ַ
	printf("������Ҫ��ӵĻ�����Ϣ:\n");
	printf("���:");
	scanf("%d",&p1->number);
	printf("����:");
	scanf("%s",&p1->name);
	printf("�۸�:");
	scanf("%f",&p1->price);
	printf("����:");
	scanf("%d",&p1->count);
	printf("��ӳɹ���\n");
	p->next=p1;//��p����һ�����Ϊp1
	p1->next=NULL;//p1Ϊβ��㣬������
}
//�޸���Ϣ����
void correct(a1 *head) {
	a1 *p;
	a1 *w;
	w=head;
	p=NULL;
	char nameplus[100];//�����±�����������޸ĵ�����
	int numberplus;
	float priceplus;
	int countplus;
	int v;//�����õ����޸ķ�ʽ
	int numm;
	p=head->next;//p�ӵ�һ����㿪ʼ������
	while(head!=NULL) {
		if(p==NULL) {
			printf("δ����������Ϣ���޷��޸�\n");
			break;
		}
		printf("���ձ�Ų���\n");
		printf("������Ҫ���ҵı�ţ�\n");
        scanf("%d",&numm);
			if(p->number==numm) {
				printf("���ҵ���Ϣ\n");
				printf("|���\t|����\t|�۸�\t\t|����\t |\n");
				printf("|%d\t|%s\t|%f\t|%d\t |\n",p->number, p->name,p->price,p->count);
				printf("������޸�\n");
				printf("���:");
				scanf("%d",&p->number);			
				printf("����");
				scanf("%s",&p->name);
				printf("�۸�:");
				scanf("%f",&p->price);
				printf("����");
				scanf("%d",&p->count);
				printf("�޸����");
				break;
			} else {
				printf("δ���ҵ��û���\n");
				break;
			}
 
		}
	printf("\n");
}
//ɾ����Ϣ����
void cut(a1 *head,int number) {//�Ա�ŷ�ʽɾ��
	a1 *p,*q;
	p=head;
	int numberplusplus;
	if(p->next!=NULL) {
		printf("��������ɾ��:\n");
		printf("�����������:\n");
		scanf("%d",&numberplusplus);
		if(head==NULL) {
			printf("Ϊ������\n");
			return;
		}
		while(p->number!=numberplusplus&&p->next!=NULL) {
			q=p;//q����
			p=p->next;//pǰ��
		}
		if(p->number==numberplusplus) {//�����Ŷ�Ӧ�Ļ�
			if(p==head) {//����ҵ�����ͷ���
				head=p->next;//ͷָ�����
			} else {//�������ͷ���
				q->next=p->next;//Խ��p���
			}
			free(p);
			printf("ɾ���ɹ�\n");
		} else {
			printf("û�д˻���:\n");
		}
	} else
		printf("δ����������Ϣ���޷�ɾ��\n");
}
//��ʾ��Ϣ����
void out(a1 *head) {
	a1 *p=NULL;
	p=head->next;//ָ���һ�����
	if(p!=NULL) {
		while(p!=NULL) {
			printf("__________________________________________\n");
			printf("|���\t|����\t|�۸�\t\t|����\t |\n");
			printf("|________________________________________|\n");
			printf("|%d\t|%s\t|%f\t|%d\t |\n",p->number, p->name,p->price,p->count);
			printf("|________________________________________|\n");
			p=p->next;//��˳�����
		}
	} else printf("δ����������Ϣ���޷���ʾ\n");
}
//��ȡ����
a1 *in() {
	FILE *z;
	a1 *head,*p,*w;
	if((z=fopen("������Ϣ.txt","r")) == NULL) { //��txt�ļ�  ֻ��
		printf("���ܴ��ļ���\n");
	}
	head=(a1 *)malloc(sizeof(a1)); //����ռ�,����׵�ַ
	head->next=NULL;
	p=(a1 *)malloc(sizeof(a1));
	int m=0;
	while(fread(p,sizeof(a1),1,z)) { //��ȡ�ļ���Ϣ��fread������ִ�гɹ�����ô����ֵΪcount��������ĸ�����
		m=m+1;
		p->next=NULL;//���
		printf("���:%d\t����:%s\t�۸�%f\t����:%d\t\n",p->number, p->name,p->price,p->count);
		getchar();
		if(m==1) {//���ֻ��һ����Ϣ����ֻ��һ�����
			head->next=p;
		} else {
			w->next=p;//������Ϣ
		}
		w=p;//��wָ��p�Ŀռ�
		p=(a1 *)malloc(sizeof(a1));//���µõ���ʼ��ַ
	}
	fclose(z);
	return head;
}
//����
void sort(a1 *head) {
int i,cou=0;//cou������� 
int num;//��ѭ�� 
a1 *p,*q,*tail;
p=head;
if(head->next!=NULL)
{
	printf("����Ŵ�С��������\n");
while(p->next!=NULL)//�������� 
{
	cou++;
	p=p->next;
}
for(i=0;i<cou-1;i++)
{
	num=cou-i-1;//��ѭ������ 
	q=head->next;//qָ���һ����� 
	p=q->next;//pָ��p��һ����� 
	tail=head;//tailָ��qǰһ����� 
	while(num--)//��ѭ�� 
	{
		if(q->number>p->number)
		{
			q->next=p->next;
			p->next=q;
			tail->next=p;
		}
		tail=tail->next;
		q=tail->next;
		p=q->next;
	 } 
}
printf("����ɹ�\n");
}
else 
{
	printf("�޻�����Ϣ\n");
}
}
 
//��������ʼ
int main() {
	FILE *z;//�ļ�ָ��
	int m;
	char n;
	int number;
	page();//����ҳ�溯��
	getchar();//��enter��һ��
	if((z=fopen("������Ϣ.txt","w"))!=NULL) {
		head=in();//����
	} else {
		printf("�ļ���û�б��������Ϣ��\n");
	}
	while(1) {
		system("cls");//����
		menu();//����Ŀ¼����
		scanf("%c",&n);
		switch(n) {
			case '1'://������Ϣ
				head=creat();
				break;
			case '2':// ������Ϣ
				baocun(head);
				break;
			case '3'://��ѯ��Ϣ
				search(head);
				break;
			case '4'://�޸���Ϣ
				out(head);
				correct(head);
				break;
			case '5'://ɾ����Ϣ
				cut(head,number);
				break;
			case '6'://�����Ϣ
				out(head);
				break;
			case '7'://�����Ϣ
				add(head);
				baocun(head);
				break;
			case '8'://����
				sort(head);
				break;
			case '9'://������Ϣ 
				add(head);
				break;
			case '0'://�˳�����
				break;
			default:
				printf("ѡ���ܴ���!\n");
		}
		printf("\n");
		printf("����������������������������������������������������������\n");
		printf("�Ƿ�����Ըû�����Ϣ�Ĳ���������������� �䣺1 �˳��䣺 2 \n");
		printf("����������������������������������������������������������\n");
		scanf("%d",&m);
		getchar();
		if(m==2) {
			break;
		}
	}
	return 0;
}