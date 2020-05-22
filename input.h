
#ifndef INPUT_H_INCLUDED
#define INPUT_H_INCLUDED

#include "structandfx.h"
void InputMain(Admin *administer, Goods *G_Head, in_Goods* inGoods_Head);
void Search_This(in_Goods *inGoods_Head, int a,int b[]);
int New_kind_of_good(Goods* G_Head);
void Inputmenu();
int New_shipment(Admin* administer, Goods* G_Head, in_Goods* inGoods_Head);
#endif // INPUT_H_INCLUDED
