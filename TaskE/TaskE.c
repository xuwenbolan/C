#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct string
{
    char *str;
    struct string *next;
} LinkList;

int main()
{
    t6();
	return 0;
}

void t1(char *a,int n)
{
	for (int i = n-1; i >0; i--)
	{
		int ifwap = 0;
		for (int j = 0; j< i; j++)
		{
			if (*(a+j)>*(a+j+1))
			{
				int t;
				t = *(a + j);
				*(a+j) = *(a + j + 1);
				*(a + j + 1) = t;
				ifwap = 1;
			}
		}
		if (ifwap == 0)return;
	}
}




char *t2(char *a)
{
	int i;
	char *p = a;
	for (i = 0; *(p+i) != 0; i++)
	{
		if (*(p+i) >= 97 && *(p+i) <= 122)
		{
			*(p+i) -= 32;
		}
	}
	return p;
}


void t3()
{
    printf("当前为第3题！\n");
    int a[4][5] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
    int *p1, **p2, (*p3)[5], *p4[4];
    p1 = a[0];
    p2 = p4;
    p3 = a;
    p4[0] = a[0];
    p4[1] = a[1];
    p4[2] = a[2];
    p4[3] = a[3];

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            printf("%-3d%-3d%-3d%-3d", *(p1++), p2[i][j], p3[i][j], p4[i][j]);
            printf("\n");
        }
    }
}

void t4()
{
     printf("当前为第4题！\n");
    int a[3][4][5] = {0}, *p1 = a, **p2, (*p3)[5], *p4[4];
    for (int i = 1; i <= 60; i++)
        *(p1 + i - 1) = i;

    for (int i = 0; i < 3; i++)
    {
        p1 = a[i];
        p2 = p4;
        p3 = a[i];
        p4[0] = p1;
        p4[1] = p1 + 5;
        p4[2] = p1 + 10;
        p4[3] = p1 + 15;
        for (int k = 0; k < 4; k++)
        {
            for (int j = 0; j < 5; j++)
            {
                printf("%-3d%-3d%-3d%-3d", *(p1++), p2[k][j], p3[k][j], p4[k][j]);
                printf("\n");
            }
        }
    }

    return 0;
}

void t6()
{
     printf("当前为第6题！\n");
    char temp[50] = {0};
    LinkList *head, *node, *end;
    head = (LinkList *)malloc(sizeof(LinkList));
    end = head;
    while (1)
    {
        node = (LinkList *)malloc(sizeof(LinkList));
        gets(temp);
        if (temp[0] == 0)
            break;
        node->str = (char *)malloc(strlen(temp) + 1);
        strcpy(node->str, temp);
        end->next = node;
        end = node;
    }
    end->next = NULL;

    while (head->next != NULL)
    {
        head = head->next;
        printf("%s", head->str);
    }
    printf("\n");
    return 0;
}