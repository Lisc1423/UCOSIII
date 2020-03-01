#include "cmd_func.h"
#include "can_utils.h"
#include "SICK_DT35.h"
void cmd_start_uprint(int argc, char *argv[]);

void cmd_func_init(void) {
    cmd_add("hello", "just", cmd_hello_func);
    cmd_add("set_voltage","detail please check .c",cmd_SICK_setVolage);
    cmd_add("set_distance","detail please check .c",cmd_SICK_setDistance);
    cmd_add("set_Param","detail please check .c",cmd_SICK_setPARA);
    cmd_add("start_uprint","",cmd_start_uprint);
    cmd_add("culculate_kb","",cmd_SICK_culculate);
    cmd_add("distance_1time","",cmd_print_distance_one_time);
    cmd_add("can_sending","",cmd_start_can_sending);
    #ifdef DEBUG
    cmd_add("can_test", "test can", cmd_can_test);
    #endif
}

void cmd_hello_func(int argc, char *argv[]) {
    uprintf("hello world\r\n");
}

void cmd_can_test(int argc, char *argv[]) {
    uprintf("can send test\r\n");
    can_send_test();
}

void cmd_start_uprint(int argc, char *argv[]){
    main_flag.print_flag = atoi(argv[1]);
    uprintf("print_flag is %d\r\n",main_flag.print_flag);
}

void cmd_start_can_sending(int argc, char *argv[]){
    main_flag.can_send_flag = atoi(argv[1]);
    uprintf("can_start_sending! now\r\n");
}


