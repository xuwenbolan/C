#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <windows.h>
#define LEN sizeof(struct student)
struct student
{   
	long num;
    char name[100];
    struct student *next;
};


void  SaveNode( struct  student  *head, char *filename)
{
    struct  student *p;
    if (head ==NULL){
        printf("print nothing,data is NULL\n");
        return;
    }
    FILE *fp;
    fp=fopen(filename,"w");
    if (fp==NULL){
        printf("error to write !");
        return;
    }
    p=head;
    do{
        fprintf(fp,"%ld,%s\n", p->num, p->name);
        p=p->next;
    } while(p !=NULL);
    printf("save node datas to <%s>....Ok\n",filename);
    fclose(fp);
}

void PrintNode(struct  student  *head)
{
   struct  student *p=head;
   int n=0;
   if (head==NULL){
       printf("\n List is NULL\n");
       return;
   }
   do{
        printf("%2d---%ld,%s\n", ++n,p->num, p->name);
        p=p->next;
   } while(p !=NULL);
}

void PrintNode2(struct  student  *head,long thenum)
{
   struct  student *p=head;
   int n=0;
   if (head==NULL){
       printf("\n List is NULL\n");
       return;
   }
   do{  
        if(p->num==thenum) printf("%2d---%ld,%s\n", ++n,p->num, p->name);
        p=p->next;
   } while(p !=NULL);
}


struct student *AddNewNode(struct student *head,struct student *newNode)
{
    struct student *p=head;
    if (head==NULL){
        head=newNode;
        newNode->next=NULL;
        return head;
    }
    while (p->next!=NULL){
        p=p->next;
    }
    p->next=newNode;
    newNode->next=NULL;
    return head;
}

struct student *AddNewNodeFromFile(struct student *head,char *filename)
{
    struct student *p;
    FILE *fp;
    printf("Get data from file: %s...\n",filename);
    fp=fopen(filename,"r");
    if (fp==NULL) { 
        printf("open file error!\n");
        return head;
    }
    p=( struct student *) malloc(LEN);
    while(fscanf(fp,"%ld,%s",&p->num, p->name)!=EOF){
        head=AddNewNode(head,p);
        p=( struct student *) malloc(LEN);
    }
    fclose(fp);
    return head;
}

struct student *AddNewNodeFromKeyboard(struct student *head)
{
    struct student *p;
    for (;;){
        p=( struct student *) malloc(LEN);
        printf("input new datas (End:0,0):\n");
        scanf("%ld,%s",&p->num,p->name);
        if (p->num==0){
            free(p);
            break;
        }
        head=AddNewNode(head,p);
    }
    return head;
}


void ListSort(struct student *head)   //排序
{                            
    int i,t,num=0;
    struct student *p;
    char buf[100];
    for (p=head; p!=NULL;p=p->next) num++;
    for (i=0;i<num-1;i++) {
        p=head;
        while (p->next != NULL) {
            if (p->num > p->next->num) {
                t = p->num;            //交换数据1
                p->num = p->next->num;
                p->next->num = t;          
                strcpy(buf,p->name);   //交换数据2
                strcpy(p->name,p->next->name);
                strcpy(p->next->name,buf);
            }
            p=p->next;
        }
    }
   
}                 

void DisplayMenu()
{
    printf("\n=====[ver 1.0 Menu]=============\n");
    printf("[A]-Display Current all Nodes\n");
    printf("[B]-Add New Node Datas\n");
    printf("[C]-reLoad Node Datas From File\n");
    printf("[D]-Save Node Datas to File\n");
    printf("[E]-Sort Node Link-List\n");
    printf("[F]-Reserver\n");
    printf("[Q]-Quit\n");
    printf("=================================\n");
}

int main(void)
{
    struct student *nodehead=NULL;
    char readFilename[30]="data.txt";
    char saveFilename[30]="";
    long thenum;
    system("cls");
    nodehead=AddNewNodeFromFile(nodehead,readFilename);//creatFromFile(readFilename);
    PrintNode(nodehead);
    
    for(;;){
        DisplayMenu();
        switch(getch()){
            case 'A':
            case 'a':
                PrintNode(nodehead);
                break;
            case 'B':
            case 'b':
                nodehead=AddNewNodeFromKeyboard(nodehead);
                PrintNode(nodehead);
                break;
            case 'C':
            case 'c':
                nodehead=NULL;
                nodehead=AddNewNodeFromFile(nodehead,readFilename);
                PrintNode(nodehead);
                break;
            case 'D':
            case 'd':
                printf("input the filename (data.txt):");
                gets(saveFilename);
                if (strlen(saveFilename)==0)strcpy(saveFilename,readFilename);
                SaveNode(nodehead, saveFilename);
                break; 
            case 'E':
            case 'e':
                ListSort(nodehead);
                PrintNode(nodehead);
                break; 
            case 'F':
            case 'f':
                //printf("is [F]\n");  //预留
                printf("Input the num:");
                scanf("%ld",&thenum);
                PrintNode2(nodehead,thenum);
                break; 
            case 'Q':
            case 'q':
                printf("\nbye!\n");
                return(0);
        }
        fflush(stdin);
    }
    return 0;
}
