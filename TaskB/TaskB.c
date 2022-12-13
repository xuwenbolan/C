#include <stdio.h>
#include <string.h>

void getnext(int next[], char p[]);
void KMP(char t[],char p[],int d[]);

int main()
{
  char t[100]={0},p[50],c[50];
  int d[50]={0};
  printf("Input the String 1:");
  scanf("%s",t);
  printf("Input the String 2:");
  scanf("%s",p);
  printf("Input the String 3:");
  scanf("%s",c);
  KMP(t,p,d);
  int a,b;
  for(int i=d[0];i>=1;i--)
  {
    a=d[i];
    b=strlen(c)-strlen(p);
    if(b>0) for(int j=strlen(t);j>=a;j--) t[j+b]=t[j];
    if(b<0) for(int j=a;j<=strlen(t);j++) t[j]=t[j-b];
    for(int j=0;j<strlen(c);j++,a++) t[a]=c[j];
  }
  printf("%s",t);

}

void KMP(char t[],char p[],int d[])
{
  int next[strlen(p)];
  int i = 0,j = 0,b=1;
  int a =strlen(p);
  getnext(next, p);
  while (i <= strlen(t) && j <= a)
  {
    if(j==a)
    {
      d[0]=b;
      d[b]=(i-j);
      b++;
      j=0;
    }

    if (j == -1 || t[i] == p[j])
    {
      i++;
      j++;
    }
    else j = next[j];
  }
}

void getnext(int next[], char p[])
{
  next[0] = -1;
  int j = 0;
  int k = -1;
  while (j < strlen(p) - 1)
  {
    if (k == -1 || p[j] == p[k])
    {
      if (p[++j] == p[++k])next[j] = next[k];
      else next[j] = k;
    }
    else k = next[k];
  }
}


// T4
/*
  char chuan1[2000] = {0};
  char chuan2[2000] = {0};
  char chuan3[2000] = {0};
  char chuan4[2000] = {0}; //临时数组
  gets(chuan1);
  gets(chuan2);
  gets(chuan3);
  int a = strlen(chuan1); //计算chuan1长度
  int b = strlen(chuan2); //计算chuan2长度
  int c = strlen(chuan3);
  int i, j, m, n;
  int k = 0;
  for (i = 0; i < a; i++)
  { //遍历数组1
    for (j = 0; chuan1[i + j] != 0 && chuan2[j] != 0; j++)
    {
      if (chuan1[i + j] == chuan2[j])
      {
        k++; //用来判断长度是否和chuan2相同
      }
      else
        break;
    } //判断重叠部分
    if (k == b)
    {        //如果重叠
      n = i; //找到i

      for (j = 0; chuan1[n + j] != '\0'; j++)
      { //保存到临时数组chuan4
        chuan4[j] = chuan1[n + b + j];
      }
      strcpy(chuan1 + n, chuan3);     //移动chuan3
      strcpy(chuan1 + n + c, chuan4); //移动chuan4
    }
    k = 0;
  }
  for (i = 0;chuan1[i]!=0; i++)
  {
    printf("%c", chuan1[i]);
  }
  return 0;
*/

// T4
/*#include <stdio.h>
#include <string.h>

void getnext(int next[], char p[]);
void KMP(char t[],char p[],int d[]);

int main()
{
  char t[100]={0},p[50],c[50];
  int d[100]={};
  printf("Input the String 1:");
  scanf("%s",t);
  printf("Input the String 2:");
  scanf("%s",p);
  printf("Input the String 3:");
  scanf("%s",c);
  KMP(t,p,d);
  int a,b;
  for(int i=d[0];i>=1;i--)
  {
    a=d[i];;
    b=strlen(c)-strlen(p);
    if(b>0) for(int j=strlen(t);j>=a;j--) t[j+b]=t[j];
    if(b<0)
    {
      for(int j=a;j<=strlen(t);j++)
      {
        t[j]=t[j-b];
      }
    }
    for(int j=0;j<strlen(c);j++,a++) t[a]=c[j];
  }
  printf("%s",t);



}

void KMP(char t[],char p[],int d[])
{
  int next[strlen(p)];
  int b=1;
  int i = 0; // 主串的位置
  int j = 0; // 模式串的位置
  int a =strlen(p);
  getnext(next, p);
  while (i <= strlen(t) && j <= a)
  {
    if(j==a)
    {
      d[0]=b;
      d[b]=(i-j);
      b++;
      j=0;
    }

    if (j == -1 || t[i] == p[j])
    { // 当j为-1时，要移动的是i，当然j也要归0

      i++;

      j++;
    }
    else
    {

      j = next[j]; // j回到指定位置
    }
  }
}

void getnext(int next[], char p[])
{
  next[0] = -1;

  int j = 0;

  int k = -1;

  while (j < strlen(p) - 1)
  {

    if (k == -1 || p[j] == p[k])
    {
      if (p[++j] == p[++k])
      {

        next[j] = next[k];
      }
      else
      {

        next[j] = k;
      }
    }
    else
    {

      k = next[k];
    }
  }
}*/

