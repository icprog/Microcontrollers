#include "l3g4200d.h"

#define ADDR          0x69
#define ID            0xD3

#define REG_WHO_AM_I  0x0F
#define REG_1         0x20
#define REG_2         0x21
#define REG_3         0x22
#define REG_4         0x23
#define REG_5         0x24
#define REG_TEMP      0x26
#define REG_DATA      0x28


bool adrone::l3g4200d::init()
{
    if (!connected()) return false;

    // High pass filter
    write_byte(ADDR, REG_2, 0x00);
    // Generata data ready interrupt
    write_byte(ADDR, REG_3, 0x00);
    // Controls the full-scale range
    write_byte(ADDR, REG_4, 0b00000000);
    // Boot in normal mode, disable FIFO, HPF disabled
    write_byte(ADDR, REG_5, 0x00);
    // Enable all axis and setup normal mode + Output Data Range & Bandwidth
    write_byte(ADDR, REG_1, 0b01111111);

    // reset offset values
    _offset[0] = 0;
    _offset[1] = 0;
    _offset[2] = 0;

    return true;
}


bool adrone::l3g4200d::connected()
{
    uint8_t data;
    read_byte(ADDR, REG_WHO_AM_I, &data);

    return (data == ID) ? true : false;
}


void adrone::l3g4200d::read()
{
    uint8_t reg[6];  // 3 axis data from 6 registers
    read_bytes(ADDR, REG_DATA | (1 << 7), reg, 6);

    _raw[0] = ((int16_t)reg[1] << 8) | reg[0];
    _raw[1] = ((int16_t)reg[3] << 8) | reg[2];
    _raw[2] = ((int16_t)reg[5] << 8) | reg[4];

    //read_byte(ADDR, REG_TEMP, &reg[0]);
    //double factor =

    _data[0] = (_raw[0] - _offset[0]) * 0.00875; // + factor);
    _data[1] = (_raw[1] - _offset[1]) * 0.00875; // + factor);
    _data[2] = (_raw[2] - _offset[2]) * 0.00875; // + factor);
}


void adrone::l3g4200d::calibrate()
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
    _offset[2] /= 100;
}


const double& adrone::l3g4200d::get_x() const
{
    return _data[0];
}


const double& adrone::l3g4200d::get_y() const
{
    return _data[1];
}


const double& adrone::l3g4200d::get_z() const
{
    return _data[2];
}
