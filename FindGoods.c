#include "FindGoods.h"
#include <stdio.h>
#include "ChangeGoodsInfo.h"

void FindMain(Goods *G_Head, in_Goods *inGoods_Head) {
    int choice;
    while (1) {
        system("cls");
        SetPos(titleX, titleY);
        printf("商品查询菜单");
        SetPos(menuX, menuY);
        printf("1.按商品名称查询");
        SetPos(menuX, menuY + 1);
        printf("2.按商品货号查询");
        SetPos(menuX, menuY + 2);
        printf("3.按商品厂家查询");
        SetPos(menuX, menuY + 3);
        printf("4.按商品类别查询");
        SetPos(menuX, menuY + 4);
        printf("5.模糊查询");
        SetPos(menuX, menuY + 5);
        printf("6.商品名称与厂家组合查询");
        SetPos(menuX, menuY + 6);
        printf("0.退出系统");
        SetPos(menuX, menuY + 7);
        printf("请输入您的选择:");
        choice = 0;
        choice = GetChoice();
        switch (choice) {
            case 0:
                break;
            case 1:
                find_1(G_Head, inGoods_Head);
                break;
            case 2:
                find_2(G_Head, inGoods_Head);
                break;
            case 3:
                find_3(G_Head);
                break;
            case 4:
                find_4(G_Head);
                break;
            case 5:
                find_5(G_Head);
                break;
            case 6:
                find_6(G_Head);
            default:
                break;
        }
        if (choice == 0) break;
    }
}

//根据名称查询
void find_1(Goods *G_Head, in_Goods *inGoods_Head) {
    system("cls");
    int j = 1;
    int i = 0;
    char name[50];
    char temp[50];
    int a[50];
    SetPos(menuX, menuY);
    printf("请输入您要查询商品的名称:");
    while (1) {
        memset(temp, 0, sizeof(temp));
        SetPos(menuX + 30, menuY);
        s_get(temp, 50);
        if (strlen(temp) >= name_size) {      //判断名字是否输入过长
            SetPos(menuX + 30, titleY + 2);
            int i;
            for (i = 0; i < strlen(temp); i++)
                printf("   ");
            SetPos(menuX + 30, titleY + 2);
            printf("非法:\t名字输入过长，请重新输入     ");
            Sleep(1000);
            SetPos(menuX + 30, titleY + 2);
            printf("                                                                       ");
        } else {
            strcpy(name, temp);
            break;
        }
    }
    system("cls");
    Goods *p;//在汇总链表中查询
    p = FindByName_2(name, G_Head);
    if (p == NULL) {
        SetPos(menuX, menuY + 2);
        printf("无该商品");
        SetPos(menuX, menuY + 3);
        system("pause");
    } else {
        printf("批次\t商品名称\t货号\t种类\t经手人\t入库数量\t生产日期\t进货单价\t生产厂家\t售货单价\t保质期(年/月/日)\t销量\t总数\t折扣\t\n");
        in_Goods *q;//在入库链表中查询
        q = inGoods_Head->next;
        while (q != NULL) {
            if (strcmp(q->name, name) == 0) {
                if (q->P_num != 0) {
                    printf("%05d\t%-16s%05d\t%-8s%-8s%-16d%d/%d/%-10d%-15.2f%-16s%-16.2f%d/%d/%-19d%-8d%-8d%.2f\n", j,
                           q->name, q->goods_id, q->kind, q->admin, q->P_In_num, q->P_date.year, q->P_date.month,
                           q->P_date.day, q->P_price, p->Manufacturer, p->S_price, p->Q_G_period.year,
                           p->Q_G_period.month, p->Q_G_period.day, p->sales_volume, p->total_num, p->discount);
                    j++;

                }
                q = q->next;
            } else q = q->next;
        }
        Goods *k;
        k = G_Head->next;
        while (k != NULL) {
            if (strcmp(k->name, name) == 0) {
                i++;
            }
            k = k->next;
        }
        printf("名叫%s的商品一共有%d种\n", name, i);
        system("pause");
    }
}

