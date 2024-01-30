#ifndef __MPU6050_READ_H__
#define __MPU6050_READ_H__
#include "APP.h"
#include "driver/i2c.h"
#define MPU6050_IICADDR 0x68
#define MPU6050_SMPLRT_DIV  0x19
#define MPU6050_CONFIG 0x1A
#define MPU6050_GYR_CONFIG 0x1B
#define MPU6050_ACC_CONFIG 0x1C
#define MPU6050_PWP_MGMT_1 0x6B
#define MPU6050_PWP_MGMT_2 0x6C

#define MPU6050_ACC_X   0x3B//加速度计的X轴分量ACC_X
#define MPU6050_ACC_Y    0x3D//加速度计的Y轴分量ACC_Y
#define MPU6050_ACC_Z   0x3F//加速度计的Z轴分量ACC_Z
#define MPU6050_TEMP    0x41//当前温度TEMP
#define MPU6050_GYR_X   0x43//绕X轴旋转的角速度GYR_X
#define MPU6050_GYR_Y   0x45//绕Y轴旋转的角速度GYR_Y
#define MPU6050_GYR_Z   0x47//绕Z轴旋转的角速度GYR_Z


uint8_t mpu6050_reg_read(uint8_t reg,uint8_t *data);
uint8_t mpu6050_reg_write(uint8_t reg,uint8_t data);
void mpu6050_init(void);

/*
    IIC相关函数
*/




#endif