///*1.5.4
//优化了操作逻辑和用户体验
//修复了已知bug*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "input.h"
#include <math.h>

void Search_This(in_Goods *inGoods_Head, int a, int b[]) {
    in_Goods *existence = inGoods_Head->next;
    while (existence != NULL) {
        if (a == existence->goods_id) {
            if (existence->P_num != 0) {
                b[0] += existence->P_num;
                b[1]++;
            }
        }
        existence = existence->next;
    }
}

int New_kind_of_good(Goods *G_Head)
{
    system("cls");
    SetPos(titleX + 0, titleY + 0);
    printf("建立该商品信息。");
    SetPos(titleX + 0, titleY + 1);
    printf("名称：");
    SetPos(titleX + 0, titleY + 2);
    printf("货号：");
    SetPos(titleX + 0, titleY + 3);
    printf("厂家：");
    SetPos(titleX + 0, titleY + 4);
    printf("保质期:      年    月    天");
    SetPos(titleX + 0, titleY + 5);
    printf("单位：");
    SetPos(titleX + 0, titleY + 6);
    printf("售货单价：      .  元");
    SetPos(titleX + 0, titleY + 7);
    printf("商品类别：");
    SetPos(titleX + 0, titleY + 8);
    printf("库存上限：");
    int Max = 0;
    int id = 0, isnum = 2, isfive = 0;
    char c;
    double pri = 0;
    char nam[20], manufacturer[20], uni[20], kin[20], temp[50];
    Date tim;
    tim.year = tim.month = tim.day = 0;

    SetPos(titleX + 9, titleY + 1);//输入名字 char
    while (1) {
        SetPos(titleX + 9, titleY + 1);
        memset(temp, 0, sizeof(temp));
        s_get(temp,50);
        if (strlen(temp) >= name_size || strlen(temp) < 1) {
            SetPos(titleX + 9, titleY + 1);
            int i;
            for (i = 0; i < strlen(temp); i++)
                printf("   ");
            SetPos(titleX + 9, titleY + 1);
            printf("非法输入:请重新输入        ");
            Sleep(1000);
            SetPos(titleX + 9, titleY + 1);
            printf("                               ");
        }
        else {
            strcpy(nam, temp);
            break;
        }
    }

    SetPos(titleX + 9, titleY + 2);//输入货号 int
    while (1)
    {
        SetPos(titleX + 9, titleY + 2);
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
            SetPos(titleX + 9, titleY + 2);
            int i;
            for (i = 0; i < isfive; i++)printf(" ");
            SetPos(titleX + 9, titleY + 2);
            printf("非法输入:请重新输入                             ");
            Sleep(1000);
            SetPos(titleX + 0, titleY + 2);
            printf("货号：                                                                          ");
        }
        else { break; }
    }
    Goods* position = FindByID_2(id, G_Head);
    if (position)
    {
        system("cls");
        SetPos(titleX + 0, titleY +0);
        printf("已存在该货号商品，请检查后再新建商品。");
        SetPos(titleX + 0, titleY +1);
        system("pause");
        return 0;
    }

    SetPos(titleX + 9, titleY + 3);//输入厂家 char
    while (1) {
        SetPos(titleX + 9, titleY + 3);
        memset(temp, 0, sizeof(temp));
        s_get(temp,50);
        if (strlen(temp) >= name_size || strlen(temp) < 1) {
            SetPos(titleX + 9, titleY + 3);
            int i;
            for (i = 0; i < strlen(temp); i++)
                printf("   ");
            SetPos(titleX + 9, titleY + 3);
            printf("非法输入:请重新输入");
            Sleep(1000);
            SetPos(titleX + 9, titleY + 3);
            printf("                          ");
        }
        else {
            strcpy(manufacturer, temp);
            break;
        }
    }

    SetPos(titleX + 9, titleY + 4);//输入保质期，年 int
    while (1)
    {
        SetPos(titleX + 9, titleY + 4);
        tim.year = isfive = isnum = 0;
        while ((c = getchar()) != '\n')
        {
            if (c >= '0' && c <= '9') { tim.year = tim.year * 10 + c - '0'; }
            else { isnum = 1; }
            isfive++;
        }
        if (isfive > 4 || isnum != 0 || isfive == 0) //控制长度与是否为数字
        {
            SetPos(titleX + 9, titleY + 4);
            int i;
            for (i = 0; i < isfive; i++)printf("   ");
            SetPos(titleX + 9, titleY + 4);
            printf("非法输入:请重新输入         ");
            Sleep(1000);
            SetPos(titleX + 0, titleY + 4);
            printf("保质期:      年    月    天                              ");
        }
        else { break; }
    }

    SetPos(titleX + 17, titleY + 4);//输入保质期，月 int
    while (1)
    {
        SetPos(titleX + 17, titleY + 4);
        tim.month = isfive = isnum = 0;
        while ((c = getchar()) != '\n')
        {
            if (c >= '0' && c <= '9') { tim.month = tim.month * 10 + c - '0'; }
            else { isnum = 1; }
            isfive++;
        }
        if (isfive > 2 || isnum != 0 || isfive == 0) //控制长度与是否为数字
        {
            SetPos(titleX + 17, titleY + 4);
            int i;
            for (i = 0; i < isfive; i++)printf("  ");
            SetPos(titleX + 15, titleY + 4);
            printf("非法输入:请重新输入        ");
            Sleep(1000);
            SetPos(titleX + 15, titleY + 4);
            printf("    月    天                          ");
        }
        else { break; }
    }

    SetPos(titleX + 23, titleY + 4);//输入保质期，天 int
    while (1)
    {
        SetPos(titleX + 23, titleY + 4);
        tim.day = isfive = isnum = 0;
        while ((c = getchar()) != '\n')
        {
            if (c >= '0' && c <= '9') { tim.day = tim.day * 10 + c - '0'; }
            else { isnum = 1; }
            isfive++;
        }
        if (isfive > 2 || isnum != 0 || isfive == 0) //控制长度与是否为数字
        {
            SetPos(titleX + 23, titleY + 4);
            int i;
            for (i = 0; i < isfive; i++)printf(" ");
            SetPos(titleX + 23, titleY + 4);
            printf("非法输入:请重新输入");
            Sleep(1000);
            SetPos(titleX + 21, titleY + 4);
            printf("    天                 ");
        }
        else { break; }
    }

    SetPos(titleX + 9, titleY + 5);//输入单位 char
    while (1) {
        SetPos(titleX + 9, titleY + 5);
        memset(temp, 0, sizeof(temp));
        s_get(temp,50);
        if (strlen(temp) >= name_size || strlen(temp) < 1) {
            SetPos(titleX + 9, titleY + 5);
            int i;
            for (i = 0; i < strlen(temp); i++)
                printf("   ");
            SetPos(titleX + 9, titleY + 5);
            printf("非法输入:请重新输入                      ");
            Sleep(1000);
            SetPos(titleX + 9, titleY + 5);
            printf("                                           ");
        }
        else {
            strcpy(uni, temp);
            break;
        }
    }

    SetPos(titleX + 11, titleY + 6);//输入价格 double（小数点前）
    while (1)
    {
        SetPos(titleX + 11, titleY + 6);
        pri = isfive = isnum = 0;
        while ((c = getchar()) != '\n')
        {
            if (c >= '0' && c <= '9') { pri = pri * 10 + c - '0'; }
            else { isnum = 1; }
            isfive++;
        }
        if (isnum != 0 || isfive == 0||isfive>5) //控制长度与是否为数字
        {
            SetPos(titleX + 11, titleY + 6);
            int i;
            for (i = 0; i < isfive; i++)printf("  ");
            SetPos(titleX + 11, titleY + 6);
            printf("非法输入:请重新输入不大于五位数     ");
            Sleep(1000);
            SetPos(titleX + 0, titleY + 6);
            printf("售货单价：      .  元                                 ");
        }
        else { break; }
    }

    SetPos(titleX + 17, titleY + 6);//输入价格 double（小数点后）
    while (1)
    {
        SetPos(titleX + 17, titleY + 6);
        float s = 0;
        isfive = isnum = 0;
        while ((c = getchar()) != '\n')
        {
            if (c >= '0' && c <= '9') //小数点后数字处理方法
            {
                float  i = 0;
                for (i = 0; i < isfive + 1; i++)s = s + (c - '0') / pow(10, isfive + 1);

            }
            else { isnum = 1; }
            isfive++;
        }
        if (isfive != 2 || isnum != 0 || isfive == 0) //控制长度与是否为数字
        {
            SetPos(titleX + 17, titleY + 6);
            int i;
            for (i = 0; i < isfive; i++)printf("  ");
            SetPos(titleX + 17, titleY + 6);
            printf("非法输入:请输入小数点后两位        ");
            Sleep(1000);
            SetPos(titleX + 17, titleY + 6);
            printf("  元                                                        ");
        }
        else {
            pri = pri + s;
            break;
        }
    }

    SetPos(titleX + 11, titleY + 7);//输入种类 char
    while (1) {
        SetPos(titleX + 11, titleY + 7);
        memset(temp, 0, sizeof(temp));
        s_get(temp,50);
        if (strlen(temp) >= name_size || strlen(temp) < 1) {
            SetPos(titleX + 11, titleY + 7);
            int i;
            for (i = 0; i < strlen(temp); i++)
                printf("   ");
            SetPos(titleX + 11, titleY + 7);
            printf("非法输入:请重新输入    ");
            Sleep(1000);
            SetPos(titleX + 11, titleY + 7);
            printf("                                ");
        }
        else {
            strcpy(kin, temp);
            break;
        }
    }

    SetPos(titleX + 11, titleY + 8);//输入最大库存 int
    while (1)
    {
        SetPos(titleX + 11, titleY + 8);
        Max = isfive = isnum = 0;
        while ((c = getchar()) != '\n')
        {
            if (c >= '0' && c <= '9')
            {
                Max = Max * 10 + c - '0';
            }
            else { isnum = 1; }
            isfive++;
        }
        if (isnum != 0 || isfive == 0) //控制长度与是否为数字
        {
            SetPos(titleX + 11, titleY + 8);
            int i;
            for (i = 0; i < isfive; i++)printf(" ");
            SetPos(titleX + 11, titleY + 8);
            printf("非法输入:请重新输入");
            Sleep(1000);
            SetPos(titleX + 0, titleY + 8);
            printf("库存上限：                              ");
        }
        else { break; }
    }

    SetPos(titleX, titleY + 9);
    printf("输入无误？Y/N");
    char t;//输入Y或N
    SetPos(titleX + 15, titleY + 9);
    while (1) {
        SetPos(titleX + 15, titleY + 9);
        isfive = isnum = 0;

        while ((t = getchar()) != '\n') {
            c = t;
        }
        if (c != 'N' && c != 'Y' && c != 'n' && c != 'y')//控制长度与是否为数字
        {
            SetPos(titleX + 15, titleY + 9);
            printf("非法输入:请重新输入                                 ");
            Sleep(1000);
            SetPos(titleX + 15, titleY + 9);
            printf("                                                                   ");
        }
        else { break; }
    }
    if (c == 'N' || c == 'n')
    {
        SetPos(titleX + 0, titleY + 10);
        printf("已取消新增商品操作。");
        Sleep(2000);
        return 0;
    }

    position = (Goods*)malloc(sizeof(Goods));
    Goods* Cur = G_Head;
    while (Cur->next)
    {
        Cur = Cur->next;
    }
    strcpy(position->name, nam);
    position->goods_id = id;
    strcpy(position->Manufacturer, manufacturer);
    position->Q_G_period = tim;                              //赋值
    strcpy(position->unit, uni);
    position->S_price = pri;
    position->MaximumNum = Max;
    strcpy(position->kind, kin);
    position->sales_volume = 0;
    position->avg_time = 0;
    position->discount = 10;
    position->total_num = 0;
    Cur->next = position;
    position->next = NULL;
    WriteGoods(G_Head);
    SetPos(titleX + 0 ,titleY + 10);
    printf("商品新建成功。");
    SetPos(titleX + 0 ,titleY + 11);
    system("pause");
    return 0;
}

