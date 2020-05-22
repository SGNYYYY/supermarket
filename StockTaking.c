//
// Created by SGNY on 2020/5/9.
//
#include "StockTaking.h"
#include <stdio.h>
//库存盘点
//库存盘点主函数
void StockTakingMain(Goods *G_Head, in_Goods *IG_Head) {
    int Num = GetNumOfGoods(G_Head);      //获取汇总商品种数
    Goods *GoodsArray = NULL;
    if (Num != 0) {          //如果有此商品
        GoodsArray = BuildArray(Num, G_Head); //建立动态数组
        GetAvgTime(GoodsArray, IG_Head, Num); //获取每种商品在库平均时间
        int choice;
        while (1) {
            choice = 0;
            STMenu();
            choice = GetChoice();
            switch (choice) {
                case 1:
                    STBySalesVol(GoodsArray, 0, Num-1);
                    Order(Num, GoodsArray);
                    break;
                case 2:
                    STByInNum(GoodsArray, 0, Num-1);
                    Order(Num, GoodsArray);
                    break;
                case 3:
                    STById(GoodsArray, 0, Num-1);
                    Order(Num, GoodsArray);
                    break;
                case 4:
                    STByName(GoodsArray, 0, Num-1);
                    Order(Num, GoodsArray);
                    break;
                case 5:
                    STByAvgTime(GoodsArray, 0, Num-1);
                    Order(Num, GoodsArray);
                    break;
                case 6:
                    STBYKind(GoodsArray, 0, Num-1);
                    Order(Num, GoodsArray);
                    break;
                default:
                    break;
            }
            if (choice == 0) {
                free(GoodsArray);
                break;
            }
        }
    } else {
        system("cls");
        SetPos(titleX, titleY);
        printf("库存是空的\n");
        system("pause");
    }
}

//库存盘点菜单
void STMenu() {
    system("cls");
    SetPos(titleX, titleY);
    printf("库 存 盘 点");
    SetPos(menuX, menuY);
    printf("1 按销量盘点");
    SetPos(menuX, menuY + 1);
    printf("2 按库存数量盘点");
    SetPos(menuX, menuY + 2);
    printf("3 按货号盘点");
    SetPos(menuX, menuY + 3);
    printf("4 按名称盘点");
    SetPos(menuX, menuY + 4);
    printf("5 按平均在库时间盘点");
    SetPos(menuX, menuY + 5);
    printf("6 按种类盘点");
    SetPos(menuX, menuY + 6);
    printf("0 返回主菜单");
    SetPos(menuX, menuY + 7);
    printf("请输入您的选择:\t");
}

//获取库存中商品数量
int GetNumOfGoods(Goods *G_Head) {
    Goods *cur = G_Head->next;
    int num = 0;
    while (cur != NULL) {
        num++;
        cur = cur->next;
    }
    return num;
}

//建立动态商品数组
Goods *BuildArray(int Num, Goods *G_Head) {
    Goods *room = (Goods *) malloc(Num * sizeof(Goods));
    Goods *cur = G_Head->next;
    int i = 0;
    while (cur != NULL) {
        room[i].goods_id = cur->goods_id;
        strcpy(room[i].name, cur->name);
        room[i].S_price = cur->S_price;
        strcpy(room[i].kind, cur->kind);
        room[i].total_num = cur->total_num;
        room[i].Q_G_period = cur->Q_G_period;
        room[i].sales_volume = cur->sales_volume;
        strcpy(room[i].unit, cur->unit);
        strcpy(room[i].Manufacturer, cur->Manufacturer);
        room[i].avg_time = 0;
        room[i].discount = cur->discount;
        cur = cur->next;
        i++;
    }
    return room;
}

//按销量排序
void STBySalesVol(Goods *room, int l, int r) {
    int mid = room[(l + r) / 2].sales_volume;      //取中间一个销量的值
    int i = l, j = r;
    while (i <= j) {
        while (room[i].sales_volume < mid) i++; //如果小于中间值在中间值的左边，位置不变
        while (room[j].sales_volume > mid) j--;//如果大于中间值在中间值的右边，位置不变
        if (i <= j) {
            mySwap(&room[i], &room[j]);
            i++;
            j--;
        }
    }
    if (l < j) STBySalesVol(room, l, j);
    if (i < r) STBySalesVol(room, i, r);
}

