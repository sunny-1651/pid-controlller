#include "PID.h"
#include <vector>
#include <numeric>
#include <iostream>

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp_, double Ki_, double Kd_)
{
  this->Kp = Kp_;
  this->Ki = Ki_;
  this->Kd = Kd_;

  i_error = 0.0;
  d_error = 0.0;
  p_error = 0.0;
}

void PID::UpdateError(double cte)
{
  d_error = cte - p_error;
  p_error = cte;
  i_error += cte;  
}

double PID::TotalError()
{
  return ((p_error * Kp) + (i_error * Ki) + (d_error * Kd));
}

void PID::SetGains(const double Kp_G, const double Ki_G, const double Kd_G)
{
  Kp = Kp_G;
  Ki = Ki_G;
  Kd = Kd_G;
}

double PID::CalcSteerAngle()
{
  double angle;

  angle = -Kp * p_error - Kd * d_error - Ki * i_error;

  //The angle must be between -1 and 1
  if(angle < -1){
    angle = -1;
  }
  else if (angle > 1){
    angle = 1;
  }

  return angle;
}