void Inputmenu()
{
    SetPos(titleX, titleY);
    printf("入 库 功 能");
    SetPos(menuX, menuY);
    printf("1 入库");
    SetPos(menuX, menuY + 1);
    printf("2 新建商品信息");
    SetPos(menuX, menuY + 2);
    printf("0 返回主菜单");
    SetPos(menuX, menuY + 3);
    printf("请输入您的选择：");
}

int New_shipment(Admin* administer, Goods* G_Head, in_Goods* inGoods_Head)
{
    int id = 0, isnum = 2, isfive = 0;
    char c;

    system("cls");
    SetPos(titleX + 0, titleY + 1);
    printf("请输入入库商品的货号：");

    SetPos(titleX + 25, titleY + 1);              //入库货号
    while (1)
    {
        SetPos(titleX + 25, titleY + 1);
        isfive = isnum = 0;
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
            SetPos(titleX + 25, titleY + 1);
            int i;
            for (i = 0; i < isfive; i++)printf("  ");
            SetPos(titleX + 25, titleY + 1);
            printf("非法输入:请重新输入");
            Sleep(1000);
            SetPos(titleX + 25, titleY + 1);
            printf("                                   ");
        }
        else { break; }
    }

    Goods* position = FindByID_2(id, G_Head);
    if (position == NULL)
    {
        system("cls");
        SetPos(titleX,titleY);
        printf("未存在该商品，请前去建立商品信息。");
        SetPos(titleX,titleY+1);
        system("pause");
        return 0;
    }
    else
    {
        SetPos(titleX + 0, titleY + 2);
        printf("正在进行商品 %s 的入库", position->name);
        Sleep(2000);
    }

    system("cls");
    SetPos(titleX + 0, titleY + 0);
    printf("请输入该批次：");
    SetPos(titleX + 0, titleY + 1);
    printf("进货单价：      .  元");
    SetPos(titleX + 0, titleY + 2);
    printf("进货数量：");
    SetPos(titleX + 0, titleY + 3);
    printf("生产日期：      年    月    日");
    int price = 0, num = 0;
    Date productime;
    productime.year = productime.month = productime.day = 0;

    SetPos(titleX + 11, titleY + 1);//输入该批次价格 double（小数点前）
    while (1)
    {
        SetPos(titleX + 11, titleY + 1);
        price = isfive = isnum = 0;
        while ((c = getchar()) != '\n')
        {
            if (c >= '0' && c <= '9') { price = price * 10 + c - '0'; }
            else { isnum = 1; }
            isfive++;
        }
        if (isnum != 0 || isfive == 0||isfive>5) //控制长度与是否为数字
        {
            SetPos(titleX + 11, titleY + 1);
            int i;
            for (i = 0; i < isfive; i++)printf("  ");
            SetPos(titleX + 11, titleY + 1);
            printf("非法输入:请重新输入不大于五位数");
            Sleep(1000);
            SetPos(titleX + 0, titleY + 1);
            printf("进货单价：      .  元                                    ");
        }
        else { break; }
    }

    SetPos(titleX + 17, titleY + 1);//输入价格 double（小数点后）
    while (1)
    {
        SetPos(titleX + 17, titleY + 1);
        float s = 0;
        isfive = isnum = 0;
        while ((c = getchar()) != '\n')
        {
            if (c >= '0' && c <= '9') //小数点后数字处理方法
            {
                float  i = 0;
                for (i = 0; i < isfive + 1; i++)s = s + (c - '0') / pow(10, isfive + 1);

            }
            else { isnum = 1; }
            isfive++;
        }
        if (isfive != 2 || isnum != 0 || isfive == 0) //控制长度与是否为数字
        {
            SetPos(titleX + 17, titleY + 1);
            int i;
            for (i = 0; i < isfive; i++)printf("  ");
            SetPos(titleX + 17, titleY + 1);
            printf("非法输入:请输入小数点后两位");
            Sleep(1000);
            SetPos(titleX + 17, titleY + 1);
            printf("  元                                                  ");
        }
        else {
            price = price + s;
            break;
        }
    }

    SetPos(titleX + 11, titleY + 2);   //该批次数量
    while (1)
    {
        SetPos(titleX + 11, titleY + 2);
        num = isfive = isnum = 0;
        while ((c = getchar()) != '\n')
        {
            if (c >= '0' && c <= '9')
            {
                num = num * 10 + c - '0';
            }
            else { isnum = 1; }
            isfive++;
        }
        if (isfive > 5 || isnum != 0 || isfive == 0||num==0) //控制长度与是否为数字
        {
            SetPos(titleX + 11, titleY + 2);
            int i;
            for (i = 0; i < isfive; i++)printf(" ");
            SetPos(titleX + 11, titleY + 2);
            printf("非法输入:请重新输入");
            Sleep(1000);
            SetPos(titleX + 11, titleY + 2);
            printf("                                 ");
        }
        else { break; }
    }

    SetPos(titleX + 12, titleY + 3);      //生产日期
    while (1)
    {
        SetPos(titleX + 12, titleY + 3);
        productime.year = isfive = isnum = 0;
        while ((c = getchar()) != '\n')
        {
            if (c >= '0' && c <= '9') { productime.year = productime.year * 10 + c - '0'; }
            else { isnum = 1; }
            isfive++;
        }
        if (isfive != 4 || isnum != 0 || isfive == 0) //控制长度与是否为数字
        {
            SetPos(titleX + 12, titleY + 3);
            int i;
            for (i = 0; i < isfive; i++)printf("  ");
            SetPos(titleX + 12, titleY + 3);
            printf("非法输入:请重新输入");
            Sleep(1000);
            SetPos(titleX + 0, titleY + 3);
            printf("生产日期：      年    月    日                 ");
        }
        else { break; }
    }

    SetPos(titleX + 20, titleY + 3);      //月
    while (1)
    {
        SetPos(titleX + 20, titleY + 3);
        productime.month = isfive = isnum = 0;
        while ((c = getchar()) != '\n')
        {
            if (c >= '0' && c <= '9') { productime.month = productime.month * 10 + c - '0'; }
            else { isnum = 1; }
            isfive++;
        }
        if (isfive > 2 || isnum != 0 || isfive == 0) //控制长度与是否为数字
        {
            SetPos(titleX + 20, titleY + 3);
            int i;
            for (i = 0; i < isfive; i++)printf(" ");
            SetPos(titleX + 20, titleY + 3);
            printf("非法输入:请重新输入");
            Sleep(1000);
            SetPos(titleX + 18, titleY + 3);
            printf("    月    日               ");
        }
        else { break; }
    }

    SetPos(titleX + 26, titleY + 3);       //日
    while (1)
    {
        SetPos(titleX + 26, titleY + 3);
        productime.day = isfive = isnum = 0;
        while ((c = getchar()) != '\n')
        {
            if (c >= '0' && c <= '9') { productime.day = productime.day * 10 + c - '0'; }
            else { isnum = 1; }
            isfive++;
        }
        if (isfive > 2 || isnum != 0 || isfive == 0) //控制长度与是否为数字
        {
            SetPos(titleX + 26, titleY + 3);
            int i;
            for (i = 0; i < isfive; i++)printf("  ");
            SetPos(titleX + 26, titleY + 3);
            printf("非法输入:请重新输入");
            Sleep(1000);
            SetPos(titleX + 24, titleY + 3);
            printf("    日                     ");
        }
        else { break; }
    }

    SetPos(titleX, titleY + 4);
    printf("正在进行 %s %05d 的入库操作，输入无误？Y/N",position->name,position->goods_id);
    char t;//输入Y或N
    SetPos(titleX+0, titleY + 5);
    while (1) {
        SetPos(titleX + 0, titleY + 5);
        isfive = isnum = 0;

        while ((t = getchar()) != '\n') {
            c = t;
        }
        if (c != 'N' && c != 'Y'&&c!='n'&&c!='y')//控制长度与是否为数字
        {
            SetPos(titleX + 50, titleY + 5);
            printf("非法输入:请重新输入");
            Sleep(1000);
            SetPos(titleX + 0, titleY + 5);
            printf("                              ");
        }
        else { break; }
    }
    if (c == 'N'||c=='n')
    {
        SetPos(titleX + 0, titleY + 6);
        printf("已取消入库操作。");
        Sleep(2000);
        return 0;
    }

    in_Goods* cur = inGoods_Head;
    in_Goods* New = NULL;
    while (cur->next != NULL) {
        cur = cur->next;
    }
    New = (in_Goods*)malloc(sizeof(in_Goods));
    New->goods_id = position->goods_id;
    strcpy(New->name, position->name);
    New->P_num = New->P_In_num = num;
    position->total_num += num;
    strcpy(New->unit, position->unit);
    New->P_price = price;
    New->P_date = productime;
    New->In_date = GetTodayDate();
    strcpy(New->kind, position->kind);
    strcpy(New->admin, administer->name);
    cur->next = New;
    New->next = NULL;
    WriteGoods(G_Head);
    WriteInGoods(inGoods_Head);
    //}
    int b[2] = { 0, 0 };
    Search_This(inGoods_Head, id, b);
    SetPos(titleX + 0, titleY + 5);
    printf("当前商品 %s %05d 在仓库中共计存在 %d 件，%d 批次。", position->name, id, b[0], b[1]);
    SetPos(titleX + 0, titleY + 6);
    system("pause");
    if (b[0] >= 0.9 * position->MaximumNum) {
        SetPos(titleX + 0, titleY + 7);
        printf("该商品当前数量接近最大库存，请注意。");
        SetPos(titleX + 0, titleY + 8);
        system("pause");
    }
    return 0;
}

void InputMain(Admin* administer, Goods* G_Head, in_Goods* inGoods_Head)
{
    int choice = 1;
    while (choice) {
        system("cls");
        choice = 0;
        Inputmenu();
        choice = GetChoice();
        switch (choice) {
        case 1:
            New_shipment( administer, G_Head,  inGoods_Head);
            break;
        case 2:
            New_kind_of_good( G_Head);
            break;
        case 0:
            break;
        }
    }
}