// T5
/*char a0[8][8]={
    {' ','*','*','*','*','*','*',' '},
    {'*',' ',' ',' ',' ',' ',' ','*'},
    {'*',' ',' ',' ',' ',' ',' ','*'},
    {'*',' ',' ',' ',' ',' ',' ','*'},
    {'*',' ',' ',' ',' ',' ',' ','*'},
    {'*',' ',' ',' ',' ',' ',' ','*'},
    {'*',' ',' ',' ',' ',' ',' ','*'},
    {' ','*','*','*','*','*','*',' '}};
  char a1[8][8]={
    {' ',' ',' ','*','*',' ',' ',' '},
    {' ',' ','*','*','*',' ',' ',' '},
    {' ',' ',' ','*','*',' ',' ',' '},
    {' ',' ',' ','*','*',' ',' ',' '},
    {' ',' ',' ','*','*',' ',' ',' '},
    {' ',' ',' ','*','*',' ',' ',' '},
    {' ',' ',' ','*','*',' ',' ',' '},
    {'*','*','*','*','*','*','*','*'}};
  char a2[8][8]={
    {' ','*','*','*','*','*','*',' '},
    {' ',' ',' ',' ',' ',' ',' ','*'},
    {' ',' ',' ',' ',' ',' ',' ','*'},
    {' ','*','*','*','*','*','*',' '},
    {'*',' ',' ',' ',' ',' ',' ',' '},
    {'*',' ',' ',' ',' ',' ',' ',' '},
    {'*',' ',' ',' ',' ',' ',' ',' '},
    {' ','*','*','*','*','*','*',' '}};
  char a3[8][8]={
    {' ','*','*','*','*','*','*',' '},
    {' ',' ',' ',' ',' ',' ',' ','*'},
    {' ',' ',' ',' ',' ',' ',' ','*'},
    {' ','*','*','*','*','*','*',' '},
    {' ',' ',' ',' ',' ',' ',' ','*'},
    {' ',' ',' ',' ',' ',' ',' ','*'},
    {' ',' ',' ',' ',' ',' ',' ','*'},
    {' ','*','*','*','*','*','*',' '}};
  char a4[8][8]={
    {'*',' ',' ',' ',' ',' ',' ','*'},
    {'*',' ',' ',' ',' ',' ',' ','*'},
    {'*',' ',' ',' ',' ',' ',' ','*'},
    {'*','*','*','*','*','*','*','*'},
    {' ',' ',' ',' ',' ',' ',' ','*'},
    {' ',' ',' ',' ',' ',' ',' ','*'},
    {' ',' ',' ',' ',' ',' ',' ','*'},
    {' ',' ',' ',' ',' ',' ',' ','*'}};
  char a5[8][8]={
    {' ','*','*','*','*','*','*',' '},
    {'*',' ',' ',' ',' ',' ',' ',' '},
    {'*',' ',' ',' ',' ',' ',' ',' '},
    {' ','*','*','*','*','*','*',' '},
    {' ',' ',' ',' ',' ',' ',' ','*'},
    {' ',' ',' ',' ',' ',' ',' ','*'},
    {' ',' ',' ',' ',' ',' ',' ','*'},
    {' ','*','*','*','*','*','*',' '}};
  char a6[8][8]={
    {' ','*','*','*','*','*','*',' '},
    {'*',' ',' ',' ',' ',' ',' ',' '},
    {'*',' ',' ',' ',' ',' ',' ',' '},
    {' ','*','*','*','*','*','*',' '},
    {'*',' ',' ',' ',' ',' ',' ','*'},
    {'*',' ',' ',' ',' ',' ',' ','*'},
    {'*',' ',' ',' ',' ',' ',' ','*'},
    {' ','*','*','*','*','*','*',' '}};
  char a7[8][8]={
    {'*','*','*','*','*','*','*',' '},
    {' ',' ',' ',' ',' ',' ',' ','*'},
    {' ',' ',' ',' ',' ',' ',' ','*'},
    {' ',' ',' ',' ',' ',' ',' ','*'},
    {' ',' ',' ',' ',' ',' ',' ','*'},
    {' ',' ',' ',' ',' ',' ',' ','*'},
    {' ',' ',' ',' ',' ',' ',' ','*'},
    {' ',' ',' ',' ',' ',' ',' ','*'}};
  char a8[8][8]={
    {' ','*','*','*','*','*','*',' '},
    {'*',' ',' ',' ',' ',' ',' ','*'},
    {'*',' ',' ',' ',' ',' ',' ','*'},
    {' ','*','*','*','*','*','*',' '},
    {'*',' ',' ',' ',' ',' ',' ','*'},
    {'*',' ',' ',' ',' ',' ',' ','*'},
    {'*',' ',' ',' ',' ',' ',' ','*'},
    {' ','*','*','*','*','*','*',' '}};
  char a9[8][8]={
    {' ','*','*','*','*','*','*',' '},
    {'*',' ',' ',' ',' ',' ',' ','*'},
    {'*',' ',' ',' ',' ',' ',' ','*'},
    {' ','*','*','*','*','*','*',' '},
    {' ',' ',' ',' ',' ',' ',' ','*'},
    {' ',' ',' ',' ',' ',' ',' ','*'},
    {' ',' ',' ',' ',' ',' ',' ','*'},
    {' ','*','*','*','*','*','*',' '}};
  char c,num[100],d[8][8];
  int n;
  printf("please input:");

  for (n = 0; n < 200; n++)
  {
    c = getchar();
    if (c == '\n')
      break;
    num[n] = c;
  }

    for(int i=0;i<8;i++)
  {
    for(int j=0;j<n;j++)
    {
      for(int k=0;k<8;k++)
      {
          switch (num[j])
        {
        case '0':
          printf("%c",a0[i][k]);
          break;
        case '1':
          printf("%c",a1[i][k]);
          break;
        case '2':
          printf("%c",a2[i][k]);
          break;
        case '3':
          printf("%c",a3[i][k]);
          break;
        case '4':
          printf("%c",a4[i][k]);
          break;
        case '5':
          printf("%c",a5[i][k]);
          break;
        case '6':
          printf("%c",a6[i][k]);
          break;
        case '7':
          printf("%c",a7[i][k]);
          break;
        case '8':
          printf("%c",a8[i][k]);
          break;
        case '9':
          printf("%c",a9[i][k]);
          break;
        }
      }
      printf(" ");
    }
    printf("\n");
  }
  return 0;*/

