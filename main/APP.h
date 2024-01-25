#ifndef __GORAL_VALUE_H__
#define __GORAL_VALUE_H__
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