//
// Created by SGNY on 2020/5/8.
//
//包含结构体和共用的函数
#ifndef SUPER_V1_STRUCTANDFX_H
#define SUPER_V1_STRUCTANDFX_H

#define    name_size  20
#define    titleX     80       //菜单标题位置
#define    titleY     15        //菜单标题位置
#define    menuX      80       //菜单选项位置
#define    menuY      17        //菜单选项位置

#include <stdlib.h>
#include <windows.h>
#include <string.h>

//日期结构体
typedef struct date {
    int year, month, day;
} Date;
//入库所用货物结构体
typedef struct in_goods {
    int    goods_id;                      //货号
    char   name[name_size];               //货物名称
    int    P_num;                         //数量（会变）
    int    P_In_num;                      //入库数量（不变）
    char   unit[name_size];               //计量单位
    double P_price;                       //进货单价
    Date   P_date;                        //生产日期
    Date   In_date;                       //入库日期
    char   kind[name_size];               //种类
    char   admin[name_size];              //经手人
    struct in_goods *next;
} in_Goods;
//汇总货物结构体
typedef struct goods {
    int    goods_id;                      //货号
    char   name[name_size];               //商品名称
    double S_price;                       //售货单价
    char   kind[name_size];               //种类
    int    total_num;                     //该货物总数
    Date   Q_G_period;                    //保质期
    int    sales_volume;                  //销量
    char   unit[name_size];               //计量单位
    char   Manufacturer[name_size];       //生产厂家
    double avg_time;                      //平均在库时间
    double discount;                      //折扣
    int    MaximumNum;                     //最大库存数量
    struct goods *next;
} Goods;
//出库所用结构体
typedef struct out_goods {
    int    goods_id;                       //货号
    char   name[name_size];                //货物名称
    int    Out_num;                        //出库数量
    double S_price;                        //出货单价
    double discount;                       //折扣
    char   remark[name_size];              //备注
    Date   P_date;                         //生产日期
    Date   Out_date;                       //出库日期
    char   admin[name_size];               //经手人
    struct out_goods *next;
} out_Goods;
//管理员
typedef struct admin {
    char admin_id[name_size];              //工号
    char name[name_size];                  //姓名
    char pwd[name_size];              //密码
    char phone[name_size];                 //手机号
    char qu[name_size];              //密保问题
    char ans[name_size];                //答案
    struct admin *next;
} Admin;

//会员
typedef struct vip {
    char name[name_size];                  //姓名
    char phone[11];                        //手机号
    Date RegTime;                          //注册时间
    struct vip *next;
} VIP;

//主菜单
void MainMenu();
//设置光标位置
void SetPos(int x, int y);
//读取字符串
char* s_get(char* st, int n);
//选择菜单获取用户选择函数
int GetChoice();

//获取当前时间
Date GetTodayDate();

//在汇总中通过姓名查询
Goods* FindByName_2(char *name, Goods *G_Head);
//在汇总中通过id查询
Goods* FindByID_2(int id, Goods *G_Head);

//计算相对时间
int GetRelativeTime(Date day);

//读文件和写文件
//管理员链表
Admin* ReadAdmin();
void WriteAdmin(Admin *A_Head);
//入库链表
in_Goods* ReadInGoods();
void WriteInGoods(in_Goods *inGoods_Head);
//出库链表
out_Goods* ReadOutGoods();
void WriteOutGoods(out_Goods *outGoods_Head);
//汇总链表
Goods* ReadGoods();
void WriteGoods(Goods *G_Head);
//VIP
VIP* ReadVIP();
void WriteVIP(VIP *V_Head);



void FreeInGoodsNode(in_Goods *IG_Head);
void FreeOutGoodsNode(out_Goods *OG_Head);
void FreeGoodsNode(Goods *G_Head);

#endif //SUPER_V1_STRUCTANDFX_H