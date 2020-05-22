//
// Created by SGNY on 2020/5/8.
//
#include "admin.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>
Admin* AdminMain(Admin *A_Head){
    system("cls");
    Admin *administer = NULL;
    while(1) {
        AdminMenu();//显示菜单
        int choice = GetChoice();//获取选择
        switch (choice){
            case 1:
                administer = SignIn(A_Head);
                break;
            case 2:
                ForgetPwd(A_Head);
                break;
            case 3:
                ChangePwd(A_Head);
                break;
            default:
                break;
        }
        if(choice == 0) {   //如果是0退出
            WriteAdmin(A_Head);
            FreeAdminNode(A_Head);
            return NULL;
        }
        if(administer != NULL) {
            WriteAdmin(A_Head);
            return administer;
        }
    }

}
//打印开始菜单
void AdminMenu(){
    system("cls");
    SetPos(titleX-13,titleY-2);
    printf("*******超市商品库存信息管理系统*******");
    int i = 0;
    for(i = 1;i <= 10;i++){
        SetPos(titleX-13,titleY-2+i);
        printf("*");
        SetPos(titleX+24,titleY-2+i);
        printf("*");
    }
    for(i = 1;i <= 36;i++){
        SetPos(titleX-13+i,titleY-2+10);
        printf("*");
    }
    SetPos(titleX,titleY);
    printf("开 始 菜 单");
    SetPos(menuX,menuY);
    printf("1 账号登陆");
    SetPos(menuX,menuY+1);
    printf("2 忘记密码");
    SetPos(menuX,menuY+2);
    printf("3 修改密码");
    SetPos(menuX,menuY+3);
    printf("0 退出系统");
    SetPos(menuX,menuY+4);
    printf("请输入您的选择： ");
}

