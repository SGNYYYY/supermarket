#include "ChangeGoodsInfo.h"
#include <stdio.h>
#include <math.h>

void ChangeMain(Goods *G_Head) {
    system("cls");
    int id;
    int choice;
    choice = 0;

    while (1) {
        SetPos(titleX, titleY);
        printf("请输入您想要修改的商品的货号:");
        id = GetId();
        if (id == -1 || id == -2) {
            SetPos(menuX,titleY);
            printf("请输入您想要修改的商品的货号:输入格式错误，请重新输入                                                             ");
            Sleep(1000);
            SetPos(menuX, titleY);
            printf("请输入您想要修改的商品的货号:                                                                                              ");
        } else
            break;
    }
    Goods *p;
    p = FindByID_2(id, G_Head);
    if (p == NULL) {
        SetPos(titleX, titleY + 1);
        printf("未找到该商品\n");
        Sleep(1000);
    } else {
        while (1) {
            system("cls");
            SetPos(titleX, titleY);
            printf("商品信息修改菜单");
            SetPos(menuX, menuY);
            printf("1.修改该商品的生产厂家");
            SetPos(menuX, menuY + 1);
            printf("2.修改该商品的售价");
            SetPos(menuX, menuY + 2);
            printf("3.修改该商品的总数量");
            SetPos(menuX, menuY + 3);
            printf("0.退出");
            SetPos(menuX, menuY + 4);
            printf("请输入您的选择：");
            choice = GetChoice();
            switch (choice) {
                case 0:
                    break;
                case 1:
                    change_1(p, G_Head);
                    break;
                case 2:
                    change_2(p, G_Head);
                    break;
                case 3:
                    change_3(p, G_Head);
                    break;
            }
            if (choice == 0)
                break;
        }
    }
}

void change_1(Goods *p, Goods *G_Head) {
    int k = 0;
    while (1) {
        system("cls");
        SetPos(titleX, titleY);
        printf("该商品的名称:%s", p->name);
        SetPos(menuX, menuY);
        printf("该商品的货号:%05d", p->goods_id);
        SetPos(menuX, menuY + 1);
        printf("该商品的生产厂家:%s", p->Manufacturer);
        SetPos(menuX, menuY + 2);
        printf("请您确认是否继续修改（如果是请按1，不是请按0）");

        k = GetChoice();
        if (k == 1) {
            SetPos(menuX, menuY + 4);
            printf("您想将生产厂家修改为:");
            char facturer[50];
            while (1) {
                memset(facturer, 0, sizeof(facturer));
                SetPos(menuX + 25, menuY + 4);
                s_get(facturer, 50);
                if (strlen(facturer) >= name_size) {      //判断名字是否输入过长
                    SetPos(menuX + 25, titleY + 6);
                    int i;
                    for (i = 0; i < strlen(facturer); i++)
                        printf("   ");
                    SetPos(menuX + 25, titleY + 6);
                    printf("非法:\t输入过长，请重新输入");
                    Sleep(1000);
                    SetPos(menuX + 25, titleY + 6);
                    printf("                                                                          ");
                } else {
                    strcpy(p->Manufacturer, facturer);
                    WriteGoods(G_Head);
                    SetPos(menuX, menuY + 5);
                    printf("修改成功");
                    SetPos(menuX, menuY + 6);
                    system("pause");
                    break;
                }
            }
            break;
        } else if (k == 0) {
            SetPos(menuX, menuY + 3);
            printf("放弃修改");
            SetPos(menuX, menuY + 4);
            system("pause");
            break;
        }
    }
}

