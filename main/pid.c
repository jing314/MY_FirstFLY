
#include "pid.h"
PidValueStruct pwm_out1pid;
PidValueStruct pwm_out2pid;
PidValueStruct pwm_out3pid;
PidValueStruct pwm_out4pid;

void PidStructInit1(void){
    pwm_out1pid.Kp = 0.0;
    pwm_out1pid.Ki = 0.0;
    pwm_out1pid.Kd = 0.0;
}
void PidStructInit2(void){
    pwm_out2pid.Kp = 0.0;
    pwm_out2pid.Ki = 0.0;
    pwm_out2pid.Kd = 0.0;
}
void PidStructInit3(void){
    pwm_out3pid.Kp = 0.0;
    pwm_out3pid.Ki = 0.0;
    pwm_out3pid.Kd = 0.0;
}
void PidStructInit4(void){
    pwm_out4pid.Kp = 0.0;
    pwm_out4pid.Ki = 0.0;
    pwm_out4pid.Kd = 0.0;
}

void GetPidOutputValue(float curvalue,float setpoint,PidValueStruct *pidstruct){
    pidstruct->error = pidstruct->setpoint - curvalue;
    pidstruct->intergral += pidstruct->error;
    pidstruct->derivative = pidstruct->error-pidstruct->last_error;

    pidstruct->last_error = pidstruct->error;
    pidstruct->output = pidstruct->Kd * pidstruct->error +  \
                        pidstruct->Ki * pidstruct->intergral\
                        + pidstruct->Kd * pidstruct->derivative;
}