//账号登陆
Admin* SignIn(Admin *A_Head){
    int isExist = 0;       //账号是否存在
    int isCorrect = 0;     //密码是否正确
    int inCorrect = 0;     //密码不正确次数
    char acc[50];
    while(!isCorrect) {
        system("cls");
        SetPos(titleX,titleY);
        printf("  登 陆");
        SetPos(titleX, titleY + 1);
        printf("账号:\t");
        SetPos(titleX, titleY + 2);
        printf("密码:\t");

        memset(acc,0,sizeof(acc));
        int size = 0;
        char c;
        SetPos(titleX+6, titleY + 1);
        while ((c = getchar()) != '\n') {
            acc[size++] = c;
            if (size == name_size - 1)
                break;
        }
        acc[size] = '\0';
        isExist = CheckAcc(acc,A_Head);
        if(isExist == 0) {
            SetPos(titleX, titleY + 3);
            printf("账号不存在\n");
            SetPos(titleX, titleY + 4);
            system("pause");
            return 0;  //登陆失败
        }
        size = 0;
        SetPos(titleX+6, titleY + 2);
        char pwd[50];
        memset(pwd,0,sizeof(pwd));
        while (1) {//输入密码  回显密文
            c = getch();
            if(c == '\b') {
                if(size > 0) {
                    putch('\b');
                    putch(' ');
                    putch('\b');
                    size--;
                    continue;
                }else{
                    continue;
                }
            }
            if (size == 12||c == '\r')
                break;
            putch('*');
            pwd[size++] = c;
        }
        pwd[size] = '\0';
        isCorrect =  CheckAccPwd(acc,pwd,A_Head);
        if(isCorrect == 0) {
            SetPos(titleX, titleY + 3);
            printf("账号或密码错误\n");
            Sleep(500);
            inCorrect++;
        }
        if(inCorrect == 5) {
            SetPos(titleX, titleY + 3);
            printf("您已经5次输错密码，可能忘记密码\n");
            SetPos(titleX, titleY + 4);
            system("pause");
            return NULL;//登陆失败
        }
    }
    SetPos(titleX, titleY + 3);
    printf("登陆成功\n");
    Sleep(1000);
    return FindAdmin(acc,A_Head);//登陆成功
}
//检查账号是否存在
int  CheckAcc(char *acc, Admin *A_Head){
    Admin *cur = A_Head->next;
    while(cur != NULL){
        if(strcmp(acc,cur->admin_id) == 0){
            return 1; //存在
        }
        cur = cur->next;
    }
    return 0; //不存在
}
//检查账号密码是否匹配
int  CheckAccPwd(char *acc, char *pwd,Admin *A_Head){
    Admin *cur = A_Head->next;
    while(cur != NULL){
        if(strcmp(acc,cur->admin_id) == 0){
            if(strcmp(pwd,cur->pwd) == 0)
              return 1; //匹配
            else
                return 0;
        }
        cur = cur->next;
    }
}
//返回登陆管理员指针
Admin* FindAdmin(char *acc, Admin *A_Head){
    Admin *cur = A_Head->next;
    while(cur != NULL){
        if(strcmp(acc,cur->admin_id) == 0){
            return cur; //存在
        }
        cur = cur->next;
    }
}
//用户注册
void Register(Admin *A_Head){
    int choice = 1;
    Admin *p = (Admin *) malloc(sizeof(Admin));
    while (1) {
        system("cls");
        SetPos(titleX, titleY);
        printf("  注 册");
        system("cls");
        SetPos(titleX, titleY + 1);
        printf("姓  名:\t");
        SetPos(titleX, titleY + 2);
        printf("工  号:\t");
        SetPos(titleX, titleY + 3);
        printf("手机号:\t");
        SetPos(titleX, titleY + 4);
        printf("密码:\t");
        SetPos(titleX, titleY + 5);
        printf("确认密码:\t");
        SetPos(titleX, titleY + 6);
        printf("密保问题:\t");
        SetPos(titleX, titleY + 7);
        printf("答案:\t");
        SetPos(titleX, titleY + 8);
        printf("(工号作为登陆账号)");
        char temp[50];
        while (1) {
            memset(temp, 0, sizeof(temp));
            SetPos(titleX + 9, titleY + 1);
            s_get(temp,50);
            if (strlen(temp) >= name_size) {      //判断名字是否输入过长
                SetPos(titleX + 9, titleY + 1);
                int i;
                for (i = 0; i < strlen(temp); i++)
                    printf("   ");
                SetPos(titleX + 9, titleY + 1);
                printf("非法:\t名字输入过长，请重新输入");
                Sleep(1000);
                SetPos(titleX + 9, titleY + 1);
                printf("                                 ");
            } else {
                strcpy(p->name, temp);
                break;
            }
        }
        while (1) {
            memset(temp, 0, sizeof(temp));
            SetPos(titleX + 9, titleY + 2);
            s_get(temp,50);
            if (strlen(temp) >= name_size) {      //判断工号是否输入过长
                SetPos(titleX + 9, titleY + 2);
                int i;
                for (i = 0; i < strlen(temp); i++)
                    printf("   ");
                SetPos(titleX + 9, titleY + 2);
                printf("非法:\t工号输入过长，请重新输入");
                Sleep(1000);
                SetPos(titleX + 9, titleY + 2);
                printf("                                     ");
            } else {
                int isHave = CheckAcc(temp,A_Head);//检查是否存在账号
                if(isHave == 1){
                    SetPos(titleX + 9, titleY + 2);
                    int i;
                    for (i = 0; i < strlen(temp); i++)
                        printf("   ");
                    SetPos(titleX + 9, titleY + 2);
                    printf("账号已存在，无需注册 ");
                    system("pause");
                    return ;
                }
                strcpy(p->admin_id, temp);
                break;
            }
        }
        while (1) {
            memset(temp, 0, sizeof(temp));
            SetPos(titleX + 9, titleY + 3);
            s_get(temp,50);
            if (strlen(temp) != 11) {      //判断手机号位数是否正确
                SetPos(titleX + 9, titleY + 3);
                int i;
                for (i = 0; i < strlen(temp); i++)
                    printf("   ");
                SetPos(titleX + 9, titleY + 3);
                printf("非法:\t手机号输入非法，请重新输入");
                Sleep(1000);
                SetPos(titleX + 9, titleY + 3);
                printf("                                          ");
            } else {
                int i = 0;
                for (i = 0; i < 11; i++) {
                    if (!isdigit(temp[i]))
                        break;
                }
                if (i == 11) {
                    strcpy(p->phone, temp);
                    break;
                }
                SetPos(titleX + 9, titleY + 3);
                printf("手机号含有非数字,请重新输入");
                Sleep(1000);
                SetPos(titleX + 9, titleY + 3);
                printf("                                   ");
            }
        }
        char pwd1[50], pwd2[50];
        int isSame = 1;
        while (isSame != 0) {
            while (1) {
                memset(pwd1, 0, sizeof(pwd1));
                SetPos(titleX + 9, titleY + 4);
                s_get(pwd1,50);
                if (strlen(pwd1) < 6 || strlen(pwd1) > 12) {  //判断密码长度是否合法
                    SetPos(titleX + 9, titleY + 4);
                    int i;
                    for (i = 0; i < strlen(pwd1); i++)
                        printf("   ");
                    SetPos(titleX + 9, titleY + 4);
                    printf("密码长度应为6-12个字符,请重新输入");
                    Sleep(1000);
                    SetPos(titleX + 9, titleY + 4);
                    printf("                                            ");
                } else {
                    break;
                }
            }
            while (1) {
                memset(pwd2, 0, sizeof(pwd2));
                SetPos(titleX + 9, titleY + 5);
                s_get(pwd2,50);
                isSame = strcmp(pwd1, pwd2);
                if (isSame != 0) {
                    SetPos(titleX + 9, titleY + 5);
                    int i;
                    for (i = 0; i < strlen(pwd1); i++)
                        printf("   ");
                    SetPos(titleX + 9, titleY + 5);
                    printf("两次输入密码不一致，请重新输入");
                    Sleep(1000);
                    SetPos(titleX + 9, titleY + 5);
                    printf("                                         ");
                    SetPos(titleX + 9, titleY + 4);
                    printf("                                        ");
                    break;
                } else {
                    break;
                }
            }
        }
        strcpy(p->pwd, pwd1);
        while (1) {
            memset(temp, 0, sizeof(temp));
            SetPos(titleX + 9, titleY + 6);
            s_get(temp,50);
            if (strlen(temp) >= name_size) {      //判断密保问题是否输入过长
                SetPos(titleX + 9, titleY + 6);
                int i;
                for (i = 0; i < strlen(temp); i++)
                    printf("   ");
                SetPos(titleX + 9, titleY + 6);
                printf("非法:\t密保问题输入过长，请重新输入");
                Sleep(1000);
                SetPos(titleX + 9, titleY + 6);
                printf("                                              ");
            } else {
                strcpy(p->qu, temp);
                break;
            }
        }
        while (1) {
            memset(temp, 0, sizeof(temp));
            SetPos(titleX + 9, titleY + 7);
            s_get(temp,50);
            if (strlen(temp) >= name_size) {      //判断答案是否输入过长
                SetPos(titleX + 9, titleY + 7);
                int i;
                for (i = 0; i < strlen(temp); i++)
                    printf("   ");
                SetPos(titleX + 9, titleY + 7);
                printf("非法:\t答案输入过长，请重新输入");
                Sleep(1000);
                SetPos(titleX + 9, titleY + 7);
                printf("                                      ");
            } else {
                strcpy(p->ans, temp);
                break;
            }
        }
        OutPutInfo(p);
        //while (1) {
            SetPos(titleX, titleY + 8);
            printf("1 信息无误确认注册");
            SetPos(titleX, titleY + 9);
            printf("0 信息有误");
            while(1) {
                SetPos(titleX, titleY + 10);
                printf("请输入您的选择:\t");
                choice = GetChoice();
                if (choice == 1||choice == 0)
                    break;
                SetPos(titleX, titleY + 10);
                printf("                                     ");
            }
            if(choice == 1){
                break;
            }else {
                system("cls");
                SetPos(titleX, titleY + 1);
                printf("1 重新注册");
                SetPos(titleX, titleY + 2);
                printf("0 退出");
                while(1) {
                    SetPos(titleX, titleY + 3);
                    printf("请输入您的选择:\t");
                    choice = GetChoice();
                    if (choice == 1||choice == 0)
                        break;
                    SetPos(titleX, titleY + 3);
                    printf("                                     ");
                }
            }
            if(choice == 1){
                continue;
            }
            if (choice == 0) {
                free(p);
                return;
            }
        //}
    }
    Admin *cur = A_Head;
    while(cur->next != NULL){
        cur = cur->next;
    }
    cur->next = p;
    p->next = NULL;
    WriteAdmin(A_Head);
    system("cls");
    SetPos(titleX, titleY + 1);
    printf("注册成功！");
    Sleep(1000);
}
//忘记密码
void ForgetPwd(Admin *A_Head){
    int isExist = 0;       //账号是否存在
    int isCorrect = 0;     //答案是否正确
    char acc[50];
    while(!isCorrect) {
        memset(acc,0,sizeof(acc));
        system("cls");
        SetPos(titleX,titleY);
        printf("忘 记 密 码");
        SetPos(titleX, titleY + 1);
        printf("账号:\t");
        char c;
        int size = 0;
        while ((c = getchar()) != '\n') {
            acc[size++] = c;
            if (size == name_size - 1)
                break;
        }
        acc[size] = '\0';
        isExist = CheckAcc(acc,A_Head);
        SetPos(titleX, titleY + 2);
        if(isExist == 0) {
            printf("账号不存在\n");
            SetPos(titleX, titleY + 3);
            system("pause");
            return;
        }
        OutPutQu(acc,A_Head);
        SetPos(titleX, titleY + 3);
        printf("答    案:");
        char ans[50];
        memset(ans,0,sizeof(ans));
        size = 0;
        while ((c = getchar()) != '\n') {
            ans[size++] = c;
            if (size == name_size - 1)
                break;
        }
        ans[size] = '\0';
        isCorrect = CheckQuAns(acc,ans,A_Head);
        if(isCorrect){
            SetPos(titleX, titleY + 4);
            printf("密    码:\t");
            SetPos(titleX, titleY + 5);
            printf("确认密码:\t");
            char pwd1[50], pwd2[50];
            int isSame = 1;
            while (isSame != 0) {
                while (1) {
                    memset(pwd1, 0, sizeof(pwd1));
                    SetPos(titleX + 9, titleY + 4);
                    s_get(pwd1,50);
                    if (strlen(pwd1) < 6 || strlen(pwd1) > 12) {  //判断密码长度是否合法
                        SetPos(titleX + 9, titleY + 4);
                        int i;
                        for (i = 0; i < strlen(pwd1); i++)
                            printf("   ");
                        SetPos(titleX + 9, titleY + 4);
                        printf("密码长度应为6-12个字符,请重新输入");
                        Sleep(1000);
                        SetPos(titleX + 9, titleY + 4);
                        printf("                                            ");
                    } else {
                        break;
                    }
                }
                while (1) {
                    memset(pwd2, 0, sizeof(pwd2));
                    SetPos(titleX + 9, titleY + 5);
                    s_get(pwd2,50);
                    isSame = strcmp(pwd1, pwd2);
                    if (isSame != 0) {
                        SetPos(titleX + 9, titleY + 5);
                        int i;
                        for (i = 0; i < strlen(pwd1); i++)
                            printf("   ");
                        SetPos(titleX + 9, titleY + 5);
                        printf("两次输入密码不一致，请重新输入");
                        Sleep(1000);
                        SetPos(titleX + 9, titleY + 5);
                        printf("                                         ");
                        SetPos(titleX + 9, titleY + 4);
                        printf("                                        ");
                        break;
                    } else {
                        break;
                    }
                }
            }
            Admin *cur = A_Head->next;
            while(cur != NULL){
                if(strcmp(acc,cur->admin_id) == 0){
                    memset(cur->pwd,0, sizeof(cur->pwd));
                    strcpy(cur->pwd,pwd1);
                    break;
                }
                cur = cur->next;
            }
        }else{
            SetPos(titleX, titleY + 4);
            printf("答案错误");
            SetPos(titleX, titleY + 5);
            system("pause");
        }
    }
    WriteAdmin(A_Head);
}
//输出密保问题
void OutPutQu(char *acc,Admin *A_Head){
    SetPos(titleX, titleY + 2);
    printf("密保问题:");
    Admin *cur = A_Head->next;
    while(cur != NULL){
        if(strcmp(acc,cur->admin_id) == 0){
            printf("%s",cur->qu);
            return;
        }
        cur = cur->next;
    }
}
//检查密保问题和答案是否匹配
int  CheckQuAns(char *acc,char *ans,Admin *A_Head){
    Admin *cur = A_Head->next;
    while(cur != NULL){
        if(strcmp(acc,cur->admin_id) == 0){
            if(strcmp(ans,cur->ans) == 0)
                return 1;//匹配
        }
        cur = cur->next;
    }
    return 0;//不匹配
}
//修改密码
void ChangePwd(Admin *A_Head) {
    int isExist = 0;       //账号是否存在
    int isCorrect = 0;     //密码是否正确
    int inCorrect = 0;     //密码不正确次数
    char acc[50];
    while (!isCorrect) {
        system("cls");
        SetPos(titleX, titleY);
        printf("修 改 密 码");
        SetPos(titleX, titleY + 1);
        printf("账号:\t");
        SetPos(titleX, titleY + 2);
        printf("密码:\t");

        memset(acc, 0, sizeof(acc));
        int size = 0;
        char c;
        SetPos(titleX + 6, titleY + 1);
        while ((c = getchar()) != '\n') {
            acc[size++] = c;
            if (size == name_size - 1)
                break;
        }
        acc[size] = '\0';
        isExist = CheckAcc(acc, A_Head);
        if (isExist == 0) {
            SetPos(titleX, titleY + 3);
            printf("账号不存在...\n");
            SetPos(titleX, titleY + 4);
            system("pause");
            return;  //登陆失败
        }
        size = 0;
        SetPos(titleX + 6, titleY + 2);
        char pwd[50];
        memset(pwd, 0, sizeof(pwd));
        while ((c = getchar()) != '\n') {
            pwd[size++] = c;
            if (size == 11)
                break;
        }
        pwd[size] = '\0';
        isCorrect = CheckAccPwd(acc, pwd, A_Head);
        if (isCorrect == 0) {
            SetPos(titleX, titleY + 3);
            printf("账号或密码错误\n");
            Sleep(500);
            inCorrect++;
        }
        if (inCorrect == 5) {
            SetPos(titleX, titleY + 3);
            printf("您已经5次输错密码，可能忘记密码\n");
            SetPos(titleX, titleY + 4);
            system("pause");
            return;//登陆失败
        }
    }
    SetPos(titleX, titleY + 4);
    printf("新 密 码:\t");
    SetPos(titleX, titleY + 5);
    printf("确认密码:\t");
    char pwd1[50], pwd2[50];
    int isSame = 1;
    while (isSame != 0) {
        while (1) {
            memset(pwd1, 0, sizeof(pwd1));
            SetPos(titleX + 9, titleY + 4);
            s_get(pwd1,50);
            if (strlen(pwd1) < 6 || strlen(pwd1) > 12) {  //判断密码长度是否合法
                SetPos(titleX + 9, titleY + 4);
                int i;
                for (i = 0; i < strlen(pwd1); i++)
                    printf("   ");
                SetPos(titleX + 9, titleY + 4);
                printf("密码长度应为6-12个字符,请重新输入");
                Sleep(1000);
                SetPos(titleX + 9, titleY + 4);
                printf("                                            ");
            } else {
                break;
            }
        }
        while (1) {
            memset(pwd2, 0, sizeof(pwd2));
            SetPos(titleX + 9, titleY + 5);
            s_get(pwd2,50);
            isSame = strcmp(pwd1, pwd2);
            if (isSame != 0) {
                SetPos(titleX + 9, titleY + 5);
                int i;
                for (i = 0; i < strlen(pwd1); i++)
                    printf("   ");
                SetPos(titleX + 9, titleY + 5);
                printf("两次输入密码不一致，请重新输入");
                Sleep(1000);
                SetPos(titleX + 9, titleY + 5);
                printf("                                         ");
                SetPos(titleX + 9, titleY + 4);
                printf("                                        ");
                break;
            } else {
                break;
            }
        }
    }
    Admin *cur = A_Head->next;
    while (cur != NULL) {
        if (strcmp(acc, cur->admin_id) == 0) {
            memset(cur->pwd, 0, sizeof(cur->pwd));
            strcpy(cur->pwd, pwd1);
            break;
        }
        cur = cur->next;
    }
    SetPos(titleX, titleY + 6);
    WriteAdmin(A_Head);
    printf("修改密码成功！");
    Sleep(1000);
}
//输出用户输入信息
void OutPutInfo(Admin *node){
    system("cls");
    SetPos(titleX,titleY+1);
    printf("姓    名:");
    printf("%s\n",node->name);
    SetPos(titleX,titleY+2);
    printf("工    号:");
    printf("%s\n",node->admin_id);
    SetPos(titleX,titleY+3);
    printf("手 机 号:");
    printf("%s\n",node->phone);
    SetPos(titleX,titleY+4);
    printf("密    码:");
    printf("%s\n",node->pwd);
    SetPos(titleX,titleY+5);
    printf("密保问题:");
    printf("%s\n",node->qu);
    SetPos(titleX,titleY+6);
    printf("答    案:");
    printf("%s\n",node->ans);
}

void FreeAdminNode(Admin *A_Head){
    Admin *cur = A_Head->next;
    Admin *temp = cur;
    while(cur!=NULL) {
        temp = cur;
        cur = cur->next;
        free(temp);
    }
    free(A_Head);
    A_Head = NULL;
}