void find_2(Goods *G_Head, in_Goods *inGoods_Head) {
    system("cls");
    int i = 1;
    int j = 0;
    int id;

    while (1) {
        SetPos(menuX, menuY);
        printf("请输入您要查询商品的货号:");
        id = GetId();
        if (id == -1 || id == -2) {
            SetPos(menuX, menuY);
            printf("请输入您要查询商品的货号:输入格式错误，请重新输入                                                           ");
            Sleep(800);
            SetPos(menuX, menuY);
            printf("                                                                                         ");
        } else
            break;
    }
    system("cls");
    Goods *p;//在汇总链表中查询
    p = FindByID_2(id, G_Head);
    if (p == NULL) {
        SetPos(menuX, menuY + 2);
        printf("无该商品\n");
        SetPos(menuX, menuY + 3);
        system("pause");
    } else {
        printf("批次\t商品名称\t货号\t种类\t经手人\t入库数量\t生产日期\t进货单价\t生产厂家\t售货单价\t保质期(年/月/日)\t销量\t库存\t折扣\t\n");
        in_Goods *q;//在入库链表中查询
        q = inGoods_Head->next;
        while (q != NULL) {
            if (q->goods_id == id) {
                if (q->P_num != 0) {
                    printf("%05d\t%-16s%05d\t%-8s%-8s%-16d%d/%d/%-10d%-15.2f%-16s%-16.2f%d/%d/%-19d%-8d%-8d%.2f\n", i,
                           q->name, q->goods_id, q->kind, q->admin, q->P_In_num, q->P_date.year, q->P_date.month,
                           q->P_date.day, q->P_price, p->Manufacturer, p->S_price, p->Q_G_period.year,
                           p->Q_G_period.month, p->Q_G_period.day, p->sales_volume, p->total_num, p->discount);
                    i++;
                    j++;
                    q = q->next;
                } else q = q->next;
            } else q = q->next;
        }
        printf("统计：%s商品，一共入库%d批，库存%d\n", p->name, j, p->total_num);
        system("pause");
    }
}

void find_3(Goods *G_Head) {
    system("cls");
    int j = 0;
    int i = 0;
    char facture[50];
    char temp[50];
    SetPos(menuX, menuY);
    printf("请输入您要查询的生产厂家:");
    while (1) {
        memset(temp, 0, sizeof(temp));
        SetPos(menuX + 30, menuY);
        s_get(temp, 50);
        if (strlen(temp) >= name_size) {      //判断名字是否输入过长
            SetPos(menuX + 30, titleY + 2);
            int i;
            for (i = 0; i < strlen(temp); i++)
                printf("   ");
            SetPos(menuX + 30, titleY + 2);
            printf("非法:\t输入过长，请重新输入");
            Sleep(1000);
            SetPos(menuX + 30, titleY + 2);
            printf("                                                                       ");
        } else {
            strcpy(facture, temp);
            break;
        }
    }
    system("cls");
    Goods *q;//在汇总链表中查询
    q = G_Head->next;
    printf("商品名称\t货号\t商品种类\t售货单价\t保质期(年/月/日)\t销量\t库存\t折扣\t\n");
    while (q != NULL) {
        if (strcmp(q->Manufacturer, facture) == 0) {
            printf("%-16s%05d\t%-16s%-16.2f%d/%d/%-19d%-8d%-8d%.2f\n", q->name, q->goods_id, q->kind, q->S_price,
                   q->Q_G_period.year, q->Q_G_period.month, q->Q_G_period.day, q->sales_volume, q->total_num,
                   q->discount);
            j = 1;
            i++;
            q = q->next;
        } else q = q->next;
    }
    if (j == 0) {
        SetPos(menuX, menuY + 2);
        printf("未找到该生产厂家\n");
        SetPos(menuX, menuY + 3);
        system("pause");
        return;
    } else {
        printf("统计：%s厂家，一共%d种商品\n", facture, i);
    }
    system("pause");
}


void find_4(Goods *G_Head) {
    system("cls");
    int j = 0;
    int i = 0;
    char kind[50];
    char temp[50];
    SetPos(menuX, menuY);
    printf("请输入您要查询的商品种类:");
    while (1) {
        memset(temp, 0, sizeof(temp));
        SetPos(menuX + 30, menuY);
        s_get(temp, 50);
        if (strlen(temp) >= name_size) {      //判断名字是否输入过长
            SetPos(menuX + 30, titleY + 2);
            int i;
            for (i = 0; i < strlen(temp); i++)
                printf("   ");
            SetPos(menuX + 30, titleY + 2);
            printf("非法:\t输入过长，请重新输入");
            Sleep(1000);
            SetPos(menuX + 30, titleY + 2);
            printf("                                                            ");
        } else {
            strcpy(kind, temp);
            break;
        }
    }
    system("cls");
    Goods *q;//在汇总链表中查询
    q = G_Head->next;
    printf("商品名称\t货号\t生产厂家\t售货单价\t保质期(年/月/日)\t销量\t库存\t折扣\t\n");
    while (q != NULL) {
        if (strcmp(q->kind, kind) == 0) {
            printf("%-16s%05d\t%-16s%-16.2f%d/%d/%-19d%-8d%-8d%.2f\n", q->name, q->goods_id, q->Manufacturer,
                   q->S_price, q->Q_G_period.year, q->Q_G_period.month, q->Q_G_period.day, q->sales_volume,
                   q->total_num, q->discount);
            j = 1;
            i++;
            q = q->next;
        } else q = q->next;
    }
    if (j == 0) {
        SetPos(menuX, menuY + 2);
        printf("无该类商品\n");
        SetPos(menuX, menuY + 3);
        system("pause");
        return;
    } else {
        printf("统计：%s类的商品，一共%d种\n", kind, i);
    }
    system("pause");
}

