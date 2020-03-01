#include "SICK_DT35.h"                                                           
//#define TEST_MODE


SICK_DT35 sensor1;
static void culculate_k_b_params(SICK_DT35 *sensor);
void read_parameter_from_flash(SICK_DT35 *sensor);

/**sick_dt35_init 初始化 包括设置参与与开启ADC（连续模式）
*参数：void
*返回值： void
*说明: 放在main函数之前使用，之后增加更多sick传感器是需要在代码中加入新的部分
*作者: zx
*/
void sick_dt35_init(){
  #ifdef TEST_MODE
  sensor1.FAR_DISTANCE = 3;
  sensor1.FAR_voltage = 4096;
  sensor1.NEAR_DISTANCE = 0.01;
  sensor1.NEAR_voltage = 0;
  #endif
  #ifndef TEST_MODE
  read_parameter_from_flash(&sensor1);
  #endif
  sensor1.can_id = SENSOR1_ID;
  sensor1.name = "sensor1";
  sensor1.ADC_port = hadc2;
  sensor1.channel = ADC_CHANNEL_4;
  culculate_k_b_params(&sensor1);
  if(HAL_ADC_Start_DMA(&hadc2, sensor1.ADC_value ,AVERAGE_AMOUNT) != HAL_OK) while(1);;
}
/**culculate_distance 计算对应传感器的距离
*参数：输入对应的传感器结构体
*返回值： float 为计算出的实际距离 单位 米
*说明: 放在main函数之中使用即可
*作者: zx
*/
float culculate_distance(SICK_DT35 *sensor){
  float sum_up = 0;
  float distance;
  for(int i=0; i < AVERAGE_AMOUNT ; i++){
    sum_up += sensor->ADC_value[i];
  }
  distance = sum_up * sensor->k_param /AVERAGE_AMOUNT + sensor->b_param;
  distance = KalMan(&kal_ang1 , distance);
  sensor1.distance = distance;
  sensor->sick_can_msg.fl[0] = distance;
  sensor->sick_can_msg.fl[1] = 0;  
  return distance; 
}

/**culculate_k_b_params 内部函数，计算对应传感器的距离曲线
*参数：输入对应的传感器结构体
*返回值： void
*说明: 内部函数
*作者: zx
*/
static void culculate_k_b_params(SICK_DT35 *sensor){
  sensor1.k_param = (sensor1.FAR_DISTANCE - sensor1.NEAR_DISTANCE) / (sensor1.FAR_voltage - sensor1.NEAR_voltage);
  sensor1.b_param = sensor1.FAR_DISTANCE - sensor1.k_param*sensor1.FAR_voltage;
  uprintf("k is %f and d is %f\r\n", sensor1.k_param, sensor1.b_param);
}

/**set_parameter_to_flash 向flash中写入数据
*参数：输入对应的传感器结构体
*返回值： void
*说明: none
*作者: zx
*/
void set_parameter_to_flash(SICK_DT35 *sensor){
  flash_data[0] = sensor->FAR_DISTANCE;
  flash_data[1] = sensor->FAR_voltage;
  flash_data[2] = sensor->NEAR_DISTANCE;
  flash_data[3] = sensor->NEAR_voltage;
  write_prams();
  uprintf("write param to flash finished!\r\n");
}

/**read_parameter_from_flash 从flash中载入数据
*参数：输入对应的传感器结构体
*返回值： void
*说明: none
*作者: zx
*/
void read_parameter_from_flash(SICK_DT35 *sensor){
  load_prams();
  sensor->FAR_DISTANCE = flash_data[0];
  sensor->FAR_voltage = flash_data[1];
  sensor->NEAR_DISTANCE = flash_data[2];
  sensor->NEAR_voltage = flash_data[3];
  uprintf("read param form flash finished!\r\n");
}

/** cmd_SICK_setVolage 在cmd_fun.c使用
*参数：cmd执行函数标准参数
* 第一个参数为 int；等于0时设置FAR voltage；等于1时设置NEAR voltage （voltage就是adc读入的数据0-4095）
*返回值： void
*说明: none
*作者: zx
*/
void cmd_SICK_setVolage(int argc, char *argv[]) {
    int number = atoi(argv[1]);
    int sum_up = 0;
    
    if(number == 0){
      for(int i=0; i < AVERAGE_AMOUNT ; i++){
        sum_up += sensor1.ADC_value[i];
      }
      sensor1.FAR_voltage = (float)sum_up / AVERAGE_AMOUNT;
      uprintf("FAR_voltage is %f\r\n",sensor1.FAR_voltage);
    }

    if(number == 1){
      for(int i=0; i < AVERAGE_AMOUNT ; i++){
        sum_up += sensor1.ADC_value[i];
      }
      sensor1.NEAR_voltage = sum_up / AVERAGE_AMOUNT;
      uprintf("NEAR_voltage is %f\r\n",sensor1.NEAR_voltage);
    }
}

/**cmd_SICK_setDistance 在cmd_fun.c使用
*参数：cmd执行函数标准参数
* 第一个参数为 int；等于0时设置FAR distance；等于1时设置NEAR ditance 
* 第二个参数为对应的distance的数值 单位 米
*返回值： void
*说明: near的distance不要少于10cm
*作者: zx
*/
void cmd_SICK_setDistance(int argc, char *argv[]) {
    int number = atoi(argv[1]);
    float distance = atof(argv[2]);       //注 distance 单位m
    if(number == 0){
      sensor1.FAR_DISTANCE = distance;
      uprintf("FAR_DISTANCE is %f\r\n",sensor1.FAR_DISTANCE);
    }

    if(number == 1){
      sensor1.NEAR_DISTANCE = distance;
      uprintf("NEAR_DISTANCE is %f\r\n",sensor1.NEAR_DISTANCE);
    }
}

/**cmd_SICK_setPARA 在cmd_fun.c使用
*参数：cmd执行函数标准参数
* 第一个参数为 int；等于0时写入flash；等于1时从flash中读取 
*返回值： void
*说明: none
*作者: zx
*/
void cmd_SICK_setPARA(int argc, char *argv[]) {
  int number = atoi(argv[1]);
  if(number == 0){
    set_parameter_to_flash(&sensor1);
  }
  if(number == 1){
    read_parameter_from_flash(&sensor1);
  }
}

/**cmd_SICK_culculate 在cmd_fun.c使用
*参数：cmd执行函数标准参数
*返回值： void
*说明: 用cmd执行计算kd的函数
*作者: zx
*/
void cmd_SICK_culculate(int argc, char *argv[]){
  culculate_k_b_params(&sensor1);
  uprintf("finish culculate k and b\r\n");
}


/**cmd_SICK_culculate 在cmd_fun.c使用
*参数：cmd执行函数标准参数
*返回值： void
*说明: 单词打印距离
*作者: zx
*/
void cmd_print_distance_one_time(int argc, char *argv[]){
    uprintf("distance is %f\r\n",sensor1.distance);
}