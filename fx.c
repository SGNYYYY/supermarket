//
// Created by SGNY on 2020/5/8.
//
#include "structandfx.h"
#include <stdio.h>
#include <time.h>

//设置光标位置，左上角为原点，向下为y轴正方向，向右为x轴正方向
void SetPos(int x, int y) {
    COORD pos;
    HANDLE handle;
    pos.X = x;
    pos.Y = y;
    handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(handle, pos);
}
//读取字符串
char* s_get(char* st, int n)//一个参数是指针，另一个是长度大小
{
    char* want;
    int i = 0;
    want = fgets(st, n, stdin);
    if (st)
    {
        while (st[i] != '\n' && st[i] != '\0')i++;
        if (st[i] == '\n')st[i] = '\0';
        else
            while (getchar() != '\n')continue;
    }
    return want;
}
//选择菜单获取用户选择函数
int GetChoice() {
    int choice = 0;
    int flag = 0;
    int isInput = 0;//是否输入数字，有输入为1
    char c;
    while ((c = getchar()) != '\n') {
        if (c >= '0' && c <= '9') {
            choice = choice * 10 + c - '0';
            isInput = 1;
        } else {
            flag = 1;
        }
    }
    if(isInput == 0||flag == 1)
        return 10;
    if(flag == 0){
        return choice;
    }
}

//获取当前时间
Date GetTodayDate() {
    time_t timep;//time_t就是long，函数返回从1970年1月1日（MFC是1899年12月31日）0时0分0秒，到现在的的秒数。
    struct tm *p;
    time(&timep);
    p = gmtime(&timep);//将日历时间转化为世界标准时间（即格林尼治时间）
    Date Today;
    Today.year = p->tm_year + 1900;
    Today.month = p->tm_mon + 1;
    Today.day = p->tm_mday;
    return Today;
}

//用姓名查询汇总链表
Goods *FindByName_2(char *name, Goods *G_Head) {
    Goods *p;
    p = G_Head->next;
    while (p != NULL) {
        if (strcmp(p->name, name) == 0) {
            return p;
        } else p = p->next;
    }
    return p;
}

//用id查询汇总链表
Goods *FindByID_2(int id, Goods *G_Head) {
    Goods *p;
    p = G_Head->next;
    while (p != NULL) {
        if (id == p->goods_id) {
            return p;
        } else p = p->next;
    }
    return p;
}

