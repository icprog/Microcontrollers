#include "pwm.h"

adrone::pwm::pwm()
{ }


void adrone::pwm::init(const uint8_t &pin, const uint16_t &max_duty_cycle)
{
    _pin            = pin;
    _counter        = 0;
    _max_duty_cycle = max_duty_cycle;

    gpio_enable(_pin, GPIO_OUTPUT);
}


void adrone::pwm::update(const uint16_t &duty_cycle)
{
    if (duty_cycle != 0)
    {
        if (_counter == duty_cycle)
        {
            gpio_write(_pin, 0);
        }
        else if (_counter >= _max_duty_cycle)
        {
            gpio_write(_pin, 1);
            _counter = 0;
        }

        ++_counter;
    }
    else
    {
        gpio_write(_pin, 0);
    }
}
