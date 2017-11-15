#ifndef ADRONE_KALMANFILTER_H
#define ADRONE_KALMANFILTER_H

#include "matrix.h"


namespace adrone
{
    class kalman
    {
    public:
        /**
         * Constructor sets the initial settings. Copy and move have been disabled
         * 
         * @param other kalman object
         */
        kalman();
        kalman(const kalman &kalman)  = delete;
        kalman(const kalman &&kalman) = delete;

        /**
         * Disable copy and move assignment operator
         * 
         * @param other kalman object
         */
        kalman& operator=(const kalman &other)  = delete;
        kalman& operator=(const kalman &&other) = delete;

        /**
         * [description]
         * 
         * @param F [description]
         * @param B [description]
         * @param Q [description]
         * @param H [description]
         * @param R [description]
         */
        void init(matrix *F, matrix *B, matrix *Q, matrix *H, matrix *R);

        /**
         * Update filter
         * 
         * @param angle [description]
         * @param rate [description]
         * 
         * @return [description]
         */
        double update(const double &angle, const double &rate);

    private:
        matrix *_F, *_B, *_Q, *_H, *_R;
        matrix _X, _P;
    };
}

#endif
