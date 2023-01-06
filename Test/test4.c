#include <stdio.h>

void filew(const char* filename);

int main()
{
    FILE *fp = NULL;
    int a=0;
    float d=0;
    char data[255]={0},b[100]={0},c[100]={0};
    fopen_s(&fp,"test.txt", "r");
    fscanf_s(fp, "%s %d %s %s %f",data,20,&a,b,20,c,20,&d);//读取一段字符串以空格结束
    printf("1: %s\n",data);
    printf("2: %d\n",a);
    printf("3: %s\n",b);
    printf("4: %s\n",c);
    printf("5: %.2f\n",d);
    fclose(fp);

    return 0;
}

void filew(const char* filename)//文件写入
{
	FILE* pf;
	fopen_s(&pf, filename, "w");
	fprintf(pf,"KSDBNGIBDSIOGSPFBOI");
	fclose(pf);
}