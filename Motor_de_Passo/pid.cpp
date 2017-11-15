#include "pid.h"

adrone::pid::pid()
{ }


void adrone::pid::init(const double &kp, const double &ki, const double &kd, const double &dt, const double &max, const double &min)
{
	_dt = dt;
	_previus_error = 0;
	_integral = 0;
	_flag = true;
    _max = max;
    _min = min;

	kpid(kp, ki, kd);
}


void adrone::pid::kpid(const double &kp, const double &ki, const double &kd)
{
	_kp = kp;
	_kd = kd;
	_ki = ki;
}


double adrone::pid::update(const double &setpoint, const double &pv)
{
	// calculate error
    double error = setpoint - pv;

    // calculating the integral term
    if (_flag)
        _integral += error * _dt;

    // calculating the derivative of the error
    double derivative = (error - _previus_error) / _dt;
    _previus_error = error;

    // calculate total output
    double output = (_kp * error) + (_ki * _integral) + (_kd * derivative);

    // Restrict to max/min
    if (output > _max)
    {
        output = _max;
        _flag = false;
    }
    else if(output < _min)
    {
        output = _min;
        _flag = false;
    }
    else
    {
        _flag = true;
    }

    return output;
}