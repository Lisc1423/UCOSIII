#ifndef __karman_H
#define __karman_H

typedef struct _kal_struct{
	float A;   //һ��Ϊ1
	float B;   //һ��Ϊ0
	float Q;//ϵͳ����������Э����
	float R;//����������Э����
	
	float kal_out; //��һ�ο����������
	
	float cov; //��һ�ο������������Э����
	
}Kal_Struct;
extern Kal_Struct kal_ang1;
float KalMan(Kal_Struct *kal,float x);

#endif