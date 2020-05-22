//
// Created by SGNY on 2020/5/20.
//
//数据备份与恢复
#ifndef SUPER_V1_BACKUPRESTORE_H
#define SUPER_V1_BACKUPRESTORE_H

#include "structandfx.h"

//数据备份
void Backup(Admin *A_Head, in_Goods *inGoods_Head, out_Goods *outGoods_Head,
        Goods *G_Head, VIP *V_Head);
//数据恢复
void Restore(Admin *A_Head, in_Goods *inGoods_Head, out_Goods *outGoods_Head,
             Goods *G_Head, VIP *V_Head);
Admin* RestoreAdmin();
void BackupAdmin(Admin *A_Head);
//入库链表
in_Goods* RestoreInGoods();
void BackupInGoods(in_Goods *inGoods_Head);
//出库链表
out_Goods* RestoreOutGoods();
void BackupOutGoods(out_Goods *outGoods_Head);
//汇总链表
Goods* RestoreGoods();
void BackupGoods(Goods *G_Head);
//VIP
VIP* RestoreVIP();
void BackupVIP(VIP *V_Head);


#endif //SUPER_V1_BACKUPRESTORE_H
