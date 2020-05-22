//
// Created by SGNY on 2020/5/8.
//
//管理员登陆界面
#ifndef SUPER_V1_ADMIN_H
#define SUPER_V1_ADMIN_H

#include "structandfx.h"
Admin* AdminMain(Admin *A_Head);
void AdminMenu();
//账号登陆
Admin* SignIn(Admin *A_Head);
int  CheckAcc(char *acc, Admin *A_Head);//检查账号是否存在
int  CheckAccPwd(char *acc, char *pwd, Admin *A_Head);//检查账号密码是否匹配
Admin* FindAdmin(char *acc, Admin *A_Head);//返回当前操作人员
//用户注册
void Register(Admin *A_Head);
void OutPutInfo(Admin *node);//输出用户输入信息

//忘记密码
void ForgetPwd(Admin *A_Head);
void OutPutQu(char *acc,Admin *A_Head);
int  CheckQuAns(char *acc,char *ans,Admin *A_Head);//检查密保问题和答案是否匹配

//修改密码
void ChangePwd(Admin *A_Head);

//释放内存空间
void FreeAdminNode(Admin *A_Head);
#endif //SUPER_V1_ADMIN_H
