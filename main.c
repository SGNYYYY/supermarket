#include <stdio.h>
#include "structandfx.h"
#include "admin.h"
#include "input.h"
#include "output.h"
#include "setdiscount.h"
#include "FindGoods.h"
#include "ChangeGoodsInfo.h"
#include "SoldOut.h"
#include "VIP.h"
#include "BackupRestore.h"

#include "StockTaking.h"
#include "DailySum.h"
in_Goods *inGoods_Head;
Goods *G_Head;
out_Goods *outGoods_Head;
Admin *A_Head;
VIP *V_Head;

int main() {
    A_Head = ReadAdmin();
    Admin *administer = AdminMain(A_Head);
    if (administer != NULL) {
        inGoods_Head = ReadInGoods();
        outGoods_Head = ReadOutGoods();
        G_Head = ReadGoods();
        V_Head = ReadVIP();
        DeleteIfOutDate(V_Head);
        Backup(A_Head,inGoods_Head,outGoods_Head,G_Head,V_Head);
        int choice = 0;
        while (1) {
            system("cls");
            choice = 0;
            MainMenu();
            choice = GetChoice();
            switch (choice) {
                case 1:
                    InputMain(administer, G_Head, inGoods_Head);
                    break;
                case 2:
                    OutPutMain(outGoods_Head, inGoods_Head, G_Head, administer, V_Head);
                    break;
                case 3:
                    FindMain(G_Head, inGoods_Head);
                    break;
                case 4:
                    ChangeMain(G_Head);
                    break;
                case 5:
                    SetDiscountMain(G_Head);
                    break;
                case 6:
                    DeleteMain(G_Head);
                    break;
                case 7:
                    StockTakingMain(G_Head, inGoods_Head);
                    break;
                case 8:
                    DailySumMain(inGoods_Head, outGoods_Head, V_Head);
                    break;
                case 9:
                    VIPMain(A_Head,inGoods_Head,outGoods_Head,G_Head,V_Head);
                    break;
                default:
                    break;
            }
            Backup(A_Head,inGoods_Head,outGoods_Head,G_Head,V_Head);
            if (choice == 0)
                break;
        }

        WriteVIP(V_Head);
        FreeVIPNode(V_Head);
        WriteInGoods(inGoods_Head);
        WriteOutGoods(outGoods_Head);
        WriteGoods(G_Head);
        FreeAdminNode(A_Head);
        FreeInGoodsNode(inGoods_Head);
        FreeOutGoodsNode(outGoods_Head);
        FreeGoodsNode(G_Head);
    }
    return 0;
}

void MainMenu(){
    system("cls");
    SetPos(titleX-13,titleY-2);
    printf("*******超市商品库存信息管理系统*******");
    int i = 0;
    for(i = 1;i <= 16;i++){
        SetPos(titleX-13,titleY-2+i);
        printf("*");
        SetPos(titleX+24,titleY-2+i);
        printf("*");
    }
    for(i = 1;i <= 36;i++){
        SetPos(titleX-13+i,titleY-2+16);
        printf("*");
    }
    SetPos(titleX, titleY);
    printf(" 主 菜 单");
    SetPos(menuX, menuY);
    printf("1 商品入库");
    SetPos(menuX, menuY + 1);
    printf("2 商品出库");
    SetPos(menuX, menuY + 2);
    printf("3 商品查询");
    SetPos(menuX, menuY + 3);
    printf("4 修改商品信息");
    SetPos(menuX, menuY + 4);
    printf("5 设置折扣");
    SetPos(menuX, menuY + 5);
    printf("6 下架商品");
    SetPos(menuX, menuY + 6);
    printf("7 库存盘点");
    SetPos(menuX, menuY + 7);
    printf("8 每日盘点");
    SetPos(menuX, menuY + 8);
    printf("9 管理员管理");
    SetPos(menuX, menuY + 9);
    printf("0 退出系统");
    SetPos(menuX, menuY + 10);
    printf("请输入您的选择:\t");
}