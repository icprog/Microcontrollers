#include <espressif/esp_common.h>
#include <esp/uart.h>
#include <esp8266.h>
#include <FreeRTOS.h>
#include <task.h>

const int D0 = 16, D1 = 5, D2 = 4, D3 = 0;

const bool LOW = 0, HIGH = 1;

const unsigned int timer = 5000;

void step_0 () 
{
    gpio_write(D0, LOW);
    gpio_write(D1, LOW);
    gpio_write(D2, LOW);
    gpio_write(D3, LOW);
    sdk_os_delay_us(timer);
}

void step_1 () 
{
    gpio_write(D0, HIGH);
    gpio_write(D1, LOW);
    gpio_write(D2, LOW);
    gpio_write(D3, LOW);
    sdk_os_delay_us(timer);
}

void step_2 () 
{
    gpio_write(D0, LOW);
    gpio_write(D1, HIGH);
    gpio_write(D2, LOW);
    gpio_write(D3, LOW);
    sdk_os_delay_us(timer); 
}

void step_3 () 
{
    gpio_write(D0, LOW);
    gpio_write(D1, LOW);
    gpio_write(D2, HIGH);
    gpio_write(D3, LOW);
    sdk_os_delay_us(timer); 
}

void step_4 () 
{
    gpio_write(D0, LOW);
    gpio_write(D1, LOW);
    gpio_write(D2, LOW);
    gpio_write(D3, HIGH);
    sdk_os_delay_us(timer);
}

extern "C" void user_init(void)
{
    gpio_enable(D0, GPIO_OUTPUT);
    gpio_enable(D1, GPIO_OUTPUT);
    gpio_enable(D2, GPIO_OUTPUT);
    gpio_enable(D3, GPIO_OUTPUT);

    step_0();

    uint8_t cont = 1;
    
    while(1)
    {
        //sentido horario
        for (int i = 0; i < 2100; ++i)
        {
            switch(cont)
            {
                case 1:
                    step_1();
                    cont++;
                    break;
                case 2:
                    step_2();
                    cont++;
                    break;
                case 3:
                    step_3();
                    cont++;
                    break;
                case 4:
                    step_4();
                    cont = 1;
                    break;
                default:
                    step_0();
                    cont = 1;
                    break;
            }
        }
        // sentido anti-horario
        for (int i = 0; i < 2100; ++i)
        {
            switch(cont)
            {
                case 1:
                    step_4();
                    cont++;
                    break;
                case 2:
                    step_3();
                    cont++;
                    break;
                case 3:
                    step_2();
                    cont++;
                    break;
                case 4:
                    step_1();
                    cont = 1;
                    break;
                default:
                    step_0();
                    cont = 1;
                    break;
            }

        }

    }
}

