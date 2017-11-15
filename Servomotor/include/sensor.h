#ifndef _ADRONE_SENSOR_H_
#define _ADRONE_SENSOR_H_

#include <stdint.h>  // uint8_t; uint16_t
#include <stdbool.h> // bool
#include <i2c/i2c.h> // i2c_slave_read; i2c_slave_write


namespace adrone
{
    class sensor
    {
    public:
        /**
         * Setup registers
         * 
         * @return Verifies that the startup was successful
         */
        virtual bool init() = 0;

        /**
         * Check if sensor is connected correctly
         * 
         * @return Wiring well connected
         */
        virtual bool connected() = 0;

        /**
         * Read data from sensor
         */
        virtual void read() = 0;

    protected:
        /**
         * Read one byte from device
         * 
         * @param addr Address of the sensor on the bus
         * @param reg Registrar address
         * @param data Read sensor data
         */
        void read_byte(uint8_t addr, uint8_t reg, uint8_t *data)
        {
            i2c_slave_read(addr, &reg, data, 1);
        }
        
        /**
         * Read n byte from device
         * 
         * @param addr Address of the sensor on the bus
         * @param reg Registrar address
         * @param data Read sensor data
         * @param len Number of registers
         */
        void read_bytes(uint8_t addr, uint8_t reg, uint8_t *data, uint8_t len)
        {
            i2c_slave_read(addr, &reg, data, len);
        }

        /**
         * Write one byte from device
         * 
         * @param addr Address of the sensor on the bus
         * @param reg Registrar address
         * @param value Data to write to the sensor register
         */
        void write_byte(uint8_t addr, uint8_t reg, uint8_t value)
        {
            i2c_slave_write(addr, &reg, &value, 1);
        }
    };
}

#endif
