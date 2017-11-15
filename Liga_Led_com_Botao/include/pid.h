#ifndef ARONE_PID_H
#define ARONE_PID_H

namespace adrone
{
	class pid
	{
	public:
		/**
         * Constructor sets the initial settings. Copy and move have been disabled
         * 
         * @param other pid object
         */
        pid();
        pid(const pid &other)  = delete;
        pid(const pid &&other) = delete;

       /**
         * Disable copy and move assignment operator
         * 
         * @param other pid object
         */
        pid& operator=(const pid &other)  = delete;
        pid& operator=(const pid &&other) = delete;

        /**
         * [brief description]
         * 
         * @param kp [description]
         * @param ki [description]
         * @param kd [description]
         * @param dt [description]
         * @param max [description]
         * @param min [description]
         */
        void init(const double &kp, const double &ki, const double &kd, const double &dt, const double &max = 4096.0, const double &min = 0.0);

        /**
         * [brief description]
         * 
         * @param kp [description]
         * @param ki [description]
         * @param kd [description]
         */
        void kpid(const double &kp, const double &ki, const double &kd);

        /**
         * [brief description]
         * 
         * @param setpoint [description]
         * @param pv [description]
         * 
         * @return [description]
         */
        double update(const double &setpoint, const double &pv);

    private:
    	double _kp, _kd, _ki, _dt;
    	double _max, _min;
        double _previus_error;
        double _integral;
        bool   _flag;
	};
}

#endif