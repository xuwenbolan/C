#include <stdio.h>
#include <conio.h>
#include <string.h>
int aa[200];
float ff[200];
char cc[200];
char str[200][50];

void ReadFromFile(char filename[])
{
    FILE *fp=fopen(filename,"r");
    int a;
    float f;
    char c;
    char string[50];
    if (fp==NULL){
        printf("open read file error\n");
        return;
    }
    int i=0;
    while(fscanf(fp,"%d,%f,%c,%s",&a,&f,&c,string)!=EOF){   
        printf("%d,%.2f,%c,%s\n",a,f,c,string);
        // aa[i]=a;ff[i]=f;cc[i]=c;
        // strcpy(str[i],string);
        // ++i;
    }
    fclose(fp);
}
void AddOneReocrdToFile(char filename[])
{
    FILE *fp=fopen(filename,"a");
    int a;
    float b;
    char c;
    char string[50];
    if (fp==NULL){
        printf("open write file error\n");
        return;
    }
    printf("Input new datas:");
    scanf("%d,%f,%c,%s",&a,&b,&c,string);
    fprintf(fp,"%d,%.2f,%c,%s\n",a,b,c,string);    //记得带\n
    fclose(fp);
}


int main()
{
    char savefilename[]="savedata.txt"; //"D:\\C_example\\savedata.txt"
    for(;;){
        printf("\n=======================\n");
        printf("Read Data from file [R]\n");
        printf("Write data to file  [W]\n");
        printf("Exit. [Q]\n");
        printf("========================\n");
        switch(getch()){
            case 'R':
            case 'r':
                ReadFromFile(savefilename);
                break;
            case 'w':
            case 'W':
                AddOneReocrdToFile(savefilename);
                break;
            case 'Q':
            case 'q':
                return 0;
        }
    }
}