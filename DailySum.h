//
// Created by SGNY on 2020/5/9.
//
//每日盘点
#ifndef SUPER_V1_DAILYSUM_H
#define SUPER_V1_DAILYSUM_H

#include "structandfx.h"

void DailySumMain(in_Goods *IG_Head, out_Goods *OG_Head, VIP *V_Head);    //日盘点主函数
void DailySumMenu();   //日盘点主菜单
void totalSum(in_Goods *TodayIG, out_Goods *TodayOG, VIP *TodayV);       //当日总盘点
void InSum(in_Goods *TodayIG);         //当日入库盘点
void OutSum(out_Goods *TodayOG);        //当日出库盘点
VIP* GetTodayVIP(Date today, VIP* V_Head);   //获取当日注册会员
in_Goods* GetTodayIG(Date today, in_Goods *IG_Head);  //获取当日入库
out_Goods* GetTodayOG(Date today, out_Goods *OG_Head);//获取当日出库
double SUM;           //当日总流水
double EARN;          //当日收入
double expense;           //当日指出
#endif //SUPER_V1_DAILYSUM_H
