#ifndef __PID_CTROL_H__
#define __PID_CTROL_H__
#include <stdio.h>
#include "APP.h"


void PidStructInit1(void);
void PidStructInit2(void);
void PidStructInit3(void);
void PidStructInit4(void);
void GetPidOutputValue(float curvalue,float setpoint,PidValueStruct *pidstruct);



#endif