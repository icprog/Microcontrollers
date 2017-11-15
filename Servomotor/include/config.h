#ifndef ADRONE_CONFIG_H
#define ADRONE_CONFIG_H


// Serial baud rate
#define BAUD_RATE 115200


// i2c pins
#define SCL_PIN 13
#define SDA_PIN 12


// motor pins, dont use pin 16 -> wakeup func
#define MOTOR1  16  //15
#define MOTOR2  5   //12
#define MOTOR3  14  //14
#define MOTOR4  4   //4


// wifi settings
#define AP_SSID "ESP-OTA-AP"
#define AP_PSK  "espotaap"


// socket settings
#define WS_TIMEOUT 15


#endif