#include "karman.h"


/*
	�������˲�����
*/
Kal_Struct kal_ang1={1,0,0.01,37.1160,0,1};
Kal_Struct kal_ang2={1,0,0.01,37.1160,0,1};
Kal_Struct kal_ang3={1,0,0.01,37.1160,0,1};
Kal_Struct kal_ang4={1,0,0.01,37.1160,0,1};
Kal_Struct kal_ang5={1,0,0.01,37.1160,0,1};
Kal_Struct kal_ang6={1,0,0.01,37.1160,0,1};

float KalMan(Kal_Struct *kal,float x){
	
	float kalman_pre;  //��������Ԥ��ֵ
	float cov_pre;  //������Ԥ��ֵ��Э����

	
	float kg;//����
	kalman_pre=kal->kal_out*kal->A;  //���㱾�ο�������Ԥ��ֵ
	
	cov_pre=kal->cov*kal->A*kal->A+kal->Q;
	
	kg=cov_pre/(cov_pre+kal->R);   //���㱾�εĿ���������
	
	kal->kal_out=kalman_pre+kg*(x-kalman_pre);   //ͨ��Ԥ��ֵ�����㱾�ο������˲�������
	
	kal->cov=(1-kg)*cov_pre;
	
	return kal->kal_out;
}


 