//按库存数量排序
void STByInNum(Goods *room, int l, int r) {
    int mid = room[(l + r) / 2].total_num;      //取中间一个库存数量的值
    int i = l, j = r;
    while (i <= j) {
        while (room[i].total_num < mid) i++; //如果小于中间值在中间值的左边，位置不变
        while (room[j].total_num > mid) j--;//如果大于中间值在中间值的右边，位置不变
        if (i <= j) {
            mySwap(&room[i], &room[j]);
            i++;
            j--;
        }
    }
    if (l < j) STByInNum(room, l, j);
    if (i < r) STByInNum(room, i, r);
}

//按货号排序
void STById(Goods *room, int l, int r) {
    int mid = room[(l + r) / 2].goods_id;      //取中间一个货号的值
    int i = l, j = r;
    while (i <= j) {
        while (room[i].goods_id < mid) i++; //如果小于中间值在中间值的左边，位置不变
        while (room[j].goods_id > mid) j--;//如果大于中间值在中间值的右边，位置不变
        if (i <= j) {
            mySwap(&room[i], &room[j]);
            i++;
            j--;
        }
    }
    if (l < j) STById(room, l, j);
    if (i < r) STById(room, i, r);
}

//按名称排序
void STByName(Goods *room, int l, int r) {
    char *mid = (char*)malloc(50*sizeof(char));
    strcpy(mid, room[(l + r) / 2].name);
    int i = l, j = r;
    while (i <= j) {
        while (strcmp(room[i].name, mid) < 0) i++; //如果小于中间值在中间值的左边，位置不变
        while (strcmp(room[j].name, mid) > 0) j--; //如果大于中间值在中间值的右边，位置不变
        if (i <= j) {
            mySwap(&room[i], &room[j]);
            i++;
            j--;
        }
    }
    free(mid);
    if (l < j) STByName(room, l, j);
    if (i < r) STByName(room, i, r);
}

//按平均在库时间排序
void STByAvgTime(Goods *room, int l, int r) {
    double mid = room[(l + r) / 2].avg_time;      //取中间一个货号的值
    int i = l, j = r;
    while (i <= j) {
        while (room[i].avg_time < mid) i++; //如果小于中间值在中间值的左边，位置不变
        while (room[j].avg_time > mid) j--;//如果大于中间值在中间值的右边，位置不变
        if (i <= j) {
            mySwap(&room[i], &room[j]);
            i++;
            j--;
        }
    }
    if (l < j) STByAvgTime(room, l, j);
    if (i < r) STByAvgTime(room, i, r);
}

//按种类排序
void STBYKind(Goods *room, int l, int r) {
    char *mid = (char*)malloc(50*sizeof(char));
    strcpy(mid, room[(l + r) / 2].kind);
    int i = l, j = r;
    while (i <= j) {
        while (strcmp(room[i].kind, mid) < 0) i++; //如果小于中间值在中间值的左边，位置不变
        while (strcmp(room[j].kind, mid) > 0) j--;//如果大于中间值在中间值的右边，位置不变
        if (i <= j) {
            mySwap(&room[i], &room[j]);
            i++;
            j--;
        }
    }
    free(mid);
    if (l < j) STByName(room, l, j);
    if (i < r) STByName(room, i, r);
}

