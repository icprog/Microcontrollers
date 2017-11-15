#include <espressif/esp_common.h>
#include <esp/uart.h>
#include <esp8266.h>
#include <FreeRTOS.h>
#include <task.h>

const int D3 = 0, D1 = 2;

extern "C" void user_init(void)
{
    gpio_enable(D3, GPIO_INPUT);
    gpio_enable(D1, GPIO_OUTPUT);

    gpio_write(D1, 0);

    bool valorLido;

    while(1)
    {
        valorLido = gpio_read(D3);
        gpio_write(D1, valorLido);
    }
}


/*
para lembrar

gpio_read
gpio_write
gpio_enable(porta, GPIO_INPUT)
sdk_os_delay_us()
*/