void find_5(Goods *G_Head) {
    system("cls");
    int j = 0;
    char words[50];
    char temp[50];
    SetPos(menuX, menuY);
    printf("请输入模糊词汇:");
    while (1) {
        memset(temp, 0, sizeof(temp));
        SetPos(menuX+15, menuY);
        s_get(temp, 50);
        if (strlen(temp) >= name_size) {      //判断名字是否输入过长
            SetPos(menuX + 15, titleY + 2);
            int i;
            for (i = 0; i < strlen(temp); i++)
                printf("   ");
            SetPos(menuX + 15, titleY + 2);
            printf("非法:\t输入过长，请重新输入");
            Sleep(1000);
            SetPos(menuX + 15, titleY + 2);
            printf("                                                                       ");
        } else {
            strcpy(words, temp);
            break;
        }
    }
    system("cls");
    Goods *q;//在汇总链表中查询
    q = G_Head->next;
    printf("商品名称\t货号\t生产厂家\t售货单价\t保质期(年/月/日)\t销量\t库存\t折扣\t\n");
    while (q != NULL) {
        if (compare(q->name, words) == 0) {
            printf("%-16s%05d\t%-16s%-16.2f%d/%d/%-19d%-8d%-8d%.2f\n", q->name, q->goods_id, q->Manufacturer,
                   q->S_price, q->Q_G_period.year, q->Q_G_period.month, q->Q_G_period.day, q->sales_volume,
                   q->total_num, q->discount);
            j = 1;
            printf("%s可能是%s\n", words, q->name);
            q = q->next;
        } else q = q->next;
    }
    if (j == 0) {
        SetPos(menuX, menuY + 2);
        printf("无该商品\n");
        SetPos(menuX, menuY + 3);
        system("pause");
        return;
    }
    system("pause");
}

void find_6(Goods *G_Head) {
    system("cls");
    int j = 0;
    char facture[50];
    char name[50];
    char temp[50];
    SetPos(menuX, menuY);
    printf("请输入您要查询的生产厂家:");
    while (1) {
        memset(temp, 0, sizeof(temp));
        SetPos(menuX + 30, menuY);
        s_get(temp, 50);
        if (strlen(temp) >= name_size) {      //判断名字是否输入过长
            SetPos(menuX + 30, titleY + 2);
            int i;
            for (i = 0; i < strlen(temp); i++)
                printf("   ");
            SetPos(menuX + 30, titleY + 2);
            printf("非法:\t输入过长，请重新输入");
            Sleep(1000);
            SetPos(menuX + 30, titleY + 2);
            printf("                                                      ");
        } else {
            strcpy(facture, temp);
            break;
        }
    }
    SetPos(menuX, menuY + 2);
    printf("请输入您要查询商品的名称:");
    while (1) {
        memset(temp, 0, sizeof(temp));
        SetPos(menuX + 30, menuY + 2);
        s_get(temp, 50);
        if (strlen(temp) >= name_size) {      //判断名字是否输入过长
            SetPos(menuX + 30, titleY + 4);
            int i;
            for (i = 0; i < strlen(temp); i++)
                printf("   ");
            SetPos(menuX + 30, titleY + 4);
            printf("非法:\t名字输入过长，请重新输入");
            Sleep(1000);
            SetPos(menuX + 30, titleY + 4);
            printf("                                                      ");
        } else {
            strcpy(name, temp);
            break;
        }
    }
    system("cls");
    Goods *q;//在汇总链表中查询
    q = G_Head->next;
    printf("商品名称\t货号\t商品种类\t售货单价\t保质期(年/月/日)\t销量\t库存\t折扣\t\n");
    while (q != NULL) {
        if (strcmp(q->Manufacturer, facture) == 0 && strcmp(q->name, name) == 0) {
            printf("%-16s%05d\t%-16s%-16.2f%d/%d/%-19d%-8d%-8d%.2f\n", q->name, q->goods_id, q->kind, q->S_price,
                   q->Q_G_period.year, q->Q_G_period.month, q->Q_G_period.day, q->sales_volume, q->total_num,
                   q->discount);
            j = 1;
            printf("统计：%s厂家的%s商品的库存为%d\n", facture, name, q->total_num);
            q = q->next;
        } else q = q->next;
    }
    if (j == 0) {
        SetPos(menuX, menuY + 2);
        printf("未找到符合条件的商品\n");
        SetPos(menuX, menuY + 3);
        system("pause");
        return;
    }
    system("pause");
}

int compare(char a[], char b[]) {
    int i = 0, j = 0;
    while (a[i] != '\0') {
        if (a[i] == b[j]) {
            i++;
            j++;
            if (b[j] == '\0') {
                return (0);
            }
        } else {
            if (a[i + 1] == '\0') {
                return (1);
            }
            i++;
        }
    }
}

