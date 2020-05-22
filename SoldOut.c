#include "SoldOut.h"
#include <stdio.h>
#include "ChangeGoodsInfo.h"

void DeleteMain(Goods *G_Head)
{
	int choice;
    while (1)
	{
        system("cls");
        SetPos(titleX, titleY);
        printf("商品下架菜单");
        SetPos(menuX, menuY);
        printf("1.下架商品");
        SetPos(menuX, menuY + 1);
        printf("0.退出");
        SetPos(menuX, menuY + 2);
        printf("想输入您的选择：");
        choice=GetChoice();
        if (choice == 1)
		{
			Delete_1(G_Head);
			WriteGoods(G_Head);
		}
        else if (choice == 0) break;
    }
}

void Delete_1(Goods *G_Head)
{
	system("cls");
    int k = 0;
    Goods *p;
    Goods *Bp;
    p = G_Head->next;
    Bp = G_Head;
	SetPos(titleX, titleY);
    printf("请输入商品货号:");
    int id;
    id=GetId();
    while (p != NULL)
	{
        if (p->goods_id == id) {
			SetPos(menuX, menuY);
            printf("该商品的名称:%s", p->name);
			SetPos(menuX, menuY+1);
            printf("该商品的货号:%05d", p->goods_id);
			SetPos(menuX, menuY+2);
            printf("该商品的售货单价:%.2f", p->S_price);
			SetPos(menuX, menuY+3);
            printf("该商品的总数:%d", p->total_num);
			SetPos(menuX, menuY+4);
            printf("该商品的销量:%d", p->sales_volume);
			SetPos(menuX, menuY+5);
            printf("请确认是否删除该商品（删除请按1，放弃操作请按0）");
            k = 1;
            int j;
			while(1)
			{
			    j=GetChoice();
			    if(j==1)
                {
                    DeleteNode(Bp, p);
                    SetPos(menuX, menuY+6);
                    printf("商品已成功下架\n");
                    SetPos(menuX, menuY+7);
                    system("pause");
                    break;
                }
			    else if(j==0)
                {
                    SetPos(menuX, menuY+6);
					printf("放弃删除\n");
					SetPos(menuX, menuY+7);
					system("pause");
					break;
                }
				else
				{
					SetPos(menuX, menuY+6);
					printf("输入错误请重新输入");
				}
			}
			break;
        }
		else
		{
            p = p->next;
            Bp = Bp->next;
        }
    }
    if (0 == k)
	{
	    SetPos(menuX, menuY+3);
        printf("无此商品\n");
        SetPos(menuX, menuY+4);
        system("pause");
    }
}

void DeleteNode(Goods *Bp, Goods *p)
{
    Bp->next = p->next;
    free(p);
}
