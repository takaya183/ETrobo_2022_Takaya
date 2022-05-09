#include "driving.h"

#include <math.h>
#include <time.h>

#define DELTA_T 0.004
float integral;

WheelsControl::WheelsControl(MotorIo* motor_io) : motor_io_(motor_io) {
}

void WheelsControl::Exec(int8_t target_power_l, int8_t target_power_r) {
  // int8_t curr_power_l = motor_io_->power_l_;
}

void WheelsControl::LineTrace(Hsv curr_hsv) {
  /*
  clock_t now = clock();
  char str[264];
  sprintf(str, "time: %f\n", (static_cast<double>(now-before_time))/CLOCKS_PER_SEC);
  syslog(LOG_NOTICE, str);
  before_time = now;
  */

  /*
  char str[264];
  sprintf(str, "right: %d, left: %d\n", motor_io_->counts_r_, motor_io_->counts_l_);
  syslog(LOG_NOTICE, str);
  */
  /*int8_t base_power = 50;
  float target_v = 40;

  static float diff[2];
  float p, i, d;
  float kp = 0.36, ki = 1.2, kd = 0.027;
  
  diff[0] = diff[1];
  diff[1] = curr_hsv.v - target_v;
  integral += (diff[1] + diff[0]) / 2.0 * DELTA_T;

  p = kp * diff[1];
  i = ki * integral;
  d = kd * (diff[1] - diff[0]) / DELTA_T;

  int8_t right_power = static_cast<int8_t>(base_power + p + i + d);
  int8_t left_power = static_cast<int8_t>(base_power - p - i - d);
  */

  int8_t base_power = 50;
  float target_v = 10;

  float kp = 0.5;
  float mv = (curr_hsv.v - target_v) * kp;

  int8_t right_power = static_cast<int8_t>(base_power - mv);
  int8_t left_power = static_cast<int8_t>(base_power + mv);

  //float mv = calcMv(curr_hsv.v);
  /*float kp = 0.45;
  float mv = (target_v - curr_hsv.v) * kp;

  int8_t right_power = static_cast<int8_t>(base_power + mv);
  int8_t left_power = static_cast<int8_t>(base_power - mv);
  */

  motor_io_->SetWheelsPower(right_power, left_power);

}

void WheelsControl::GoStraight(int8_t power) {
  motor_io_->SetWheelsPower(power, power);
}

void WheelsControl::GoBackStraight(int8_t power) {
  motor_io_->SetWheelsPower(-power, -power);
}

void WheelsControl::TurnLeft() {
  motor_io_->TurnLeft();
}

void WheelsControl::Stop() {
  bool is_break = true;
  motor_io_->StopWheels(is_break);
}
