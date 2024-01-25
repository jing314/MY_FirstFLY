#ifndef __GORAL_VALUE_H__
#define __GORAL_VALUE_H__
//宏定义区
#define MYFLY_PWM1_IONUM 47
#define MYFLY_PWM2_IONUM 33
#define MYFLY_PWM3_IONUM 34
#define MYFLY_PWM4_IONUM 48

#define MYFLY_IICSCL_IONUM 1
#define MYFLY_IICSDA_IONUM 2

#define MYFLY_LED1_IONUM 6
#define MYFLY_LED2_IONUM 5
#define MYFLY_LED3_IONUM 7


//结构体定义区
typedef struct
{
    float Kp ;//比例系数
    float Ki ;//积分系数
    float Kd ;//微分系数
    float setpoint ;  //目标值
    float error ;      //型误差值
    float last_error ; //旧误差值
    float intergral ;  //积分项
    float derivative ; //微分项
    float output ;     //输出值
}PidValueStruct;//PID结构体


//全局变量声明区

extern PidValueStruct pwm_out1pid;
extern PidValueStruct pwm_out2pid;
extern PidValueStruct pwm_out3pid;
extern PidValueStruct pwm_out4pid;


#endif