#include "karman.h"


/*
	卡尔曼滤波函数
*/
Kal_Struct kal_ang1={1,0,0.01,37.1160,0,1};
Kal_Struct kal_ang2={1,0,0.01,37.1160,0,1};
Kal_Struct kal_ang3={1,0,0.01,37.1160,0,1};
Kal_Struct kal_ang4={1,0,0.01,37.1160,0,1};
Kal_Struct kal_ang5={1,0,0.01,37.1160,0,1};
Kal_Struct kal_ang6={1,0,0.01,37.1160,0,1};

float KalMan(Kal_Struct *kal,float x){
	
	float kalman_pre;  //卡尔曼的预测值
	float cov_pre;  //卡尔曼预测值的协方差

	
	float kg;//增益
	kalman_pre=kal->kal_out*kal->A;  //计算本次卡尔曼的预测值
	
	cov_pre=kal->cov*kal->A*kal->A+kal->Q;
	
	kg=cov_pre/(cov_pre+kal->R);   //计算本次的卡尔曼增益
	
	kal->kal_out=kalman_pre+kg*(x-kalman_pre);   //通过预测值来计算本次卡尔曼滤波后的输出
	
	kal->cov=(1-kg)*cov_pre;
	
	return kal->kal_out;
}


 