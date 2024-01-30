/* WiFi station Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <string.h>
#include "wifi.h"
#include "mpu6050.h"
#include "pid.h"
#include "driver/ledc.h"
#include "driver/gpio.h"
#include "APP.h"
// #include "freertos/FreeRTOS.h"
// #include "freertos/task.h"
// #include "freertos/event_groups.h"
// #include "esp_system.h"
//#include "esp_wifi.h"
//#include "esp_event.h"
//#include "esp_log.h"
//#include "nvs_flash.h"
//#include "lwip/err.h"
//#include "lwip/sys.h"
//#include "esp_netif.h"
//#include "lwip/sockets.h"


/* The examples use WiFi configuration that you can set via project configuration menu

   If you'd rather not, just change the below entries to strings with
   the config you want - ie #define EXAMPLE_WIFI_SSID "mywifissid"
*/
static const char *TAG = "wifi station";

/*
配置结构体初始化
*/
ledc_timer_config_t ledc_timer;//定时器
ledc_channel_config_t ledc_channel;//通道


void pwm_init_time(void)//pwm初始化，
{
    /*
    pwm配置
    */
    ledc_timer.freq_hz = 5000;//PWM信号频率
    ledc_timer.duty_resolution = LEDC_TIMER_13_BIT;//占空比分辨率
    ledc_timer.speed_mode = LEDC_LOW_SPEED_MODE;// 定时器模式
    ledc_timer.timer_num = LEDC_TIMER_0;// 定时器序号;使用哪个定时器0-3;
    ledc_timer_config(&ledc_timer);
    /*
    输出引脚配置
    */
    ledc_channel.channel = LEDC_CHANNEL_1;// LED控制器通道号,
    ledc_channel.duty = 8191;               //占空比，最大值8192
	ledc_channel.gpio_num = MYFLY_PWM1_IONUM;				// LED控制器通道对应GPIO, 
	ledc_channel.speed_mode = LEDC_LOW_SPEED_MODE; // 模式, 
	ledc_channel.timer_sel = LEDC_TIMER_0;   		// 使用哪个定时器0-3
    ledc_channel_config(&ledc_channel);
    ledc_channel.gpio_num = MYFLY_PWM2_IONUM;				// LED控制器通道对应GPIO, 
    ledc_channel.channel = LEDC_CHANNEL_2;// LED控制器通道号,
    ledc_channel_config(&ledc_channel);
    ledc_channel.gpio_num = MYFLY_PWM3_IONUM;				// LED控制器通道对应GPIO, 
    ledc_channel.channel = LEDC_CHANNEL_3;// LED控制器通道号,
    ledc_channel_config(&ledc_channel);
    ledc_channel.gpio_num = MYFLY_PWM4_IONUM;				// LED控制器通道对应GPIO, 
    ledc_channel.channel = LEDC_CHANNEL_4;// LED控制器通道号,
    ledc_channel_config(&ledc_channel);

    //其他引脚的初始化只需要更改gpio_num与channel即可

}

void gpio_init_normal(void)//通用gpio初始化函数
{
    gpio_config_t gpio_init_struct;
    gpio_init_struct.pin_bit_mask = (1ull << MYFLY_LED1_IONUM)|(1ull << MYFLY_LED2_IONUM)|(1ull << MYFLY_LED3_IONUM),
    gpio_init_struct.mode = GPIO_MODE_OUTPUT;//IO模式
    gpio_config(&gpio_init_struct);
}

void iic_init_mpu6050(void){

}

static void tcp_client_task(void *pvParameters)//tcp/ip协议任务
{
    char rx_buffer[128];
    char host_ip[] = "192.168.0.219";
    int  port = 5678;
    int  addr_family = 0;
    int  ip_protocol = 0;
    static const char *payload = "Hello, I am ESP32 Client.";
    while (1) {
        struct sockaddr_in dest_addr;
        dest_addr.sin_addr.s_addr = inet_addr(host_ip);
        dest_addr.sin_family = AF_INET;
        dest_addr.sin_port = htons(port);
        addr_family = AF_INET;
        ip_protocol = IPPROTO_IP;
        int sock =  socket(addr_family, SOCK_STREAM, ip_protocol);
        if (sock < 0) {
            ESP_LOGE(TAG, "Unable to create socket: errno %d", errno);
            break;
        }
        ESP_LOGI(TAG, "Socket created, connecting to %s:%d", host_ip, port);
 
        int err = connect(sock, (struct sockaddr *)&dest_addr, sizeof(struct sockaddr_in6));
        if (err != 0) {
            ESP_LOGE(TAG, "Socket unable to connect: errno %d", errno);
            break;
        }
        ESP_LOGI(TAG, "Successfully connected");
 
        err = send(sock, payload, strlen(payload), 0);//信息发送，Hello, I am ESP32 Client，表示完成配置
		if (err < 0) {
			ESP_LOGE(TAG, "Error occurred during sending: errno %d", errno);
			break;
		}
        /*
        上为标准化配置
        */
        while (1) {//此处开始正式进行tcp任务
 
            int len = recv(sock, rx_buffer, sizeof(rx_buffer) - 1, 0);
            // Error occurred during receiving
            if (len < 0) {
                ESP_LOGE(TAG, "recv failed: errno %d", errno);
                break;
            }
            // Data received
            else {
                rx_buffer[len] = 0; // Null-terminate whatever we received and treat like a string
                ESP_LOGI(TAG, "Received %d bytes from %s:", len, host_ip);
                ESP_LOGI(TAG, "%s", rx_buffer);
            }
 
            vTaskDelay(2000 / portTICK_PERIOD_MS);
        }
 
        if (sock != -1) {
            ESP_LOGE(TAG, "Shutting down socket and restarting...");
            shutdown(sock, 0);
            close(sock);
        }
    }
    vTaskDelete(NULL);
}

static void pwm_ctrol_task(void *pvParameters)//pwm控制任务
{
//移植pid算法
}

static void gpio_ctrol_task(void *pvParameters)//gpio控制任务
{
//负责引脚控制部分，LED指示灯
}

static void mpu6050_read_task(void *pvParameters)//获取mpu6050传感器的数据
{

}

void app_main(void)
{
    wifi_init_sta();
    pwm_init_time();
    gpio_init_normal();
    iic_init_mpu6050();

    xTaskCreate(tcp_client_task,"tcp_client",4096,NULL,5,NULL);
    xTaskCreate(pwm_ctrol_task,"pwm_ctrol",4096,NULL,5,NULL);
    xTaskCreate(gpio_ctrol_task,"gpio_ctrol",4096,NULL,5,NULL);
    xTaskCreate(mpu6050_read_task,"mpu6050_read",4096,NULL,5,NULL);
}
