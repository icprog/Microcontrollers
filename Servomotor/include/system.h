#ifndef ADRONE_SYSTEM_H
#define ADRONE_SYSTEM_H

#include <stdint.h>
#include <stdbool.h> // bool

#include "pid.h"


struct {
	bool power;

    bool flag;
    double yaw;

	struct {
		//bool power;
        adrone::pid pid;
        unsigned pwm;
    } motor[4];

    struct {
        double acce_z;
        double gyro_x;
        double gyro_y;
        double gyro_z;
    } flight;

    struct {
        TaskHandle_t flight;
    } task;

} asystem;

#endif