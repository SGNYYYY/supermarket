//
// Created by SGNY on 2020/5/9.
//
//库存盘点
#ifndef SUPER_V1_STOCKTAKING_H
#define SUPER_V1_STOCKTAKING_H

#include "structandfx.h"
void StockTakingMain(Goods *G_Head, in_Goods *IG_Head);            //库存盘点主函数
void STMenu();                                  //库存盘点菜单
int GetNumOfGoods(Goods *G_Head);               //获取库存中商品数量
Goods* BuildArray(int Num, Goods *G_Head);      //建立动态商品数组
void STBySalesVol(Goods *room, int l, int r);   //按销量排序
void STByInNum(Goods *room, int l, int r);      //按库存数量排序
void STById(Goods *room, int l, int r);         //按货号排序
void STByName(Goods *room, int l, int r);       //按名称排序
void STByAvgTime(Goods *room, int l, int r);    //按平均在库时间排序
void STBYKind(Goods *room, int l, int r);       //按种类排序
void mySwap(Goods* g1, Goods* g2);              //交换函数
void GetAvgTime(Goods *room, in_Goods *IG_Head, int Num);//计算某种商品的平均在库时间
void Order(int Num, Goods *room);    //选择升序降序
#endif //SUPER_V1_STOCKTAKING_H