// T3
/*void cat(char *a,char *b);
int main()
{
  char a[100]={0},b[100],c[100];
  printf("input str1:"); gets(a);
  printf("input str2:"); gets(b);
  printf("input str3:"); gets(c);
  cat(a,b);
  cat(a,c);
  printf("%s",a);
  return 0;
}

void cat(char *a,char *b)
{
  int len=strlen(a);
  for(int i=0;i<strlen(b);i++)
  {
    a[len+i]=b[i];
  }
}*/

// T2
/*float nums[4][6];
  for(int i=1;i<=4;i++)
  {
    float sum=1;
    for(int j=1;j<=6;j++)
    {
      nums[i-1][j-1]=i+(float)j/10;
      sum*=nums[i-1][j-1];
      printf("%.1f\t",nums[i-1][j-1]);
    }
    printf("%.1f\t\n",sum);
  }
  for(int i=0;i<6;i++)
  {
    float sum=1;
    for(int j=0;j<4;j++)
    {
      sum*=nums[j][i];
    }
    printf("%.1f\t",sum);
  }
  printf("sum");*/

// T1
/* char a[200]={0},t;
  int len, j, i;
  printf("input:");
  gets(a);
  len=strlen(a)-1;
  printf("length=%d\n",len);
  for (j = 0; j < len; j++)
    for (i = 0; i < len - j; i++)
    {
      if (a[i] > a[i + 1])
      {
        t = a[i];
        a[i] = a[i + 1];
        a[i + 1] = t;
      }
    }
  printf("%s", a);*/