int GetRelativeTime(Date day) {


    int c[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int l[12] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int sum = 0;
    int i = day.year - 2019;
    sum += i * 365 + (i + 2) / 4 + (i + 2) / 400 - (i + 2) / 100;
    if ((day.year % 4 == 0 && day.year % 100 != 0) || day.year % 400 == 0) {
        for (i = 0; i < day.month - 1; i++) {
            sum += l[i];
        }
    } else {
        for (i = 0; i < day.month - 1; i++) {
            sum += c[i];
        }
    }
    sum += day.day;
    return sum;
}

//将管理员信息读入链表
Admin *ReadAdmin() {
    FILE *fp;
    if ((fp = fopen("Admin.txt", "r")) == NULL) {
        printf("File open error!\n");
        system("pause");
        exit(0);
    }
    Admin *Head = (Admin *) malloc(sizeof(Admin));
    Admin *temp = Head;
    Admin *room, *p;
    room = (Admin *) malloc(sizeof(Admin));
    memset(room->admin_id, 0, sizeof(room->admin_id));
    memset(room->name, 0, sizeof(room->name));
    memset(room->pwd, 0, sizeof(room->pwd));
    memset(room->phone, 0, sizeof(room->phone));
    memset(room->qu, 0, sizeof(room->qu));
    memset(room->ans, 0, sizeof(room->ans));
    while (fscanf(fp, "%s%s%s%s%s%s", room->admin_id, room->name, room->pwd, room->phone, room->qu,
                  room->ans) != EOF) {

        //fscanf(fp,"%s%s%s%s%s%s",room[num].admin_id,room[num].name,room[num].pwd,room[num].phone,room[num].qu,room[num].ans);
        p = (Admin *) malloc(sizeof(Admin));
        strcpy(p->admin_id, room->admin_id);
        strcpy(p->name, room->name);
        strcpy(p->pwd, room->pwd);
        strcpy(p->phone, room->phone);
        strcpy(p->qu, room->qu);
        strcpy(p->ans, room->ans);
        memset(room->admin_id, 0, sizeof(room->admin_id));
        memset(room->name, 0, sizeof(room->name));
        memset(room->pwd, 0, sizeof(room->pwd));
        memset(room->phone, 0, sizeof(room->phone));
        memset(room->qu, 0, sizeof(room->qu));
        memset(room->ans, 0, sizeof(room->ans));
        temp->next = p;
        temp = p;
    }
    temp->next = NULL;
    free(room);
    if (fclose(fp)) {
        printf("Can not close the file!\n");
        system("pause");
        exit(0);
    }
    return Head;
}

//将管理员链表数据写入文件
void WriteAdmin(Admin *A_Head) {
    FILE *fp;
    if ((fp = fopen("Admin.txt", "w")) == NULL) {//D:\\SUPERMARKET\\super_v1\\
        printf("File open error!\n");
        system("pause");
        exit(0);
    }
    Admin *cur = A_Head->next;
    while (cur != NULL) {
        fprintf(fp, "%s %s %s %s %s %s\n", cur->admin_id, cur->name, cur->pwd, cur->phone, cur->qu, cur->ans);
        cur = cur->next;
    }
    if (fclose(fp)) {
        printf("Can not close the file!\n");
        system("pause");
        exit(0);
    }
}

//将入库信息读入链表
in_Goods *ReadInGoods() {
    FILE *fp;
    if ((fp = fopen("InGoods.txt", "r")) == NULL) {
        printf("File open error!\n");
        system("pause");
        exit(0);
    }
    in_Goods *Head = (in_Goods *) malloc(sizeof(in_Goods));
    in_Goods *temp = Head;
    in_Goods *room, *p;
    room = (in_Goods *) malloc(sizeof(in_Goods));
    memset(room->name, 0, sizeof(room->name));
    memset(room->unit, 0, sizeof(room->unit));
    memset(room->kind, 0, sizeof(room->kind));
    memset(room->admin, 0, sizeof(room->admin));
    while (fscanf(fp, "%d%s%d%d%s%lf%d%d%d%d%d%d%s%s", &room->goods_id, room->name, &room->P_num,
                  &room->P_In_num, room->unit, &room->P_price,
                  &room->P_date.year, &room->P_date.month, &room->P_date.day,
                  &room->In_date.year, &room->In_date.month, &room->In_date.day,
                  room->kind, room->admin) != EOF) {
        p = (in_Goods *) malloc(sizeof(in_Goods));
        p->goods_id = room->goods_id;
        p->P_num = room->P_num;
        p->P_In_num = room->P_In_num;
        p->P_price = room->P_price;
        p->P_date = room->P_date;
        p->In_date = room->In_date;
        strcpy(p->name, room->name);
        strcpy(p->unit, room->unit);
        strcpy(p->kind, room->kind);
        strcpy(p->admin, room->admin);
        memset(room->name, 0, sizeof(room->name));
        memset(room->unit, 0, sizeof(room->unit));
        memset(room->kind, 0, sizeof(room->kind));
        memset(room->admin, 0, sizeof(room->admin));
        temp->next = p;
        temp = p;
    }
    temp->next = NULL;
    free(room);
    if (fclose(fp)) {
        printf("Can not close the file!\n");
        system("pause");
        exit(0);
    }
    return Head;
}

//将出库信息读入链表
out_Goods *ReadOutGoods() {
    FILE *fp;
    if ((fp = fopen("OutGoods.txt", "r")) == NULL) {
        printf("File open error!\n");
        system("pause");
        exit(0);
    }
    out_Goods *Head = (out_Goods *) malloc(sizeof(out_Goods));
    out_Goods *temp = Head;
    out_Goods *room, *p;
    room = (out_Goods *) malloc(sizeof(out_Goods));
    memset(room->name, 0, sizeof(room->name));
    memset(room->remark, 0, sizeof(room->remark));
    memset(room->admin, 0, sizeof(room->admin));
    while (fscanf(fp, "%d%s%d%s%lf%lf%d%d%d%d%d%d%s", &room->goods_id, room->name, &room->Out_num,
                  room->remark,
                  &room->discount, &room->S_price,
                  &room->P_date.year, &room->P_date.month, &room->P_date.day,
                  &room->Out_date.year, &room->Out_date.month, &room->Out_date.day,
                  room->admin) != EOF) {
        p = (out_Goods *) malloc(sizeof(out_Goods));
        p->goods_id = room->goods_id;
        p->Out_num = room->Out_num;
        p->discount = room->discount;
        p->S_price = room->S_price;
        p->P_date = room->P_date;
        p->Out_date = room->Out_date;
        strcpy(p->name, room->name);
        strcpy(p->remark, room->remark);
        strcpy(p->admin, room->admin);
        memset(room->name, 0, sizeof(room->name));
        memset(room->remark, 0, sizeof(room->remark));
        memset(room->admin, 0, sizeof(room->admin));
        temp->next = p;
        temp = p;
    }
    temp->next = NULL;
    free(room);
    if (fclose(fp)) {
        printf("Can not close the file!\n");
        system("pause");
        exit(0);
    }
    return Head;
}

//将入库链表数据读入文件
void WriteInGoods(in_Goods *inGoods_Head) {
    FILE *fp;
    if ((fp = fopen("InGoods.txt", "w")) == NULL) {
        printf("File open error!\n");
        exit(0);
    }
    in_Goods *cur = inGoods_Head->next;
    while (cur != NULL) {
        fprintf(fp, "%d %s %d %d %s %f %d %d %d %d %d %d %s %s\n", cur->goods_id, cur->name, cur->P_num, cur->P_In_num,
                cur->unit,
                cur->P_price, cur->P_date.year, cur->P_date.month, cur->P_date.day,
                cur->In_date.year, cur->In_date.month, cur->In_date.day,
                cur->kind, cur->admin);
        cur = cur->next;
    }
    if (fclose(fp)) {
        printf("Can not close the file!\n");
        exit(0);
    }
}

void WriteOutGoods(out_Goods *outGoods_Head)//将出库链表数据读入文件
{
    FILE *fp;
    if ((fp = fopen("OutGoods.txt", "w")) == NULL) {
        printf("File open error!\n");
        exit(0);
    }
    out_Goods *cur = outGoods_Head->next;
    while (cur != NULL) {
        fprintf(fp, "%d %s %d %s %f %f %d %d %d %d %d %d %s\n", cur->goods_id, cur->name, cur->Out_num, cur->remark,
                cur->discount,
                cur->S_price, cur->P_date.year, cur->P_date.month, cur->P_date.day,
                cur->Out_date.year, cur->Out_date.month, cur->Out_date.day,
                cur->admin);
        cur = cur->next;
    }
    if (fclose(fp)) {
        printf("Can not close the file!\n");
        exit(0);
    }
}

//文件写入汇总链表
Goods *ReadGoods() {
    FILE *fp;
    if ((fp = fopen("Goods.txt", "r")) == NULL) {
        printf("cannot open this file\n");
        exit(0);
    }
    Goods *h = (Goods *) malloc(sizeof(Goods));
    Goods *temp = h;
    Goods *New = NULL;
    Goods *cur = (Goods *) malloc(sizeof(Goods));
    cur->goods_id = 0;
    memset(cur->name, 0, sizeof(cur->name));
    cur->S_price = 0;
    memset(cur->kind, 0, sizeof(cur->kind));
    cur->total_num = 0;
    cur->Q_G_period.year = cur->Q_G_period.month = cur->Q_G_period.day = 0;
    cur->sales_volume = 0;
    memset(cur->unit, 0, sizeof(cur->unit));
    memset(cur->Manufacturer, 0, sizeof(cur->Manufacturer));
    cur->avg_time = 0;
    cur->discount = 0;
    cur->MaximumNum = 0;
    while ((fscanf(fp, "%d %s %lf %s %d %d %d %d %d %s %s %lf %lf %d", &cur->goods_id, cur->name, &cur->S_price,
                   cur->kind, &cur->total_num, &cur->Q_G_period.year,
                   &cur->Q_G_period.month, &cur->Q_G_period.day, &cur->sales_volume, cur->unit, cur->Manufacturer,
                   &cur->avg_time,
                   &cur->discount, &cur->MaximumNum) != EOF)) {
        New = (Goods *) malloc(sizeof(Goods));
        New->goods_id = cur->goods_id;
        strcpy(New->name, cur->name);
        New->S_price = cur->S_price;
        strcpy(New->kind, cur->kind);
        New->total_num = cur->total_num;
        New->Q_G_period = cur->Q_G_period;
        New->sales_volume = cur->sales_volume;
        strcpy(New->unit, cur->unit);
        strcpy(New->Manufacturer, cur->Manufacturer);
        New->avg_time = cur->avg_time;
        New->discount = cur->discount;
        New->MaximumNum = cur->MaximumNum;
        cur->goods_id = 0;
        memset(cur->name, 0, sizeof(cur->name));
        cur->S_price = 0;
        memset(cur->kind, 0, sizeof(cur->kind));
        cur->total_num = 0;
        cur->Q_G_period.year = cur->Q_G_period.month = cur->Q_G_period.day = 0;
        cur->sales_volume = 0;
        memset(cur->unit, 0, sizeof(cur->unit));
        memset(cur->Manufacturer, 0, sizeof(cur->Manufacturer));
        cur->avg_time = 0;
        cur->discount = 0;
        cur->MaximumNum = 0;
        temp->next = New;
        temp = New;
    }
    temp->next = NULL;
    fclose(fp);
    free(cur);
    return h;
}

//汇总链表写入文件
void WriteGoods(Goods *G_Head) {
    FILE *fp = fopen("Goods.txt", "w+");
    if (fp == NULL) {
        printf("无法打开汇总文件");
        exit(0);
    }
    Goods *cur = G_Head->next;
    while (cur) {
        fprintf(fp, "%d %s %lf %s %d %d %d %d %d %s %s %lf %lf %d\n", cur->goods_id, cur->name, cur->S_price,
                cur->kind, cur->total_num, cur->Q_G_period.year, cur->Q_G_period.month, cur->Q_G_period.day,
                cur->sales_volume, cur->unit, cur->Manufacturer, cur->avg_time, cur->discount,
                cur->MaximumNum);
        cur = cur->next;
    }
    fclose(fp);
}

//将VIP信息从文件读入链表
VIP *ReadVIP() {
    FILE *fp;
    if ((fp = fopen("VIP.txt", "r+")) == NULL) {
        printf("File open error!\n");
        exit(0);
    }
    VIP *Head = (VIP *) malloc(sizeof(VIP));
    VIP *temp = Head;
    VIP *room, *p;
    room = (VIP *) malloc(100 * sizeof(VIP));
    int num = 0;
    memset(room[num].name, 0, sizeof(room[num].name));
    memset(room[num].phone, 0, sizeof(room[num].phone));
    while (fscanf(fp, "%s %s %d %d %d", room[num].name, room[num].phone, &room[num].RegTime.year,
                  &room[num].RegTime.month, &room[num].RegTime.day) != EOF) {

        //fscanf(fp,"%s%s%s%s%s%s",room[num].admin_id,room[num].name,room[num].pwd,room[num].phone,room[num].qu,room[num].ans);
        p = (VIP *) malloc(sizeof(VIP));
        strcpy(p->name, room[num].name);
        strcpy(p->phone, room[num].phone);
        p->RegTime = room[num].RegTime;
        num++;
        memset(room[num].name, 0, sizeof(room[num].name));
        memset(room[num].phone, 0, sizeof(room[num].phone));
        temp->next = p;
        temp = p;
    }
    temp->next = NULL;
    free(room);
    if (fclose(fp)) {
        printf("Can not close the file!\n");
        exit(0);
    }
    return Head;
}

void WriteVIP(VIP *V_Head) {
    FILE *fp;
    if ((fp = fopen("VIP.txt", "w")) == NULL) {//D:\\SUPERMARKET\\super_v1\\
        printf("File open error!\n");
        system("pause");
        exit(0);
    }
    VIP *cur = V_Head->next;
    while (cur != NULL) {
        fprintf(fp, "%s %s %d %d %d\n", cur->name, cur->phone, cur->RegTime.year, cur->RegTime.month, cur->RegTime.day);
        cur = cur->next;
    }
    if (fclose(fp)) {
        printf("Can not close the file!\n");
        system("pause");
        exit(0);
    }
}

void FreeInGoodsNode(in_Goods *IG_Head) {
    in_Goods *cur = IG_Head->next;
    in_Goods *temp = cur;
    while (cur != NULL) {
        temp = cur;
        cur = cur->next;
        free(temp);
    }
    free(IG_Head);
    IG_Head = NULL;
}

void FreeOutGoodsNode(out_Goods *OG_Head) {
    out_Goods *cur = OG_Head->next;
    out_Goods *temp = cur;
    while (cur != NULL) {
        temp = cur;
        cur = cur->next;
        free(temp);
    }
    free(OG_Head);
    OG_Head = NULL;
}

void FreeGoodsNode(Goods *G_Head) {
    Goods *cur = G_Head->next;
    Goods *temp = cur;
    while (cur != NULL) {
        temp = cur;
        cur = cur->next;
        free(temp);
    }
    free(G_Head);
    G_Head = NULL;
}