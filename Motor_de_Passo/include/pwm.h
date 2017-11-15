#ifndef ADRONE_PWM_H
#define ADRONE_PWM_H

#include <stdint.h>  // uint8_t; uint16_t
#include <stdbool.h> // bool

#include <espressif/esp_common.h>
#include <esp8266.h>


namespace adrone
{
    class pwm
    {
    public:
        /**
         * Constructor sets the initial settings. Copy and move have been disabled
         * 
         * @param other pwm object
         */
        pwm();
        pwm(const pwm &other)  = delete;
        pwm(const pwm &&other) = delete;

       /**
         * Disable copy and move assignment operator
         * 
         * @param other pwm object
         */
        pwm& operator=(const pwm &other)  = delete;
        pwm& operator=(const pwm &&other) = delete;

        /**
         * Defines the pwm pin as well as the maximum cycle value
         * 
         * @param pin GPIO pin
         * @param max_duty_cycle Maximum duty cycle value
         */
        void init(const uint8_t &pin, const uint16_t &max_duty_cycle = 4096);

        /**
         * @brief [brief description]
         * @details [long description]
         * 
         * @param duty_cycle [description]
         */
        void update(const uint16_t &duty_cycle);

    private:
        uint8_t  _pin;
        uint16_t _counter;
        uint16_t _max_duty_cycle;
    };
}

#endif
