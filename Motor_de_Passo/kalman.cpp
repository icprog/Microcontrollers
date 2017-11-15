#include "kalman.h"

#define mF (*_F)
#define mB (*_B)
#define mQ (*_Q)
#define mH (*_H)
#define mR (*_R)
#define mX _X
#define mP _P

adrone::kalman::kalman()
{ }


void adrone::kalman::init(matrix *F, matrix *B, matrix *Q, matrix *H, matrix *R)
{
    _F = F;
    _B = B;
    _Q = Q;
    _H = H;
    _R = R;

    _X = matrix(B->get_num_rows(), B->get_num_cols());

    _P = matrix(F->get_num_rows(), F->get_num_cols());
    _P.set_values(4,
        1.0 , 0.0,
        0.0 , 1.0
    );
}


double adrone::kalman::update(const double &angle, const double &rate)
{
    matrix K;

    mX = (mF * mX) + (mB * angle);
    mP = (mF * mP * (~mF)) + mQ;
    K  = mP*(~mH)*((mH * mP * (~mH) + mR)^-1);
    mX = mX + K*(rate - (mH*mX)(0,0));
    mP = mP - K*mH*mP;
    return (mH * mX)(0,0);
}
