#include "PID.h"

using namespace std;

/*
* TODO: Complete the PID class.
*/

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp, double Ki, double Kd) {
  Kp_ = Kp;
  Ki_ = Ki;
  Kd_ = Kd;
  TotalCte_ = 0.0;
}

double PID::Steer(double cte) {
  UpdateError(cte);
  double steer = -Kp_ * cte - Kd_ * (cte - PrevCte_) - Ki_ * TotalCte_;
  PrevCte_ = cte;
  return steer;
}

void PID::UpdateError(double cte) {
  TotalCte_ += cte;
}

double PID::TotalError() {
  return TotalCte_;
}


