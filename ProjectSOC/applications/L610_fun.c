/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-05-01     dongy       the first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>

#define L610_RST GET_PIN(C, 13)

int L610_Init(){

    rt_pin_mode(L610_RST, PIN_MODE_OUTPUT);

    // L610_Reset
    rt_pin_write(L610_RST, PIN_LOW);
    rt_thread_mdelay(500);
    rt_pin_write(L610_RST, PIN_HIGH);

    // Init
    do{

    }while(0);

    // 上报初始化数据
    return 0;
}


