//
// Created by SGNY on 2020/5/9.
//

#include "VIP.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "admin.h"
#include "BackupRestore.h"
void VIPMain(Admin *A_Head, in_Goods *inGoods_Head, out_Goods *outGoods_Head,
             Goods *G_Head, VIP *V_Head){
    int choice;
    VIP *tp = NULL;
    while(1){
        choice = 0;
        VIPMenu();
        choice = GetChoice();
        switch (choice){
            case 1:
                SeeAll(V_Head); //查看会员
                break;
            case 2:
                RegisterVIP(V_Head);//注册会员
                break;
            case 3:
                tp = FindVIP(V_Head);//查询会员
                SetPos(menuX,menuY);
                if(tp == NULL){
                    SetPos(menuX,menuY+1);
                    printf("查无此会员          ");
                }else if(tp != V_Head){
                    SetPos(menuX,menuY+1);
                    printf("姓名:%s",tp->name);
                    SetPos(menuX,menuY+2);
                    printf("手机号:%s",tp->phone);
                    SetPos(menuX,menuY+3);
                    printf("注册时间(年/月/日):%d/%d/%d",tp->RegTime.year,tp->RegTime.month,tp->RegTime.day);
                }
                SetPos(menuX,menuY+4);
                system("pause");
                break;
            case 4:
                ChangeVIPInfo(V_Head);//修改会员信息
                break;
            case 5:
                Register(A_Head);
                break;
            case 6:
                BandR(A_Head,inGoods_Head,outGoods_Head,G_Head,V_Head);
                break;
            default:
                break;
        }
        if(choice == 0){
            break;
        }
    }
}
//会员菜单
void VIPMenu(){
    system("cls");
    SetPos(titleX,titleY);
    printf(" 管理员管理");
    SetPos(menuX,menuY);
    printf("1 查看会员");
    SetPos(menuX,menuY+1);
    printf("2 注册会员");
    SetPos(menuX,menuY+2);
    printf("3 查询会员");
    SetPos(menuX,menuY+3);
    printf("4 修改会员信息");
    SetPos(menuX,menuY+4);
    printf("5 注册管理员");
    SetPos(menuX,menuY+5);
    printf("6 数据备份与恢复");
    SetPos(menuX,menuY+6);
    printf("0 返回上一级");
    SetPos(menuX,menuY+8);
    printf("请输入您的选择： ");
}
//查看会员
void SeeAll(VIP *V_Head){
    system("cls");
    printf("姓名\t\t手机号\t\t注册时间(年/月/日)\t\t\n");
    VIP *cur = V_Head->next;
    int flag = 0;
    while(cur != NULL){
        flag ++;
        printf("%-16s%-20s%d/%d/%d\n",cur->name,cur->phone,cur->RegTime.year,cur->RegTime.month,cur->RegTime.day);
        cur = cur->next;
    }
    printf("会员总数:%d\n",flag);
    system("pause");
}
//注册会员
void RegisterVIP(VIP *V_Head){
    system("cls");
    VIP *p = (VIP*)malloc(sizeof(VIP));
    SetPos(titleX,titleY);
    printf("会员注册");
    SetPos(menuX,menuY);
    printf("姓  名:\t");
    SetPos(menuX,menuY+1);
    printf("手机号:\t");
    char temp[50];
    while (1) {
        memset(temp, 0, sizeof(temp));
        SetPos(menuX + 9, menuY);
        s_get(temp,50);
        if (strlen(temp) >= name_size) {      //判断名字是否输入过长
            SetPos(menuX + 9, titleY + 1);
            int i;
            for (i = 0; i < strlen(temp); i++)
                printf(" ");
            SetPos(menuX + 9, titleY + 1);
            printf("非法:\t名字输入过长，请重新输入");
            Sleep(1000);
            SetPos(menuX + 9, titleY + 1);
            printf("                 ");
        } else {
            strcpy(p->name, temp);
            break;
        }
    }
    while (1) {
        memset(temp, 0, sizeof(temp));
        SetPos(menuX + 9, menuY + 1);
        s_get(temp,50);
        if (strlen(temp) != 11) {      //判断手机号位数是否正确
            SetPos(menuX + 9, menuY + 1);
            int i;
            for (i = 0; i < strlen(temp); i++)
                printf(" ");
            SetPos(menuX + 9, menuY + 1);
            printf("非法:\t手机号输入非法，请重新输入");
            Sleep(1000);
            SetPos(menuX + 9, menuY + 1);
            printf("                                          ");
        } else {
            int i = 0;
            for (i = 0; i < 11; i++) {
                if (!isdigit(temp[i]))
                    break;
            }
            if (i == 11) {
                strcpy(p->phone,temp);
                break;
            }
            SetPos(menuX + 9, titleY + 3);
            printf("手机号含有非数字,请重新输入");
            Sleep(1000);
            SetPos(menuX + 9, titleY + 3);
            printf("                                   ");
        }
    }
    SetPos(menuX,menuY+2);
    printf("是否注册  1是  0否");
    int choice = 0;
    while(1) {
        SetPos(menuX, menuY + 3);
        printf("请输入您的选择:\t");
        choice = GetChoice();
        if(choice == 1||choice == 0){
            Date today = GetTodayDate();
            p->RegTime = today;
            break;
        }
        SetPos(menuX, menuY + 3);
        printf("                                 ");
    }
    if(choice == 1){
        VIP* cur = V_Head;
        while(cur->next != NULL){
            cur = cur->next;
        }
        cur->next = p;
        p->next = NULL;
        WriteVIP(V_Head);
        system("cls");
        SetPos(titleX, titleY + 1);
        printf("注册成功！");
        Sleep(1000);
        return;
    }else{
        free(p);
        return ;
    }
}
//查询会员
VIP* FindVIP(VIP *V_Head){
    system("cls");
    SetPos(titleX,titleY);
    printf("查询会员");
    SetPos(menuX,menuY);
    printf("请输入会员手机号:");
    SetPos(menuX,menuY+1);
    printf("(输入q退出)");
    char temp[50];
    while (1) {
        memset(temp, 0, sizeof(temp));
        SetPos(menuX,menuY);
        printf("请输入会员手机号:");
        s_get(temp,50);
        if (strlen(temp) != 11) {      //判断手机号位数是否正确
            SetPos(menuX, menuY);
            int i;
            printf("请输入会员手机号:");
            if(strlen(temp) == 1&&(temp[0] == 'q'||temp[0] == 'Q')){
                return V_Head;
            }
            for (i = 0; i < strlen(temp); i++)
                printf(" ");
            SetPos(menuX, menuY);
            printf("请输入会员手机号:非法:手机号输入非法，请重新输入                  ");
            Sleep(800);
            SetPos(menuX,menuY);
            printf("请输入会员手机号:                               ");
        } else {
            int i = 0;
            for (i = 0; i < 11; i++) {
                if (!isdigit(temp[i]))
                    break;
            }
            if (i == 11) {
                break;
            }
            SetPos(menuX+9, titleY);
            printf("请输入会员手机号:手机号含有非数字,请重新输入                    ");
            Sleep(800);
            SetPos(menuX,menuY);
            printf("请输入会员手机号:                               ");
        }
    }
    VIP *cur = V_Head->next;
    while(cur != NULL){
        if(strcmp(cur->phone, temp) == 0){
            return cur;
        }
        cur = cur->next;
    }
    return cur;
}
//修改会员信息
void ChangeVIPInfo(VIP *V_Head){
    VIP *NeedToCh = FindVIP(V_Head);
    SetPos(menuX,menuY);
    if(NeedToCh == NULL){
        SetPos(menuX,menuY+1);
        printf("查无此会员          ");
    }else if(NeedToCh != V_Head){
        SetPos(menuX,menuY+1);
        printf("姓名:%s",NeedToCh ->name);
        SetPos(menuX,menuY+2);
        printf("手机号:%s",NeedToCh ->phone);
        SetPos(menuX,menuY+3);
        printf("注册时间(年/月/日):%d/%d/%d",NeedToCh ->RegTime.year,NeedToCh ->RegTime.month,NeedToCh ->RegTime.day);
    }
    if(NeedToCh == V_Head){
        return;
    }
    while(1) {
        SetPos(menuX, menuY + 4);
        printf("可以修改的选项:  1姓名  2手机号   0退出");
        SetPos(menuX, menuY + 5);
        printf("请输入需要修改的选项: ");
        int choice = GetChoice();
        switch (choice){
            case 1:
                SetPos(menuX, menuY + 4);
                printf("                                                ");
                SetPos(menuX, menuY + 5);
                printf("                                                ");
                SetPos(menuX, menuY + 4);
                printf("请输入修改后的姓名: ");
                char temp[50];
                while (1) {
                    memset(temp, 0, sizeof(temp));
                    SetPos(menuX, menuY + 4);
                    printf("请输入修改后的姓名: ");
                    s_get(temp,50);
                    if (strlen(temp) >= name_size) {      //判断名字是否输入过长
                        SetPos(menuX, menuY + 4);
                        printf("请输入修改后的姓名: ");
                        int i;
                        for (i = 0; i < strlen(temp); i++)
                            printf(" ");
                        SetPos(menuX, menuY + 4);
                        printf("请输入修改后的姓名: ERROR：输入名字过长");
                        Sleep(1000);
                        SetPos(menuX, menuY + 4);
                        printf("请输入修改后的姓名:                                       ");
                    } else {
                        strcpy(NeedToCh->name, temp);
                        break;
                    }
                }
                WriteVIP(V_Head);
                break;
                case 2:
                SetPos(menuX, menuY + 4);
                printf("                                                ");
                SetPos(menuX, menuY + 5);
                printf("                                                ");
                SetPos(menuX, menuY + 4);
                printf("请输入修改后的手机号: ");
                while (1) {
                    memset(temp, 0, sizeof(temp));
                    SetPos(menuX, menuY + 4);
                    printf("请输入修改后的手机号: ");
                    s_get(temp,50);
                    if (strlen(temp) != 11) {      //判断手机号位数是否正确
                        SetPos(menuX, menuY + 4);
                        printf("请输入修改后的手机号: ");
                        int i;
                        for (i = 0; i < strlen(temp); i++)
                            printf(" ");
                        SetPos(menuX, menuY + 4);
                        printf("请输入修改后的手机号: 非法:\t手机号输入非法，请重新输入");
                        Sleep(1000);
                        SetPos(menuX, menuY + 4);
                        printf("请输入修改后的手机号:                                     ");
                    } else {
                        int i = 0;
                        for (i = 0; i < 11; i++) {
                            if (!isdigit(temp[i]))
                                break;
                        }
                        if (i == 11) {
                            strcpy(NeedToCh->phone,temp);
                            break;
                        }
                        SetPos(menuX, titleY + 4);
                        printf("请输入修改后的手机号: 手机号含有非数字,请重新输入");
                        Sleep(1000);
                        SetPos(menuX, titleY + 4);
                        printf("请输入修改后的手机号:                                     ");
                    }
                }
                WriteVIP(V_Head);
                break;
            default:
                break;
        }
        if(0 == choice)
            break;
    }
}
//删除链表
void FreeVIPNode(VIP *V_Head){
    VIP *cur = V_Head->next;
    VIP *temp = cur;
    while(cur!=NULL) {
        temp = cur;
        cur = cur->next;
        free(temp);
    }
    free(V_Head);
    V_Head = NULL;
}
//检测会员是否过期,过期自动删除
void DeleteIfOutDate(VIP *V_Head){
    VIP *cur = V_Head->next;
    VIP *B_cur = V_Head;
    VIP *temp = NULL;
    while(cur != NULL){
        if(GetRelativeTime(GetTodayDate())-GetRelativeTime(cur->RegTime) >= 365){
            temp = cur;
            B_cur->next = cur->next;
            cur = cur->next;
            free(temp);
            continue;
        }
        cur = cur->next;
        B_cur = B_cur->next;
    }
    WriteVIP(V_Head);
}
void BandR(Admin *A_Head, in_Goods *inGoods_Head, out_Goods *outGoods_Head,
           Goods *G_Head, VIP *V_Head){
    int choice = 0;
    while(1) {
        system("cls");
        SetPos(titleX,titleY);
        printf(" 数据备份与恢复");
        SetPos(menuX,menuY);
        printf("1 数据备份");
        SetPos(menuX,menuY+1);
        printf("2 数据恢复");
        SetPos(menuX,menuY+2);
        printf("0 返回上一级");
        SetPos(menuX, menuY + 3);
        printf("请输入您的选择: ");
        choice = GetChoice();
        switch (choice){
            case 1:
                Backup(A_Head,inGoods_Head,outGoods_Head,G_Head,V_Head);
                SetPos(menuX, menuY + 4);
                printf("数据备份成功");
                SetPos(menuX, menuY + 5);
                system("pause");
                break;
            case 2:
                Restore(A_Head,inGoods_Head,outGoods_Head,G_Head,V_Head);
                SetPos(menuX, menuY + 4);
                printf("数据恢复成功");
                SetPos(menuX, menuY + 5);
                system("pause");
                break;
        }
        if(choice == 0){
            return ;
        }
    }
}