void change_2(Goods *p, Goods *G_Head) {
    int k;
    while (1) {
        system("cls");
        SetPos(titleX, titleY);
        printf("该商品的名称:%s", p->name);
        SetPos(menuX, menuY);
        printf("该商品的货号:%05d", p->goods_id);
        SetPos(menuX, menuY + 1);
        printf("该商品的售价:%.2f", p->S_price);
        SetPos(menuX, menuY + 2);
        printf("请您确认是否继续修改（如果是请按1，不是请按0）");

        k = GetChoice();
        if (k == 1) {
            double price;
            while (1) {
                SetPos(menuX, menuY + 4);
                printf("您想将售价修改为:");
                price = GetFloat();
                if (price == -1) {
                    SetPos(menuX, menuY + 4);
                    printf("您想将售价修改为:输入格式错误，请重新输入                                                              ");
                    Sleep(800);
                    SetPos(menuX, menuY + 4);
                    printf("您想将售价修改为:                                                                                         ");
                } else
                    break;
            }
            p->S_price = price;
            WriteGoods(G_Head);
            SetPos(menuX, menuY + 5);
            printf("修改成功");
            SetPos(menuX, menuY + 6);
            system("pause");
            break;
        } else if (k == 0) {
            SetPos(menuX, menuY + 3);
            printf("放弃修改");
            SetPos(menuX, menuY + 4);
            system("pause");
            break;
        }
    }
}

void change_3(Goods *p, Goods *G_Head) {
    int k;

    while (1) {
        system("cls");
        SetPos(titleX, titleY);
        printf("该商品的名称:%s", p->name);
        SetPos(menuX, menuY);
        printf("该商品的货号:%05d", p->goods_id);
        SetPos(menuX, menuY + 1);
        printf("该商品的总数量:%d", p->total_num);
        SetPos(menuX, menuY + 2);
        printf("请您确认是否继续修改（如果是请按1，不是请按0）");

        k = GetChoice();
        if (k == 1) {

            int num;
            while (1) {
                SetPos(menuX, menuY + 4);
                printf("您想将总数修改为:");
                num = GetInt();
                if (num == -1 || num == -2) {
                    SetPos(menuX, menuY + 4);
                    printf("您想将总数修改为:输入格式错误，请重新输入                                                             ");
                    Sleep(800);
                    SetPos(menuX, menuY + 4);
                    printf("您想将总数修改为:                                                                                              ");
                } else
                    break;
            }
            p->total_num = num;
            WriteGoods(G_Head);
            SetPos(menuX, menuY + 5);
            printf("修改成功");
            SetPos(menuX, menuY + 6);
            system("pause");
            break;
        } else if (k == 0) {
            SetPos(menuX, menuY + 3);
            printf("放弃修改");
            SetPos(menuX, menuY + 4);
            system("pause");
            break;
        }
    }

}

int GetInt() {
    char c;
    int total_num = 0;
    int isNum = 2;
    int isInput = 0;
    int isSeven = 0;
    while ((c = getchar()) != '\n') {
        if (c >= '0' && c <= '9') {
            total_num = total_num * 10 + c - '0';
            isInput = 1;
        } else {
            isNum = 1;
        }
        isSeven++;
    }
    if (isNum == 1 || isInput == 0) {
        return -1;
    }
    if (isSeven > 7) {
        return -2;
    }
    return total_num;
}

double GetFloat() {
    char c;
    int i = 1;
    int isInput = 0;
    int isFloat = 0;
    int Intpart = 0;
    int isNum = 2;
    int isISix = 0;
    int isFSix = 0;
    double FloatPart = 0;
    while ((c = getchar()) != '\n') {
        if (isFloat == 0) {
            if (c < '0' || c > '9') {
                if (c != '.')
                    isNum = 1;
                else if (c == '.') {
                    isFloat = 1;
                    continue;
                }
            } else {
                Intpart = Intpart * 10 + c - '0';
                isInput = 1;
            }
            isISix++;
        }
        if (isFloat == 1) {
            if (c >= '0' && c <= '9') {
                FloatPart += pow(0.1, i) * (c - '0');
                isInput = 1;
                i++;
            } else
                isNum = 1;
            isFSix++;
        }
    }
    if (isNum == 1 || isISix > 6 || isFSix >= 3 || isInput == 0)
        return -1;
    else
        return Intpart + FloatPart;
}

int GetId() {
    char c;
    int Goods_id = 0;
    int isNum = 2;
    int isFive = 0;
    while ((c = getchar()) != '\n') {
        if (c >= '0' && c <= '9') {
            Goods_id = Goods_id * 10 + c - '0';
            isNum = 0;
        } else {
            isNum = 1;
        }
        isFive++;
    }
    if (isNum == 1 || isNum == 2) {
        return -1;
    }
    if (isFive > 5) {
        return -2;
    }

    return Goods_id;
}
