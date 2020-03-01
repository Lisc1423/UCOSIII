#include "task.h"

void Task_LED1(void *p_arg);

static OS_STK Task_LED1Stk[512];
void App_TaskCreate(){
	OSTaskCreateExt(Task_LED1,
	(void *)0,
	(OS_STK *)Task_LED1Stk[512-1],
	3,3,
	(OS_STK *)Task_LED1Stk[0],
	512,
	(void *)0,
	OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR
	);
}

void Task_LED1(void *p_arg){
	(void)*p_arg;
	while(1){
		HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_2);
		OSTimeDlyHMSM(0,0,2,0);
	}
}