cmake_minimum_required(VERSION 3.15)
project(super_v1 C)

set(CMAKE_C_STANDARD 99)

add_executable(super_v1 main.c structandfx.h fx.c admin.h admin.c StockTaking.c StockTaking.h DailySum.c DailySum.h VIP.c VIP.h
        ChangeGoodsInfo.c ChangeGoodsInfo.h FindGoods.h FindGoods.c SoldOut.h SoldOut.c
        input.c input.h output.c output.h setdiscount.c setdiscount.h BackupRestore.c BackupRestore.h)