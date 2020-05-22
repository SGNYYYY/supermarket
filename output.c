#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "VIP.h"
#include <string.h>
#include "output.h"

void Search_This_1(in_Goods *inGoods_Head, int a, int b[]) {
    in_Goods *existence;
    existence = inGoods_Head;
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


void OutPutMenu() {
    system("cls");
    SetPos(titleX, titleY);
    printf("考虑到商品拥有保质期，请保证优先出售最早批次。");
    SetPos(menuX, menuY);
    printf("1 正常出售");
    SetPos(menuX, menuY + 1);
    printf("2 退货");
    SetPos(menuX, menuY + 2);
    printf("0 返回主菜单");
    SetPos(menuX, menuY + 3);
    printf("请输入选择：");
}

int Sale(out_Goods *outGoods_Head, in_Goods *inGoods_Head, Goods *G_Head, Admin *administer, VIP *V_Head) {
    system("cls");

    int id = 0, coun = 0, isnum = 2, isfive = 0;
    char c;
    out_Goods *Newout;
    out_Goods *outcur = outGoods_Head;
    in_Goods *in = inGoods_Head;

    SetPos(titleX, titleY);
    printf("请输入商品货号：");
    SetPos(titleX, titleY + 1);
    printf("请输入售出数量：");

    SetPos(titleX + 19, titleY + 0);//输入货号 int
    while (1) {
        SetPos(titleX + 19, titleY + 0);
        id = isfive = isnum = 0;
        while ((c = getchar()) != '\n') {
            if (c >= '0' && c <= '9') {
                id = id * 10 + c - '0';
            } else { isnum = 1; }
            isfive++;
        }
        if (isfive > 5 || isnum != 0 || isfive == 0) //控制长度与是否为数字
        {
            SetPos(titleX + 19, titleY + 0);
            int i;
            for (i = 0; i < isfive; i++)printf(" ");
            SetPos(titleX + 9, titleY + 0);
            printf("非法输入:请重新输入");
            Sleep(1000);
            SetPos(titleX + 0, titleY + 0);
            printf("请输入商品货号：                            ");
        } else { break; }
    }

    SetPos(titleX + 19, titleY + 1);//输入数量 int
    while (1) {
        SetPos(titleX + 19, titleY + 1);
        coun = isfive = isnum = 0;
        while ((c = getchar()) != '\n') {
            if (c >= '0' && c <= '9') {
                coun = coun * 10 + c - '0';
            } else { isnum = 1; }
            isfive++;
        }
        if (isfive > 5 || isnum != 0 || isfive == 0) //控制长度与是否为数字
        {
            SetPos(titleX + 19, titleY + 1);
            int i;
            for (i = 0; i < isfive; i++)printf(" ");
            SetPos(titleX + 19, titleY + 1);
            printf("非法输入:请重新输入");
            Sleep(1000);
            SetPos(titleX + 0, titleY + 1);
            printf("请输入售出数量：                           ");
        } else { break; }
    }

    SetPos(titleX + 0, titleY + 2);//货号出错
    Goods *position = FindByID_2(id, G_Head);
    if (position == NULL) {
        printf("未有该商品");
        SetPos(titleX + 0, titleY + 3);
        system("pause");
        return 0;
    }

    SetPos(titleX + 0, titleY + 2);//数量出错
    if (coun > position->total_num) {
        printf("出货数量大于库存数量，请检查货号或出库数量。");
        SetPos(titleX + 0, titleY + 3);
        system("pause");
        return 0;
    }

    SetPos(titleX + 0, titleY + 2);
    if (position->discount == 10) {
        printf("该商品售价共计%.2lf元", position->S_price*coun);
    } else {
        printf("该商品售价共计%.2lf元，含%.1lf折", position->S_price * position->discount / 10*coun, position->discount);
    }

    SetPos(titleX + 0, titleY + 3);
    printf("是否有会员卡Y/N？");
    SetPos(titleX + 19, titleY + 3);
    char t;//输入Y或N
    while (1) {
        SetPos(titleX + 19, titleY + 3);
        isfive = isnum = 0;

        while ((t = getchar()) != '\n') {
            c = t;
        }
        if (c != 'N' && c != 'Y' && c != 'n' && c != 'y')//控制长度与是否为数字
        {
            SetPos(titleX + 19, titleY + 3);
            printf("非法输入:请重新输入");
            Sleep(1000);
            SetPos(titleX + 19, titleY + 3);
            printf("                              ");
        }
        else { break; }
    }

    if (c == 'N'||c=='n') {
        SetPos(titleX + 0, titleY + 4);
        printf("是否注册会员Y/N？");//是否注册
        while (1) {
            SetPos(titleX + 19, titleY + 4);
            isfive = isnum = 0;
            while ((t = getchar()) != '\n') {
                c = t;
            }
            if (c != 'N' && c != 'Y' && c != 'n' && c != 'y')//控制长度与是否为数字
            {
                SetPos(titleX + 19, titleY + 4);
                printf("非法输入:请重新输入");
                Sleep(1000);
                SetPos(titleX + 19, titleY + 4);
                printf("                              ");
            }
            else { break; }
        }

        //注册会员后购买
        if (c == 'Y'||c=='y') {
            RegisterVIP(V_Head);             //注册会员

            SetPos(titleX, titleY + 3);
            printf("会员九折，实际共计%.2lf元。", position->S_price* position->discount / 10 * 0.9*coun);
            while (outcur->next) {
                outcur = outcur->next;
            }
            Newout = (out_Goods *) malloc(sizeof(out_Goods));
            Newout->goods_id = position->goods_id;
            strcpy(Newout->name, position->name);
            Newout->Out_num = coun;
            Newout->S_price = position->S_price * position->discount / 10*0.9;
            Newout->discount = position->discount;
            strcpy(Newout->remark, "会员");
            Newout->Out_date = GetTodayDate();
            Newout->P_date.year = Newout->P_date.month = Newout->P_date.day = 0;
            strcpy(Newout->admin, administer->name);
            outcur->next = Newout;
            outcur = Newout;
            outcur->next = NULL;
            position->total_num -= coun;

            while (in)   //从库存中减去
            {
                if (in->goods_id == id && in->P_num != 0) {
                    if (in->P_num > coun) {
                        in->P_num -= coun;
                        position->sales_volume += coun;
                        coun = 0;
                    } else {
                        coun -= in->P_num;
                        position->sales_volume += in->P_num;
                        in->P_num = 0;
                    }
                }
                if (coun == 0)break;
                in = in->next;
            }
            WriteGoods(G_Head);
            WriteInGoods(inGoods_Head);
            WriteOutGoods(outGoods_Head);

            SetPos(titleX, titleY + 4);
            system("pause");

        }
            //非会员购买
        else  {
            while (outcur->next) {
                outcur = outcur->next;
            }
            Newout = malloc(sizeof(out_Goods));
            Newout->goods_id = position->goods_id;
            strcpy(Newout->name, position->name);
            Newout->Out_num = coun;
            Newout->S_price = position->S_price * position->discount / 10;
            Newout->discount = position->discount;
            strcpy(Newout->remark, "非会员");
            Newout->Out_date = GetTodayDate();
            Newout->P_date.year = Newout->P_date.month = Newout->P_date.day = 0;
            strcpy(Newout->admin, administer->name);
            outcur->next = Newout;
            outcur = Newout;
            outcur->next = NULL;
            position->total_num -= coun;

            while (in)   //从库存中减去
            {
                if (in->goods_id == id && in->P_num != 0) {
                    if (in->P_num > coun) {
                        in->P_num -= coun;
                        position->sales_volume += coun;
                        coun = 0;
                    } else {
                        coun -= in->P_num;
                        position->sales_volume += in->P_num;
                        in->P_num = 0;
                    }
                }
                if (coun == 0)break;
                in = in->next;
            }
            WriteGoods(G_Head);
            WriteInGoods(inGoods_Head);
            WriteOutGoods(outGoods_Head);
        }
    }

        //已有会员购买
    else  {
        VIP *isvip = FindVIP(V_Head);
        if (isvip == V_Head) {
            SetPos(titleX + 0, titleY + 4);
            printf("取消确认会员操作，请重新进行出库。");
            SetPos(titleX + 0, titleY + 5);
            system("pause");
            return 0;
        }

        SetPos(titleX, titleY + 3);
        printf("会员九折，实际共计%.2lf元。", position->S_price* position->discount / 10 * 0.9*coun);

        while (outcur->next) {
            outcur = outcur->next;
        }
        Newout = malloc(sizeof(out_Goods));
        Newout->goods_id = position->goods_id;
        strcpy(Newout->name, position->name);
        Newout->Out_num = coun;
        Newout->S_price = position->S_price * position->discount / 10*0.9;
        Newout->discount = position->discount;
        strcpy(Newout->remark, "会员");
        Newout->Out_date = GetTodayDate();
        Newout->P_date.year = Newout->P_date.month = Newout->P_date.day = 0;
        strcpy(Newout->admin, administer->name);
        outcur->next = Newout;
        outcur = Newout;
        outcur->next = NULL;
        position->total_num -= coun;

        while (in)   //从库存中减去
        {
            if (in->goods_id == id && in->P_num != 0) {
                if (in->P_num > coun) {
                    in->P_num -= coun;
                    position->sales_volume += coun;
                    coun = 0;
                } else {
                    coun -= in->P_num;
                    position->sales_volume += in->P_num;
                    in->P_num = 0;
                }
            }
            if (coun == 0)break;
            in = in->next;
        }
        WriteGoods(G_Head);
        WriteInGoods(inGoods_Head);
        WriteOutGoods(outGoods_Head);

        SetPos(titleX, titleY + 4);
        system("pause");

    }
    SetPos(titleX + 0, titleY + 6);
    printf("出库成功。");
    Sleep(2000);
    return 0;
}

int Return(out_Goods *outGoods_Head, in_Goods *inGoods_Head, Goods *G_Head, Admin *administer) {
    system("cls");        //退货
    int id = 0, coun = 0, isnum = 2, isfive = 0;
    double pri = 0;
    char c;
    out_Goods *Newout;
    out_Goods *returncur = outGoods_Head;
    in_Goods *in = inGoods_Head;

    SetPos(titleX + 0, titleY + 0);
    printf("请输入货号：");
    SetPos(titleX + 0, titleY + 1);
    printf("退货单价：      .  元");
    SetPos(titleX, titleY + 2);
    printf("请输入数量：");


    SetPos(titleX + 14, titleY + 0);//货号
    while (1) {
        SetPos(titleX + 14, titleY + 0);
        id = isfive = isnum = 0;
        while ((c = getchar()) != '\n') {
            if (c >= '0' && c <= '9') {
                id = id * 10 + c - '0';
            } else { isnum = 1; }
            isfive++;
        }
        if (isfive > 5 || isnum != 0 || isfive == 0) //控制长度与是否为数字
        {
            SetPos(titleX + 14, titleY + 0);
            int i;
            for (i = 0; i < isfive; i++)printf(" ");
            SetPos(titleX + 14, titleY + 0);
            printf("非法输入:请重新输入");
            Sleep(1000);
            SetPos(titleX + 0, titleY + 0);
            printf("请输入货号：                            ");
        } else { break; }
    }

    SetPos(titleX + 11, titleY + 1);//   小数点前
    while (1) {
        SetPos(titleX + 11, titleY + 1);
        pri = isfive = isnum = 0;
        while ((c = getchar()) != '\n') {
            if (c >= '0' && c <= '9') { pri = pri * 10 + c - '0'; }
            else { isnum = 1; }
            isfive++;
        }
        if (isnum != 0 || isfive == 0) //控制长度与是否为数字
        {
            SetPos(titleX + 11, titleY + 1);
            int i;
            for (i = 0; i < isfive; i++)printf(" ");
            SetPos(titleX + 11, titleY + 1);
            printf("非法输入:请重新输入");
            Sleep(1000);
            SetPos(titleX + 0, titleY + 1);
            printf("退货单价：      .  元                 ");
        } else { break; }
    }

    SetPos(titleX + 17, titleY + 1);//    小数点后
    while (1) {
        SetPos(titleX + 17, titleY + 1);
        float s = 0;
        isfive = isnum = 0;
        while ((c = getchar()) != '\n') {
            if (c >= '0' && c <= '9') //小数点后数字处理方法
            {
                float i = 0;
                for (i = 0; i < isfive + 1; i++)s = s + (c - '0') / pow(10, isfive + 1);

            } 
            else { isnum = 1; }
            isfive++;
        }
        if (isfive != 2 || isnum != 0 || isfive == 0) //控制长度与是否为数字
        {
            SetPos(titleX + 17, titleY + 1);
            int i;
            for (i = 0; i < isfive; i++)printf(" ");
            SetPos(titleX + 17, titleY + 1);
            printf("非法输入:请输入小数点后两位");
            Sleep(1000);
            SetPos(titleX + 17, titleY + 1);
            printf("  元                         ");
        } else {
            pri = pri + s;
            break;
        }
    }

    SetPos(titleX + 14, titleY + 2);//   数量 int
    while (1) {
        SetPos(titleX + 14, titleY + 2);
        isfive = isnum = 0;
        while ((c = getchar()) != '\n') {
            if (c >= '0' && c <= '9') {
                coun = coun * 10 + c - '0';
            } else { isnum = 1; }
            isfive++;
        }
        if (isnum != 0 || isfive == 0) //控制长度与是否为数字
        {
            SetPos(titleX + 14, titleY + 2);
            int i;
            for (i = 0; i < isfive; i++)printf(" ");
            SetPos(titleX + 14, titleY + 2);
            printf("非法输入:请重新输入");
            Sleep(1000);
            SetPos(titleX + 0, titleY + 2);
            printf("请输入数量：                            ");
        } else { break; }
    }

    Goods *position;
    position = FindByID_2(id, G_Head);
    SetPos(titleX + 0, titleY + 3);

    if (position == NULL) {
        SetPos(titleX + 0, titleY + 3);
        printf("未有该商品请查证后输入");
        SetPos(titleX + 0, titleY + 4);
        system("pause");
        return 0;
    }

    if (coun > position->total_num) {
        SetPos(titleX + 0, titleY + 3);
        printf("出货数量大于库存数量，请检查货号或出库数量。");
        SetPos(titleX + 0, titleY + 4);
        system("pause");
        return 0;
    }

    while (returncur->next) {
        returncur = returncur->next;
    }
    Newout = malloc(sizeof(out_Goods));
    Newout->goods_id = position->goods_id;
    strcpy(Newout->name, position->name);
    Newout->Out_num = coun;
    Newout->S_price = pri;
    Newout->discount = position->discount;
    strcpy(Newout->remark, "退货");
    Newout->Out_date = GetTodayDate();
    strcpy(Newout->admin, administer->name);
    returncur->next = Newout;
    returncur = Newout;
    returncur->next = NULL;
    position->total_num -= coun;

    while (in)   //从库存中减去
    {
        if (in->goods_id == id && in->P_num != 0) {
            if (in->P_num > coun) {
                in->P_num -= coun;
                coun = 0;
            } else {
                coun -= in->P_num;
                in->P_num = 0;
            }
        }
        if (coun == 0)break;
        in = in->next;
    }
    WriteGoods(G_Head);
    WriteInGoods(inGoods_Head);

    int b[2] = {0, 0};
    Search_This_1(inGoods_Head, id, b);
    SetPos(titleX + 0, titleY + 3);
    printf("当前商品%s%d在仓库中共计存在%d件，%d批次。", position->name, id, b[0], b[1]);
    if (b[0] <= 0.1 * position->MaximumNum) {
        SetPos(titleX + 0, titleY + 4);
        printf("该商品当前数量较少，请注意。");
    }
    SetPos(titleX + 0, titleY + 5);
    system("pause");
    return 0;
}

void OutPutMain(out_Goods *outGoods_Head, in_Goods *inGoods_Head, Goods *G_Head, Admin *administer, VIP *V_Head) {
    int choice = 1;
    while (choice) {
        system("cls");
        choice = 0;
        OutPutMenu();
        choice = GetChoice();
        switch (choice) {
            case 1:
                Sale(outGoods_Head, inGoods_Head, G_Head, administer, V_Head);
                break;
            case 2:
                Return(outGoods_Head, inGoods_Head, G_Head, administer);
                break;
            case 0:
                break;
        }
    }
}