//交换函数
void mySwap(Goods *g1, Goods *g2) {
    Goods temp;
    temp.goods_id = g1->goods_id;
    strcpy(temp.name, g1->name);
    temp.S_price = g1->S_price;
    strcpy(temp.kind, g1->kind);
    temp.total_num = g1->total_num;
    temp.Q_G_period = g1->Q_G_period;
    temp.sales_volume = g1->sales_volume;
    strcpy(temp.unit, g1->unit);
    strcpy(temp.Manufacturer, g1->Manufacturer);
    temp.avg_time = g1->avg_time;
    temp.discount = g1->discount;
    g1->goods_id = g2->goods_id;
    strcpy(g1->name, g2->name);
    g1->S_price = g2->S_price;
    strcpy(g1->kind, g2->kind);
    g1->total_num = g2->total_num;
    g1->Q_G_period = g2->Q_G_period;
    g1->sales_volume = g2->sales_volume;
    strcpy(g1->unit, g2->unit);
    strcpy(g1->Manufacturer, g2->Manufacturer);
    g1->avg_time = g2->avg_time;
    g1->discount = g2->discount;
    g2->goods_id = temp.goods_id;
    strcpy(g2->name, temp.name);
    g2->S_price = temp.S_price;
    strcpy(g2->kind, temp.kind);
    g2->total_num = temp.total_num;
    g2->Q_G_period = temp.Q_G_period;
    g2->sales_volume = temp.sales_volume;
    strcpy(g2->unit, temp.unit);
    strcpy(g2->Manufacturer, temp.Manufacturer);
    g2->avg_time = temp.avg_time;
    g2->discount = temp.discount;
}

//计算某种商品的平均在库时间
void GetAvgTime(Goods *room, in_Goods *IG_Head, int Num) {
    int i = 0;
    in_Goods *cur = IG_Head->next;
    in_Goods *tp = NULL;
    while (cur != NULL&& cur->P_num == 0 ) {  //找到第一个有数量的批次，都没有返回NULL
        cur = cur->next;
    }
    double sum = 0;
    int day = 0;
    for (i = 0; i < Num; i++) {
        tp = cur;
        sum = 0;
        day = 0;
        while (tp != NULL&& tp!=IG_Head) {
            if (tp->goods_id == room[i].goods_id) {
                day = GetRelativeTime(GetTodayDate()) - GetRelativeTime(tp->In_date);
                sum += day * tp->P_num;
            }
            tp = tp->next;
        }
        if (room[i].total_num != 0)
            room[i].avg_time = (sum*1.0) / room[i].total_num;
        else
            room[i].avg_time = 0;
    }
}

//选择升序降序
void Order(int Num, Goods *room) {
    int choice = 0;
    while (1) {
        system("cls");
        SetPos(titleX, titleY);
        printf("请选择排序方式: 1 升序 2 降序 0 返回上一级");
        SetPos(titleX, titleY + 1);
        printf("请输入您的选择:\t");
        choice = GetChoice();
        switch (choice) {
            case 1: {//从小到大
                system("cls");
                printf("货号\t商品名称\t售货单价\t种类\t该货物总数\t保质期\t\t销量\t计量单位\t生产厂家\t平均在库时间\t折扣\t\n");
                int i = 0;
                for (i = 0; i < Num; i++) {
                    printf("%05d\t%-18s%-14.2f%-12s%-10d%d年%d月%d日  \t%-10d%-14s%-18s%-14.5f%.1f\n",
                           room[i].goods_id, room[i].name, room[i].S_price, room[i].kind, room[i].total_num,
                           room[i].Q_G_period.year,
                           room[i].Q_G_period.month, room[i].Q_G_period.day, room[i].sales_volume, room[i].unit,
                           room[i].Manufacturer,
                           room[i].avg_time, room[i].discount);
                }
                printf("\n共有 %d 条数据\n",i);
                system("pause");
                break;
            }
            case 2: {//从大到小
                system("cls");
                printf("货号\t商品名称\t售货单价\t种类\t该货物总数\t保质期\t\t销量\t计量单位\t生产厂家\t平均在库时间\t折扣\t\n");
                int i = 0;
                int j = 0;
                for (i = Num - 1; i >= 0; i--) {
                    printf("%05d\t%-18s%-14.2f%-12s%-10d%d年%d月%d日  \t%-10d%-14s%-18s%-14.5f%.1f\n",
                           room[i].goods_id, room[i].name, room[i].S_price, room[i].kind, room[i].total_num,
                           room[i].Q_G_period.year,
                           room[i].Q_G_period.month, room[i].Q_G_period.day, room[i].sales_volume, room[i].unit,
                           room[i].Manufacturer,
                           room[i].avg_time, room[i].discount);
                    j++;
                }
                printf("\n共有 %d 条数据\n",j);
                system("pause");
                break;
            }
            default:
                break;
        }
        if (choice == 0)
            break;
    }
}