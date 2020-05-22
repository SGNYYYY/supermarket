//
// Created by SGNY on 2020/5/9.
//
//会员管理


#ifndef SUPER_V1_VIP_H
#define SUPER_V1_VIP_H

#include "structandfx.h"
#include "BackupRestore.h"
void VIPMain(Admin *A_Head, in_Goods *inGoods_Head, out_Goods *outGoods_Head,
             Goods *G_Head, VIP *V_Head);
//会员菜单
void VIPMenu();
//查看会员
void SeeAll(VIP *V_Head);
//注册会员
void RegisterVIP(VIP *V_Head);
//查询会员
VIP* FindVIP(VIP *V_Head);
//数据备份与恢复
void BandR(Admin *A_Head, in_Goods *inGoods_Head, out_Goods *outGoods_Head,
           Goods *G_Head, VIP *V_Head);

//修改会员信息
void ChangeVIPInfo(VIP *V_Head);
//删除链表
void FreeVIPNode(VIP *V_Head);

//检测会员是否过期,过期自动删除
void DeleteIfOutDate(VIP *V_Head);
#endif //SUPER_V1_VIP_H
