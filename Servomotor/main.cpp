#include <espressif/esp_common.h>
#include <esp/uart.h>
#include <esp8266.h>
#include <FreeRTOS.h>
#include <task.h>

const int D1 = 5;

const bool HIGH = 1;
const bool LOW = 0;

extern "C" void user_init(void)
{
    gpio_enable(D1, GPIO_OUTPUT);
    gpio_write(D1, LOW);

    while(1)
    {
        for(int i = 0; i < 1000; i=i+100)
        {
            gpio_write(D1, HIGH);
            sdk_os_delay_us(1000+i);
            gpio_write(D1, LOW);
            sdk_os_delay_us(19000-i);    
        }
    }
}


/*
para lembrar

gpio_read
gpio_write
gpio_enable(porta, GPIO_INPUT)
sdk_os_delay_us()
*/