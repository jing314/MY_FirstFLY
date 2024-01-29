#include "mpu6050.h"
#define I2C_MASTER_NUM      I2C_NUM_0
#define I2C_MASTER_SDA_IO   MYFLY_IICSDA_IONUM
#define I2C_MASTER_SCL_IO   MYFLY_IICSCL_IONUM
#define I2C_MASTER_FREQ_HZ      1000
#define I2C_MASTER_RX_BUF_DISABLE   0   //从机接受缓冲区大小，主机不需要
#define I2C_MASTER_TX_BUF_DISABLE   0   //从机发送缓冲区大小，主机不需要


esp_err_t i2c_master_init(void)
{
    int i2c_master_port = I2C_MASTER_NUM;

    i2c_config_t conf = {
        .mode = I2C_MODE_MASTER,            //工作模式，主机模式
        .sda_io_num = I2C_MASTER_SDA_IO,    //SDA引脚号
        .scl_io_num = I2C_MASTER_SCL_IO,    //SCL引脚号
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .master.clk_speed = I2C_MASTER_FREQ_HZ,//SCL时钟频率
    };

    i2c_param_config(i2c_master_port, &conf);

    return i2c_driver_install(i2c_master_port, conf.mode, I2C_MASTER_RX_BUF_DISABLE, I2C_MASTER_TX_BUF_DISABLE, 0);
}

void mpu6050_reg_read(uint8_t reg,uint8_t *data){
    esp_err_t err;
    i2c_cmd_handle_t read_cmd = i2c_cmd_link_create();
    i2c_master_start(read_cmd);//开始标识
    err = i2c_master_write_byte(read_cmd,(MPU6050_IICADDR << 1)|I2C_MASTER_WRITE,true);//确定地址
    if(err != ESP_OK){
        return 1;
    }
    err = i2c_master_write_byte(read_cmd,reg,true);
    if(err != ESP_OK){
        return 1;
    }
    i2c_master_start(read_cmd);//开始标识
    err = i2c_master_write_byte(read_cmd,(MPU6050_IICADDR << 1)|I2C_MASTER_READ,true);//确定地址
    if(err != ESP_OK){
        return 1;
    }
    err = i2c_master_read_byte(read_cmd,data,I2C_MASTER_LAST_NACK);
    if(err != ESP_OK){
        return 1;
    }
    i2c_master_stop(read_cmd);//结束标识
    i2c_master_cmd_begin(I2C_NUM_0,read_cmd,10/portTICK_PERIOD_MS);
    i2c_cmd_link_delete(read_cmd);
    return 0;
}

uint8_t mpu6050_reg_write(uint8_t reg,uint8_t data)
{
    esp_err_t err;
    i2c_cmd_handle_t write_cmd;
    i2c_master_start(write_cmd);//开始标识
    err = i2c_master_write_byte(write_cmd,(MPU6050_IICADDR << 1)|I2C_MASTER_WRITE,true);//确定地址
    if(err != ESP_OK){
        return 1;
    }
    err = i2c_master_write_byte(write_cmd,reg,true);
    if(err != ESP_OK){
        return 1;
    }
    err = i2c_master_write_byte(write_cmd,data,true);
    if(err != ESP_OK){
        return 1;
    }    
    i2c_master_stop(write_cmd);//结束标识
    i2c_master_cmd_begin(I2C_NUM_0,write_cmd,10/portTICK_PERIOD_MS);
    i2c_cmd_link_delete(write_cmd);
    return 0;
}

void mpu6050_init(void)
{
    i2c_master_init();
    mpu6050_reg_write(MPU6050_PWP_MGMT_1,0x01);
    mpu6050_reg_write(MPU6050_PWP_MGMT_2,0x00);
    mpu6050_reg_write(MPU6050_SMPLRT_DIV,0x09);
    mpu6050_reg_write(MPU6050_CONFIG,0x06);
    mpu6050_reg_write(MPU6050_GYR_CONFIG,0x18);
    mpu6050_reg_write(MPU6050_ACC_CONFIG,0x18);
}