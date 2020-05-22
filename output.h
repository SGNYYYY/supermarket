
#ifndef OUTPUT_H_INCLUDED
#define OUTPUT_H_INCLUDED

#include "structandfx.h"
void OutPutMain(out_Goods* outGoods_Head, in_Goods *inGoods_Head, Goods* G_Head, Admin *administer, VIP *V_Head);
void Search_This_1(in_Goods *inGoods_Head, int a,int b[]);
void OutPutMenu();
int Sale(out_Goods* outGoods_Head, in_Goods *inGoods_Head, Goods* G_Head, Admin *administer, VIP *V_Head);
int Return(out_Goods* outGoods_Head, in_Goods *inGoods_Head, Goods* G_Head, Admin *administer);


#endif // OUTPUT_H_INCLUDED
