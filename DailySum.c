//
// Created by SGNY on 2020/5/9.
//
//每日盘点
#include "DailySum.h"
#include <stdio.h>

void DailySumMain(in_Goods *IG_Head, out_Goods *OG_Head, VIP *V_Head){
    Date Today = GetTodayDate();
    VIP *TodayV = GetTodayVIP(Today, V_Head);
    in_Goods *TodayIG = GetTodayIG(Today, IG_Head);
    out_Goods *TodayOG = GetTodayOG(Today, OG_Head);
    int choice = 0;
    while(1){
        SUM = 0;
        EARN = 0;
        expense = 0;
        choice = 0;
        DailySumMenu();
        choice = GetChoice();
        switch (choice){
            case 1:
                totalSum(TodayIG, TodayOG, TodayV);
                break;
            case 2:
                InSum(TodayIG);
                break;
            case 3:
                OutSum(TodayOG);
                break;
            default:
                break;
        }
        if(choice == 0)
            break;
    }
}
//日盘点主菜单
void DailySumMenu(){
    system("cls");
    SetPos(titleX,titleY);
    printf("库 存 盘 点");
    SetPos(menuX,menuY);
    printf("1 当日总盘点");
    SetPos(menuX,menuY+1);
    printf("2 当日入库盘点");
    SetPos(menuX,menuY+2);
    printf("3 当日出库盘点");
    SetPos(menuX,menuY+3);
    printf("0 返回上一级");
    SetPos(menuX,menuY+4);
    printf("请输入您的选择:\t");
}
//当日总盘点
void totalSum(in_Goods *TodayIG, out_Goods *TodayOG, VIP *TodayV){
    system("cls");
    printf("货号\t商品名称\t数量\t单价\t操作日期\t经手人\t备注\t合计\n");
    in_Goods *cur1 = TodayIG;
    int num = 0;
    while(cur1 != NULL){
        printf("%05d\t%-16s%-8d%-8.2f%d/%d/%-9d%-8s入库%11.2f元\n",
               cur1->goods_id,cur1->name,cur1->P_In_num,cur1->P_price,
               cur1->In_date.year,cur1->In_date.month,cur1->In_date.day,
               cur1->admin,-1*cur1->P_In_num*cur1->P_price);

        SUM -= cur1->P_In_num*cur1->P_price;
        cur1 = cur1->next;
        num++;
    }
    out_Goods *cur = TodayOG;
    while(cur != NULL){
        printf("%05d\t%-16s%-8d%-8.2f%d/%d/%-9d%-8s出库%11.2f元\n",
               cur->goods_id,cur->name,cur->Out_num,cur->S_price,
               cur->Out_date.year,cur->Out_date.month,cur->Out_date.day,
               cur->admin,cur->Out_num*cur->S_price*cur->discount*0.1);

        SUM += cur->Out_num*cur->S_price*cur->discount*0.1;
        cur = cur->next;
        num++;
    }
    VIP *cur3 = TodayV;
    while(cur3 != NULL){
        printf("\t\t\t\t\t\t\t\t办会员\t88.00元\n");
        cur3 = cur3->next;
        SUM += 88;
        num++;
    }
    printf("合计: 今天到目前流水为:\t%.2f元\n",SUM);
    printf("共有 %d 条数据\n",num);
    system("pause");
}
//当日入库盘点
void InSum(in_Goods *TodayIG){
    system("cls");
    printf("货号\t商品名称\t入库数量\t计量单位\t进货单价\t生产日期\t入库日期\t种类\t经手人\t合计\n");
    in_Goods *cur = TodayIG;
    int num = 0;
    while(cur != NULL){
        printf("%05d\t%-16s%-16d%-16s%-16.2f%d/%d/%-9d%d/%d/%-8d%-9s%-8s-%.2f元\n",
                cur->goods_id,cur->name,cur->P_In_num,cur->unit,cur->P_price,
                cur->P_date.year,cur->P_date.month,cur->P_date.day,
                cur->In_date.year,cur->In_date.month,cur->In_date.day,
                cur->kind,cur->admin,cur->P_In_num*cur->P_price);
        expense += cur->P_In_num*cur->P_price;
        cur = cur->next;
        num++;
    }
    printf("合计: 今天到目前支出:\t%.2f元\n",expense);
    printf("共有 %d 条数据\n",num);
    system("pause");
}
//当日出库盘点
void OutSum(out_Goods *TodayOG){
    system("cls");
    printf("货号\t商品名称\t出库数量\t出货单价\t出库日期\t折扣\t经手人\t备注\t合计\n");
    out_Goods *cur = TodayOG;
    int num = 0;
    while(cur != NULL){
        printf("%05d\t%-16s%-16d%-16.2f%d/%d/%-9d%-8.1f%-8s%-8s%.2f元\n",
               cur->goods_id,cur->name,cur->Out_num,cur->S_price,
               cur->Out_date.year,cur->Out_date.month,cur->Out_date.day,
               cur->discount,cur->admin,cur->remark,cur->Out_num*cur->S_price*cur->discount*0.1);

        EARN += cur->Out_num*cur->S_price*cur->discount*0.1;
        cur = cur->next;
        num++;
    }
    printf("合计: 今天到目前出库收入:\t%.2f元\n",EARN);
    printf("共有 %d 条数据\n",num);
    system("pause");
}
//获取当日注册会员
VIP* GetTodayVIP(Date today, VIP* V_Head){
    VIP *cur = V_Head->next;
    while(cur != NULL){
        if(today.year == cur->RegTime.year&&today.month == cur->RegTime.month&&today.day == cur->RegTime.day)
            return cur;
        cur = cur->next;
    }
    return cur;
}
//获取当日入库
in_Goods* GetTodayIG(Date today, in_Goods *IG_Head){
    in_Goods *cur = IG_Head->next;
    while(cur != NULL){
        if(today.year == cur->In_date.year&&today.month == cur->In_date.month&&today.day == cur->In_date.day)
            return cur;
        cur = cur->next;
    }
    return cur;
}
//获取当日出库
out_Goods* GetTodayOG(Date today, out_Goods *OG_Head){
    out_Goods *cur = OG_Head->next;
    while(cur != NULL){
        if(today.year == cur->Out_date.year&&today.month == cur->Out_date.month&&today.day == cur->Out_date.day)
            return cur;
        cur = cur->next;
    }
    return cur;
}