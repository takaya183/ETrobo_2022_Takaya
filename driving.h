#ifndef ETRC22_DRIVING_H_
#define ETRC22_DRIVING_H_

#include "device_io.h"
#include "etrc_info.h"
#include "info_type.h"
#include "utils.h"
#include "time.h"

class WheelsControl {
 public:
  WheelsControl(MotorIo* motor_io);
  void Exec(int8_t target_power_l, int8_t target_power_r);
  void LineTrace(Hsv curr_hsv);
  void GoStraight(int8_t power);
  void GoBackStraight(int8_t power);
  void TurnLeft();
  void Stop();

 private:
  clock_t before_time = 0;
  MotorIo* motor_io_;
};

#endif  // ETRC22_DRIVING_H_
