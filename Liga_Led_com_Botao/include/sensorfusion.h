#ifndef ADRONE_SENSOR_FUSION_H
#define ADRONE_SENSOR_FUSION_H

#define M_PI    3.14159265358979323846

// c library
#include <stdint.h>
#include <math.h>
// esp + extras
#include <espressif/esp_common.h>
#include <i2c/i2c.h>
// RTOS
#include <FreeRTOS.h>
#include <task.h>
// project
#include "system.h"
#include "config.h"
#include "matrix.h"
#include "kalman.h"
#include "adxl345.h"
#include "l3g4200d.h"
#include "hmc5883l.h"


namespace adrone
{
    class sensorfusion
    {
    public:
        /**
         * Constructor sets the initial settings. Copy and move have been disabled
         * 
         * @param other sensorfusion object
         */
        sensorfusion();
        sensorfusion(const sensorfusion &other)  = delete;
        sensorfusion(const sensorfusion &&other) = delete;

       /**
         * Disable copy and move assignment operator
         * 
         * @param other sensorfusion object
         */
        sensorfusion& operator=(const sensorfusion &other)  = delete;
        sensorfusion& operator=(const sensorfusion &&other) = delete;

        /**
         * [brief description]
         */
        ~sensorfusion();

        /**
         * [description]
         * 
         * @return [description]
         */
        matrix update();

    private:
        // sensors
        adrone::adxl345  _acce;
        adrone::l3g4200d _gyro;
        adrone::hmc5883l _magn;
        // matrix result with position & angles
        matrix _angle_position;
        // kalman filter parameters
        matrix *_F, *_B, *_Q, *_H, *_R;
        // kalman filters
        adrone::kalman _kpitch, _kroll, _kyaw;
        // X axis as reference in radians
        double get_pitch(const double &x, const double &y, const double &z);
        // Y axis as reference in radians
        double get_roll(const double &x, const double &y, const double &z);
        // to compensate and correct the yaw in radians
        double get_yaw(const double &x, const double &y, const double &z, const double &pitch, const double &roll);
        // remove gravity from accelerometer axis
        matrix remove_gravity(matrix position, const double &alpha, const double &beta, const double &gama);
    };
}

#endif