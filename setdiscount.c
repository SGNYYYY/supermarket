#include <stdio.h>
#include <stdlib.h>
#include "setdiscount.h"
#include <math.h>


void SetDiscountMenu() {
    SetPos(titleX, titleY);
    printf("折 扣 功 能");
    SetPos(menuX, menuY);
    printf("1 设置折扣");
    SetPos(menuX, menuY + 1);
    printf("2 重置所有折扣");
    SetPos(menuX, menuY + 2);
    printf("0 返回主菜单");
    SetPos(menuX, menuY + 3);
    printf("请输入选择：");
}

void InDiscount(Goods *G_Head) {
    system("cls");

    SetPos(titleX, titleY);
    printf("请输入要设置折扣的商品货号与折扣");
    SetPos(titleX, titleY+1);
    printf("例：12345  8.5意即将货号为12345的商品设置为八五折");
    SetPos(titleX, titleY + 2);
    printf("货号：");
    SetPos(titleX, titleY + 3);
    printf("折扣：  . 折");

    int id = 0, isnum = 2, isfive = 0;
    char c;
    double dis = 0;

    SetPos(titleX+8, titleY+2);//输入货号 int
    while (1)
    {
        SetPos(titleX + 8, titleY + 2);
        id = isfive = isnum = 0;
        while ((c = getchar()) != '\n')
        {
            if (c >= '0' && c <= '9')
            {
                id = id * 10 + c - '0';
            }
            else { isnum = 1; }
            isfive++;
        }
        if (isfive > 5 || isnum != 0 || isfive == 0) //控制长度与是否为数字
        {
            SetPos(titleX + 8, titleY + 2);
            int i;
            for (i = 0; i < isfive; i++)printf(" ");
            SetPos(titleX + 8, titleY + 2);
            printf("非法输入:请重新输入");
            Sleep(1000);
            SetPos(titleX + 0, titleY + 2);
            printf("货号：                              ");
        }
        else { break; }
    }

    SetPos(titleX+7, titleY+3);//输入折扣 小数点前
    while (1)
    {
        SetPos(titleX + 7, titleY + 3);
        dis = isfive = isnum = 0;
        while ((c = getchar()) != '\n')
        {
            if (c >= '0' && c <= '9') { dis = dis * 10 + c - '0'; }
            else { isnum = 1; }
            isfive++;
        }
        if (isnum != 0 || isfive != 1) //控制长度与是否为数字
        {
            SetPos(titleX + 7, titleY + 3);
            int i;
            for (i = 0; i < isfive; i++)printf(" ");
            SetPos(titleX + 7, titleY + 3);
            printf("非法输入:请重新输入");
            Sleep(1000);
            SetPos(titleX + 0, titleY + 3);
            printf("折扣：  . 折                      ");
        }
        else { break; }
    }

    SetPos(titleX + 9, titleY + 3);//输入折扣 小数点后
    while (1)
    {
        SetPos(titleX + 9, titleY + 3);
        float s = 0;
        isfive = isnum = 0;
        while ((c = getchar()) != '\n')
        {
            if (c >= '0' && c <= '9') //小数点后数字处理方法
            {
                float  i = 0;
                for (i = 0; i < isfive + 1; i++)s = s + (c - '0') / pow(10,isfive+1);

            }
            else { isnum = 1; }
            isfive++;
        }
        if (isfive != 1 || isnum != 0 || isfive != 1) //控制长度与是否为数字
        {
            SetPos(titleX + 9, titleY + 3);
            int i;
            for (i = 0; i < isfive; i++)printf(" ");
            SetPos(titleX + 9, titleY + 3);
            printf("非法输入:请输入小数点后一位");
            Sleep(1000);
            SetPos(titleX + 9, titleY + 3);
            printf("  折                         ");
        }
        else {
            dis = dis + s;
            break;
        }
    }

    Goods *temp;
    temp = FindByID_2(id, G_Head);
    SetPos(titleX + 0, titleY + 4);
    if (temp == NULL)
    {
        printf("未存在该商品，请检查货号。");
    }
    else
    { 
        temp->discount = dis;
        printf("商品 %s 已设置为%.1f折。", temp->name, dis);
    }
    Sleep(2000);
    WriteGoods(G_Head);
}

void DeleteDiscount(Goods *G_Head) {
    system("cls");
    int isfive, isnum;
    char t, c;
    SetPos(titleX, titleY);
    printf("确定要清除所有折扣吗?Y/N");
    SetPos(titleX + 25, titleY);//输入Y/N
    while (1) {
        SetPos(titleX + 25, titleY + 0);
        isfive = isnum = 0;

        while ((t = getchar()) != '\n') {
            c = t;
        }
        if (c != 'N' && c != 'Y'&&c!='n'&&c!='y')//控制长度与是否为数字
        {
            SetPos(titleX + 25, titleY + 0);
            printf("非法输入:请重新输入");
            Sleep(1000);
            SetPos(titleX + 25, titleY + 0);
            printf("                              ");
        }
        else { break; }
    }
    if (c == 'N'||c=='n')
    {
        SetPos(titleX, titleY+1);
        printf("已取消清除折扣操作。");
        Sleep(2000);
        return ;
    }
    else
    {
        Goods *temp = G_Head;
        while (temp) {
            temp->discount = 10;
            temp = temp->next;
        }
        WriteGoods(G_Head);
        SetPos(titleX, titleY+1);
        printf("清除折扣操作成功。");
        Sleep(2000);
    }
    
}

void SetDiscountMain(Goods *G_Head) {
    int choice = 1;
    while (choice) {
        system("cls");
        choice = 0;
        SetDiscountMenu();
        choice = GetChoice();
        switch (choice) {
            case 1:
                InDiscount(G_Head);
                break;
            case 2:
                DeleteDiscount(G_Head);
                break;
            case 0:
                break;
        }//退出功能
    }
}