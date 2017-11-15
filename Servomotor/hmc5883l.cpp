#include "hmc5883l.h"

#define ADDR          0x1E   // i2c address
#define ID_A          0x48   // device id
#define ID_B          0x34
#define ID_C          0x33

#define REG_WHO_AM_I  0x0A  // device reg id
#define REG_A         0x00
#define REG_B         0x01
#define REG_MODE      0x02
#define REG_DATA      0x03


bool adrone::hmc5883l::init()
{
    if (!connected()) return false;

    // 2 samples averaged - 75Hz
    write_byte(ADDR, REG_A, 0b00111000);
    // to do...
    //write_byte(ADDR, REG_B, );
    //continuous measurement mode
    write_byte(ADDR, REG_MODE, 0x00);

    return true;
}


bool adrone::hmc5883l::connected()
{
    uint8_t reg[3];
    read_bytes(ADDR, REG_WHO_AM_I, reg, 3);

    return (
        (reg[0] == ID_A) &&
        (reg[1] == ID_B) &&
        (reg[2] == ID_C)) ? true : false;
}


void adrone::hmc5883l::read()
{
    uint8_t reg[6];
    read_bytes(ADDR, REG_DATA, reg, 6);

    int16_t raw[3];
    raw[0] = ((int16_t)reg[0] << 8) | reg[1];
    raw[2] = ((int16_t)reg[2] << 8) | reg[3];
    raw[1] = ((int16_t)reg[4] << 8) | reg[5];

    _data[0] = raw[0] * 0.92;
    _data[1] = raw[1] * 0.92;
    _data[2] = raw[2] * 0.92;
}


const double& adrone::hmc5883l::get_x() const
{
    return _data[0];
}


const double& adrone::hmc5883l::get_y() const
{
    return _data[1];
}


const double& adrone::hmc5883l::get_z() const
{
    return _data[2];
}
