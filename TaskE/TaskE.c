#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//T6
typedef struct string
{
    char *str;
    struct string *next;
} LinkList;//采用链表

int main()
{
    char temp[50]={0};
    LinkList *head, *node, *end;
	head = (LinkList*)malloc(sizeof(LinkList));
	end = head;
	while(1)
    {
		node = (LinkList*)malloc(sizeof(LinkList));
        gets(temp);
        if(temp[0]==0)break;
        node->str=(char*)malloc(strlen(temp)+1);
        strcpy(node->str,temp);
		end->next = node;
		end = node;
	}
	end->next = NULL;

    while (head->next != NULL) 
    {
		head = head->next;
		printf("%s", head->str);
	}
    return 0;
}

/* T4
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
*/