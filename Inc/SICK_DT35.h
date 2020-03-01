#ifndef __SICK_DT35_H
#define __SICK_DT35_H
#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"
#include "stmflash.h"
#include "adc.h"
#include "simplelib.h"
#include "karman.h"

#define AVERAGE_AMOUNT 10


#define SENSOR1_ID 35
typedef struct
{
  char* name;
  uint16_t can_id;
  uint32_t channel;
  ADC_HandleTypeDef ADC_port;
  uint32_t ADC_value[AVERAGE_AMOUNT];
  float distance;
  float FAR_DISTANCE;
  float NEAR_DISTANCE;
  float FAR_voltage;
  float NEAR_voltage;
  float k_param;
  float b_param;
  can_msg sick_can_msg;
}SICK_DT35;

void sick_dt35_init();


float culculate_distance(SICK_DT35 *sensor);
void cmd_SICK_setVolage(int argc, char *argv[]);
void cmd_SICK_setDistance(int argc, char *argv[]);
void cmd_SICK_setPARA(int argc, char *argv[]);
void cmd_SICK_culculate(int argc, char *argv[]);
void cmd_print_distance_one_time(int argc, char *argv[]);
extern SICK_DT35 sensor1;
#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
