#include "sensorfusion.h"


adrone::sensorfusion::sensorfusion()
{
	// setup i2c
    i2c_init(SCL_PIN, SDA_PIN);

    // start sensors
    if (!_acce.init()) {
        printf("Oops, ADXL345 not detected ... Check your wiring.. Restart device!!!");
        //while (true);
        vTaskDelete(asystem.task.flight);
    }

    if (!_gyro.init()) {
        printf("Oops, L3G4200D not detected ... Check your wiring.. Restart device!!!");
        vTaskDelete(asystem.task.flight);
    }

    if (!_magn.init()) {
        printf("Oops, HMC5883L not detected ... Check your wiring.. Restart device!!!");
        vTaskDelete(asystem.task.flight);
    }

    // delay time for sensor setup
    vTaskDelay(10 / portTICK_PERIOD_MS);

    // calibrate sensors
    _acce.calibrate();
    _gyro.calibrate();

    // kalman filter parameters
    _F = new adrone::matrix(2, 2);
    _F->set_values(4,
    	1.0 , 0.05,
    	0.0 , 1.0
    );

    _B = new adrone::matrix(2, 1);
    _B->set_values(2,
    	0.05,
    	0.0
    );

    _Q = new adrone::matrix(2, 2, 0.3);

    _H = new adrone::matrix(1, 2);
    _H->set_values(2,
    	1.0,
    	0.0
    );

    _R = new adrone::matrix(1, 1, 0.3);

    // result matrix6x1 > 3 positons 3 angles
    _angle_position = adrone::matrix(6, 1);

    // setup kalman filter for 3 angles
    _kpitch.init(_F, _B, _Q, _H, _R);
    _kroll.init (_F, _B, _Q, _H, _R);
    _kyaw.init  (_F, _B, _Q, _H, _R);
}


adrone::sensorfusion::~sensorfusion()
{
    delete _F;
    delete _B;
    delete _Q;
    delete _H;
    delete _R;
}

adrone::matrix adrone::sensorfusion::update()
{
    // read data from sensors
    _acce.read();
    _gyro.read();
    _magn.read();

    //printf("%f   %f   %f\n",_acce.get_x(),_acce.get_y(),_acce.get_z());
    //return _angle_position;

    // calculate pitch & roll from accelerometer
    double pitch = get_pitch(_acce.get_x(), _acce.get_y(), _acce.get_z());
    double roll  = get_roll (_acce.get_x(), _acce.get_y(), _acce.get_z());

    // calculate pitch & roll from kalman filter
    pitch = _kpitch.update(_gyro.get_x(), pitch);
    roll  = _kroll.update (_gyro.get_y(), roll );

    // calculate yaw from magnetometer compensation
    double yaw = get_yaw(_magn.get_x(), _magn.get_y(), _magn.get_z(), pitch, roll);

    // calculate yaw from kalman filter
    yaw = _kyaw.update(_gyro.get_z(), yaw);

    // remove gravity
    adrone::matrix position(3,1);
    position(0,0) = _acce.get_x();
    position(1,0) = _acce.get_y();
    position(2,0) = _acce.get_z();

    position = remove_gravity(position, yaw, roll, pitch);

    // setup output
    _angle_position(0,0) = position(0,0);
    _angle_position(1,0) = position(1,0);
    _angle_position(2,0) = position(2,0);
    _angle_position(3,0) = (pitch)*180.0/M_PI;
    _angle_position(4,0) = (roll)*180.0/M_PI;
    _angle_position(5,0) = (yaw)*180.0/M_PI;

    return _angle_position;
}


double adrone::sensorfusion::get_pitch(const double &x, const double &y, const double &z)
{
    return atan2(x, sqrt(y*y + z*z));
}


double adrone::sensorfusion::get_roll(const double &x, const double &y, const double &z)
{
    return atan2(y, sqrt(x*x + z*z));
}

double adrone::sensorfusion::get_yaw(const double &x, const double &y, const double &z, const double &pitch, const double &roll)
{
    double hx  = x * cos(pitch) + y * sin(pitch)*sin(roll) + z * sin(pitch)*cos(roll);
    double hy  = y * cos(roll) - z * sin(roll);

    return atan2(hy,hx);
}


adrone::matrix adrone::sensorfusion::remove_gravity(adrone::matrix position, const double &alpha, const double &beta, const double &gama)
{

    adrone::matrix gravity(3,1);
    gravity(0,0) = 0;
    gravity(1,0) = 0;
    gravity(2,0) = 1; // G

    // em função dos ângulos em _pitch, _roll e _yaw
    adrone::matrix rotation_matrix(3,3);
    /*rotation_matrix(0,0) = cos(roll) * cos(yaw);
    rotation_matrix(0,1) = -cos(roll) * sin(yaw);
    rotation_matrix(0,2) = -sin(roll);

    rotation_matrix(1,0) = sin(pitch) * sin(roll) * cos(yaw) + cos(pitch) * sin(yaw);
    rotation_matrix(1,1) = cos(pitch) * cos(yaw) - sin(pitch) * sin(roll) * sin(yaw);
    rotation_matrix(1,2) = -sin(pitch) * cos(roll);

    rotation_matrix(2,0) = sin(pitch) * sin(yaw) - cos(pitch) * sin(roll) * cos(yaw);
    rotation_matrix(2,1) = cos(pitch) * sin(roll) * sin(yaw) + sin(pitch) * cos(yaw);
    rotation_matrix(2,2) = cos(pitch) * cos(roll);*/

    /*rotation_matrix(0,0) = cos(alpha)*cos(beta);
    rotation_matrix(0,1) = cos(alpha)*sin(beta)*sin(gama) - sin(alpha)*cos(gama);
    rotation_matrix(0,2) = cos(alpha)*sin(beta)*cos(gama) + sin(alpha)*sin(gama);

    rotation_matrix(1,0) = sin(alpha)*cos(beta);
    rotation_matrix(1,1) = sin(alpha)*sin(beta)*sin(gama) + cos(alpha)*cos(gama);
    rotation_matrix(1,2) = sin(alpha)*sin(beta)*cos(gama) - cos(alpha)*sin(gama);

    rotation_matrix(2,0) = -sin(beta);
    rotation_matrix(2,1) = cos(beta)*sin(gama);
    rotation_matrix(2,2) = cos(beta)*cos(gama);*/

    /*printf("%f  %f  %f\n%f  %f  %f\n%f  %f  %f\n",
      rotation_matrix(0,0),rotation_matrix(0,1),rotation_matrix(0,2),
      rotation_matrix(1,0),rotation_matrix(1,1),rotation_matrix(1,2),
      rotation_matrix(2,0),rotation_matrix(2,1),rotation_matrix(2,2));*/

    position = position - rotation_matrix * gravity;

    position(0,0) -= 1.0 * cos(beta) * sin(gama);
    position(1,0) -= 1.0 * sin(beta);
    position(2,0) -= 1.0 * cos(beta) * cos(gama) * position(2,0)/fabs(position(2,0));

    //printf("\n\n%f    %f    %f\n\n", sin(beta), (cos(beta) * sin(gama)), (cos(beta) * cos(gama)));

    return position;
}


/*
void printMatrix(const adrone::matrix &a)
{
    for(uint8_t i=0; i<a.get_num_rows(); ++i) {
        for(uint8_t j=0; j<a.get_num_cols(); ++j) {
            printf("%f ", a(i,j));
        }
        printf("\n");
    }
}
*/