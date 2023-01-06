#include "warehouse.h"

int main()
{
    Goods_read(G_head);
    return 0;
}

void Add_point(G_Point* headpoint,Goods point)
{
    G_Point* node =(G_Point*)malloc(sizeof(G_Point));
    node->goods=point;
    if(headpoint==NULL) node->next=NULL;
    else node->next=headpoint;
    headpoint=node;
}

void Goods_read(G_Point* headpoint)
{
    FILE *fp = NULL;
    Goods temp;
    fopen_s(&fp,"Goods_data.txt","r");
    if(fp==NULL)fopen_s(&fp,"Goods_data.txt","w");
    while(fscanf(fp,"%s %s %s %s %s %d %f",temp.name,temp.date,temp.place,temp.sup_unit,temp.phone,&temp.num,&temp.price)!=EOF)
    {
        Add_point(headpoint,temp);
    }
    printf("%s %s %s %s %s %d %f",temp.name,temp.date,temp.place,temp.sup_unit,temp.phone,temp.num,temp.price);
    fclose(fp);
}