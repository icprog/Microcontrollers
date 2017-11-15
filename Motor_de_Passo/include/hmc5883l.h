#ifndef ADRONE_HMC5883L_H
#define ADRONE_HMC5883L_H

#include <stdint.h>
#include "sensor.h"


namespace adrone
{
    class hmc5883l : public sensor
    {
    public:
        // setup registers
        bool init();
        // check wire connection
        bool connected();
        // read data from sensor
        void read();
        // get Y axie gauss
        const double& get_x() const;
        // get X axie gauss
        const double& get_y() const;
        // get Z axie gauss
        const double& get_z() const;

    private:
        double  _data[3];      // aceleration data
    };
}

#endif
