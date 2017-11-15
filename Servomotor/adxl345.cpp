#include "adxl345.h"

#define ADDR            0x53  // i2c address
#define ID              0xE5  // reg id address

#define REG_WHO_AM_I    0x00  // device id
#define REG_OFFSET_X    0x1E  // offset x
#define REG_OFFSET_Y    0x1F  // offset y
#define REG_OFFSET_Z    0x20  // offset z
#define REG_BW_RATE     0x2C  // data rate, power mode
#define REG_POWER_CTL   0x2D  // power control
#define REG_DATA_FORMAT 0x31  // data resolution
#define REG_DATA        0x32  // first data + 6


bool adrone::adxl345::init()
{
    if (!connected()) return false;

    // stop measurement
    write_byte(ADDR, REG_POWER_CTL, 0x00);
    // define offset
    //write_byte(ADDR, REG_OFFSET_X, x);
    //write_byte(ADDR, REG_OFFSET_Z, y);
    //write_byte(ADDR, REG_OFFSET_Y, z);
    // output data rate 200Hz
    write_byte(ADDR, REG_BW_RATE, 0x0B);
    // full resolution 16g
    write_byte(ADDR, REG_DATA_FORMAT, 0x0B);
    // start measurement
    write_byte(ADDR, REG_POWER_CTL, 0x08);

    // reset offset values
    _offset[0] = 0;
    _offset[1] = 0;
    _offset[2] = 0;

    return true;
}


bool adrone::adxl345::connected()
{
    uint8_t data;
    read_byte(ADDR, REG_WHO_AM_I, &data);

    return (data == ID) ? true : false;
}


void adrone::adxl345::read()
{
    uint8_t reg[6];
    read_bytes(ADDR, REG_DATA, reg, 6);

    _raw[0] = ((int16_t)reg[1] << 8) | reg[0];
    _raw[1] = ((int16_t)reg[3] << 8) | reg[2];
    _raw[2] = ((int16_t)reg[5] << 8) | reg[4];

    _data[0] = (_raw[0] - _offset[0]) * 0.00390625;
    _data[1] = (_raw[1] - _offset[1]) * 0.00390625;
    _data[2] = (_raw[2] - _offset[2]) * 0.00390625;
}


void adrone::adxl345::calibrate()
{
    for (unsigned i = 0; i < 100; ++i)
    {
        read();

        _offset[0] += _raw[0];
        _offset[1] += _raw[1];
        _offset[2] += _raw[2];

        vTaskDelay(5 / portTICK_PERIOD_MS);
    }

    _offset[0] /= 100;
    _offset[1] /= 100;
    _offset[2]  = (_offset[2] / 100) - 256;
}


const double& adrone::adxl345::get_x() const
{
    return _data[0];
}


const double& adrone::adxl345::get_y() const
{
    return _data[1];
}


const double& adrone::adxl345::get_z() const
{
    return _data[2];
}
