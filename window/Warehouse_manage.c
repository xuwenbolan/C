//‘添存信息’功能添加完后自动保存到文件
//‘创建信息’功能不设置自动保存，保存覆盖.txt 
//‘修改信息’先输出所有货物信息，再进行修改   修改是在不保存到.txt的条件下修改
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void page() { //页面开始
	system("color 3E");
	printf("\t\t\t\t\t**********************************\n");
	printf("\t\t\t\t\t\t欢迎进入仓库货物管理系统\n");
	printf("\t\t\t\t\t**********************************\n");
	printf("\n");
	printf("\t\t\t\t\t\t按enter键继续\n");
}
void menu() { //目录
	printf("\t\t\t\t\t|________________________________________|\n");
	printf("\t\t\t\t\t|________________基本信息________________|\n");
	printf("\t\t\t\t\t|   1. 创建货物信息| 2. 保存货物信息|\n");
	printf("\t\t\t\t\t|----------------------------------------|\n");
	printf("\t\t\t\t\t|   3. 查找货物信息| 4. 修改货物信息|\n");
	printf("\t\t\t\t\t|----------------------------------------|\n");
	printf("\t\t\t\t\t|   5. 删除货物信息| 6. 输出货物信息|\n");
	printf("\t\t\t\t\t|----------------------------------------|\n");
	printf("\t\t\t\t\t|   7. 添存信息    | 8. 排序|\n");
	printf("\t\t\t\t\t|----------------------------------------|\n");
	printf("\t\t\t\t\t    9. 增加信息    | 0. 退出程序\n");
	printf("\t\t\t\t\t|________________________________________|");
	printf("\n");
	printf("\n\t\t\t\t\t请输入你的操作代号(0--8):\n");
}
//定义结构体
typedef struct object {
	int number;
	char name[100];
	float price;
	int count;
	struct object * next;
} a1; //用a1代替结构体名object
a1 * head;//定义头指针
a1 * creat() { //1.创建信息功能，返回一个头指针
	a1 *po=NULL;
	a1 *p=NULL;//初始化指针
	po=head=(a1*)malloc(sizeof(a1));//开辟一个新单元,并赋给它内存初始地址
	int n;
	int ret;
	//内置一个死循环，多次调用函数
	while(1) {
		p=(a1*)malloc(sizeof(a1));//开辟动态存储区，把起始地址赋给p
		printf("请输入货物的编号、名称、价格、数量:\n");
		printf("编号:");
		scanf("%d",&p->number);
		//相邻两个比较重复
		if(p->number==po->number) {
			printf("输入货物编号重复\n");
			break;
		}
		if(p->number<0) {
			printf("输入编号格式有误\n");
			break;
		}
		printf("名称:");
		scanf("%s",&p->name);
		printf("价格:");
		ret=scanf("%f",&p->price);
		//读取到一个整型，ret=1，跳过循环。否则ret=0  非整型数据放到缓存区 
		while(ret!=1)
		{
			while(getchar()!='\n');//== fflush(stdin)  清空缓存区非法字符 
			printf("输入价格格式错误,请重新输入\n");
			ret=scanf("%f",&p->price);
			if(getchar()=='\n')
			{
				break;
			}
		}
		if(p->price<0)
		{
			printf("输入价格错误\n");
			break;
		}
		printf("数量:");
		scanf("%d",&p->count);
			if(p->count<0) {
				printf("输入数量格式有误\n");
				break;
			}
		printf("\n");
		po->next=p;
		po=p;//实现让po指向p的空间
		printf("===============================================\n");
		printf("是否退出创建货物信息 退出: 输入1 继续: 输入2\n");
		scanf("%d",&n);
		if(n==1) {
			po->next=NULL;//不再创建信息，成为尾结点
			p=NULL;
			return (head);
		}
		printf("\n");
		if(n>2) {
			printf("输入错误!\n");
			system("pause");//暂停
			break;
		}
	}
	po->next=NULL;
	free(p);
	p=NULL;//让p重新指向空
	return (head);
}
//保存信息功能
void baocun(a1 *head) { //从头指针开始
	int m;//标记
	m=0;
	a1 *p=NULL;
	FILE *z;//文件指针
	p=head->next;//p 第一结点 
	if(p==NULL) {
		printf("未创建货物信息,无法保存\n");
	} else if(p!=NULL) {
		p=head->next;//p从第一个结点开始
		if((z=fopen("货物信息.txt","w"))==NULL) { //创建货物信息文件， 只写
			printf("无法打开此货物文件\n");
			exit(0);//若空，终止
		}
		while(p!=NULL) {
			fprintf(z,"编号:%d\t",p->number);//格式化输出  以文件为对象 
			fprintf(z,"名称:%s\t",p->name);
			fprintf(z,"价格:%f\t",p->price);
			fprintf(z,"数量:%d\n",p->count);
			p=p->next;//p后移
			m++;//标记作用
		}
		printf("保存成功! 共保存%d个货物信息\n",m);
		fclose(z);//关闭文件;
	}
}
//查找功能
void search(a1 *head) {
	a1 *p=NULL;
	char name0[100];
	p=head->next;
	int n;
	int x;
	if(p!=NULL) {
		printf("\t\t\t请选择查找方式\n");//查找方式
		printf("\t\t\t1.通过货物编号查找  2.通过货物名称查找\n");
		printf("========================================\n");
		printf("请输入查找方式:1或2\n");
		scanf("%d",&n);
		switch(n) {
			case 1:
				printf("请输入查找的货物编号:\n");
				scanf("%d",&x);
				while(p!=NULL) {
					if(x==p->number) {
						printf("要查找的货物的信息为:\n");
						printf("编号: %d\n",p->number);
						printf("名称: %s\n",p->name);
						printf("价格: %f\n",p->price);
						printf("数量: %d\n",p->count);
						printf("查找成功\n");
						break;//防止无限查找
					}
					printf("\n");
					p=p->next;
				}
				break;//case1的break
			case 2:
				printf("请输入要查找的货物名称:\n");
				scanf("%s",&name0);
				while(p!=NULL) {
					if(strcmp(name0,p->name)==0) {
						printf("要查找的货物信息为:\n");
						printf("编号: %d\n",p->number);
						printf("名称: %s\n",p->name);
						printf("价格: %f\n",p->price);
						printf("数量: %d\n",p->count);
						printf("查找成功!\n");
						break;
					}
					printf("\n");
					p=p->next;
				}
				break;//case2的break
			default:
				printf("查找方式有误!\n");
		}
	} else
		printf("未录入信息，无法查找\n");
}
//添加信息功能
void add(a1 *head) {
	a1 *p=NULL;
	a1 *p1=NULL;
	p=head;//p 头指针
	while(p->next!=NULL) {
		p=p->next;
	}
	p1=(a1*)malloc(sizeof(a1));//开辟空间，给p1内存首地址
	printf("请输入要添加的货物信息:\n");
	printf("编号:");
	scanf("%d",&p1->number);
	printf("名称:");
	scanf("%s",&p1->name);
	printf("价格:");
	scanf("%f",&p1->price);
	printf("数量:");
	scanf("%d",&p1->count);
	printf("添加成功！\n");
	p->next=p1;//让p的下一个结点为p1
	p1->next=NULL;//p1为尾结点，添加完成
}
//修改信息功能
void correct(a1 *head) {
	a1 *p;
	a1 *w;
	w=head;
	p=NULL;
	char nameplus[100];//定义新变量名，存放修改的数据
	int numberplus;
	float priceplus;
	int countplus;
	int v;//下面用到的修改方式
	int numm;
	p=head->next;//p从第一个结点开始往后移
	while(head!=NULL) {
		if(p==NULL) {
			printf("未创建货物信息，无法修改\n");
			break;
		}
		printf("按照编号查找\n");
		printf("请输入要查找的编号：\n");
        scanf("%d",&numm);
			if(p->number==numm) {
				printf("已找到信息\n");
				printf("|编号\t|名称\t|价格\t\t|数量\t |\n");
				printf("|%d\t|%s\t|%f\t|%d\t |\n",p->number, p->name,p->price,p->count);
				printf("请进行修改\n");
				printf("编号:");
				scanf("%d",&p->number);			
				printf("名称");
				scanf("%s",&p->name);
				printf("价格:");
				scanf("%f",&p->price);
				printf("数量");
				scanf("%d",&p->count);
				printf("修改完成");
				break;
			} else {
				printf("未查找到该货物\n");
				break;
			}
 
		}
	printf("\n");
}
//删除信息功能
void cut(a1 *head,int number) {//以编号方式删除
	a1 *p,*q;
	p=head;
	int numberplusplus;
	if(p->next!=NULL) {
		printf("按货物编号删除:\n");
		printf("请输入货物编号:\n");
		scanf("%d",&numberplusplus);
		if(head==NULL) {
			printf("为空链表\n");
			return;
		}
		while(p->number!=numberplusplus&&p->next!=NULL) {
			q=p;//q后驱
			p=p->next;//p前驱
		}
		if(p->number==numberplusplus) {//如果编号对应的话
			if(p==head) {//如果找到的是头结点
				head=p->next;//头指针后移
			} else {//如果不是头结点
				q->next=p->next;//越过p结点
			}
			free(p);
			printf("删除成功\n");
		} else {
			printf("没有此货物:\n");
		}
	} else
		printf("未创建货物信息，无法删除\n");
}
//显示信息功能
void out(a1 *head) {
	a1 *p=NULL;
	p=head->next;//指向第一个结点
	if(p!=NULL) {
		while(p!=NULL) {
			printf("__________________________________________\n");
			printf("|编号\t|名称\t|价格\t\t|数量\t |\n");
			printf("|________________________________________|\n");
			printf("|%d\t|%s\t|%f\t|%d\t |\n",p->number, p->name,p->price,p->count);
			printf("|________________________________________|\n");
			p=p->next;//按顺序输出
		}
	} else printf("未创建货物信息，无法显示\n");
}
//读取功能
a1 *in() {
	FILE *z;
	a1 *head,*p,*w;
	if((z=fopen("货物信息.txt","r")) == NULL) { //打开txt文件  只读
		printf("不能打开文件！\n");
	}
	head=(a1 *)malloc(sizeof(a1)); //申请空间,获得首地址
	head->next=NULL;
	p=(a1 *)malloc(sizeof(a1));
	int m=0;
	while(fread(p,sizeof(a1),1,z)) { //读取文件信息。fread函数若执行成功，那么返回值为count（数据项的个数）
		m=m+1;
		p->next=NULL;//输出
		printf("编号:%d\t名称:%s\t价格%f\t数量:%d\t\n",p->number, p->name,p->price,p->count);
		getchar();
		if(m==1) {//如果只有一组信息，即只有一个结点
			head->next=p;
		} else {
			w->next=p;//多组信息
		}
		w=p;//让w指向p的空间
		p=(a1 *)malloc(sizeof(a1));//重新得到起始地址
	}
	fclose(z);
	return head;
}
//排序
void sort(a1 *head) {
int i,cou=0;//cou：结点数 
int num;//内循环 
a1 *p,*q,*tail;
p=head;
if(head->next!=NULL)
{
	printf("按编号从小到大排序\n");
while(p->next!=NULL)//计算结点数 
{
	cou++;
	p=p->next;
}
for(i=0;i<cou-1;i++)
{
	num=cou-i-1;//内循环次数 
	q=head->next;//q指向第一个结点 
	p=q->next;//p指向p后一个结点 
	tail=head;//tail指向q前一个结点 
	while(num--)//内循环 
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
printf("排序成功\n");
}
else 
{
	printf("无货物信息\n");
}
}
 
//主函数开始
int main() {
	FILE *z;//文件指针
	int m;
	char n;
	int number;
	page();//调用页面函数
	getchar();//按enter下一步
	if((z=fopen("货物信息.txt","w"))!=NULL) {
		head=in();//读入
	} else {
		printf("文件中没有保存货物信息！\n");
	}
	while(1) {
		system("cls");//清屏
		menu();//调用目录函数
		scanf("%c",&n);
		switch(n) {
			case '1'://创建信息
				head=creat();
				break;
			case '2':// 保存信息
				baocun(head);
				break;
			case '3'://查询信息
				search(head);
				break;
			case '4'://修改信息
				out(head);
				correct(head);
				break;
			case '5'://删除信息
				cut(head,number);
				break;
			case '6'://输出信息
				out(head);
				break;
			case '7'://添存信息
				add(head);
				baocun(head);
				break;
			case '8'://排序
				sort(head);
				break;
			case '9'://增加信息 
				add(head);
				break;
			case '0'://退出程序
				break;
			default:
				printf("选择功能错误!\n");
		}
		printf("\n");
		printf("—————————————————————————————\n");
		printf("是否继续对该货物信息的操作，如果继续操作 输：1 退出输： 2 \n");
		printf("—————————————————————————————\n");
		scanf("%d",&m);
		getchar();
		if(m==2) {
			break;
		}
	}
	return 0;
}