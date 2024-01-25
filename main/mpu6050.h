#ifndef __MPU6050_READ_H__
#define __MPU6050_READ_H__
#include "APP.h"
#include "driver/i2c.h"
esp_err_t i2c_master_init(void);

/*
    IIC相关函数
*/
#define I2C_Init() i2c_master_init()

#define I2C_Write_Byte(byte)
#define I2C_Read_Byte()
#define I2C_Read_ACK()
#define I2C_Write_ACK()





#endif