#include <stdio.h>
#include <stdlib.h>

typedef struct student
{
    char name[10];
    char major[20];
    char type[10];
    char std_num[10];
    char id_num[10];
    int a1;
    int a2;
    int a3;
    int a4;
    int a5;
    int a6;
    int a7;
} std;

typedef struct _point
{
    std people;
    struct _point *next;
} point;

int main()
{
    FILE *pf = NULL;
    point *head = NULL;
    point *node;
    std temp;
    fopen_s(&pf, "s-m-s.txt", "r");
    if (pf == NULL)
        printf("NULL");
    while (fscanf(pf, "%s %s %s %s %s %d %d %d %d %d %d %d", temp.name, temp.major, temp.type, temp.std_num, temp.id_num, &temp.a1, &temp.a2, &temp.a3, &temp.a4, &temp.a5, &temp.a6, &temp.a7) != EOF)
    {
        node = (point *)malloc(sizeof(point));
        if (head == NULL)
        {
            node->next = NULL;
            head = node;
        }
        else
        {
            node->next = head;
            head = node;
        }
        node->people = temp;
    }
    fclose(pf);
    point *p = head;
    while (p)
    {
        printf("%s\n", p->people.name);
        p = p->next;
    }
    return 0;
}