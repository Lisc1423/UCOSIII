#ifndef __karman_H
#define __karman_H

typedef struct _kal_struct{
	float A;   //一般为1
	float B;   //一般为0
	float Q;//系统过程噪声的协方差
	float R;//测量噪声的协方差
	
	float kal_out; //上一次卡尔曼的输出
	
	float cov; //上一次卡尔曼的输出的协方差
	
}Kal_Struct;
extern Kal_Struct kal_ang1;
float KalMan(Kal_Struct *kal,float x);

#endif