/*
*********************************************************************************************************
by zx 2019/12/1
This file is used for contain all the priorities and stack sizes of the tasks that are created by users.
*********************************************************************************************************
*/

#ifndef APP_CFG_H
#define APP_CFG_H

#include "cpu.h"

#define APP_CFG_TASK_START_PRIO 2u                  //start task priority
#define OS_TASK_TMR_PRIO (OS_LOWEST_PRIO - 2u)      //OS Timer task priority
#define APP_CFG_TASK_START_STK_SIZE 256u            //start task stack size
#define OS_CPU_EXCEPT_STK_SIZE 512u                 //exception stack size

#endif
