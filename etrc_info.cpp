#include "etrc_info.h"

#include <math.h>

#include "app.h"

Luminous::Luminous(SensorIo* sensor_io)
    : color_(kInvalidColor), hsv_({0, 0, 0}), sensor_io_(sensor_io) {
}

void Luminous::Update() {
  UpdateRgb();
  UpdateHsv();
  UpdateColor();
}

void Luminous::SetColorReference(Color c, Hsv hsv) {
  color_ref_[c] = hsv;
}

void Luminous::UpdateRgb() {
  rgb_raw_t val = sensor_io_->color_rgb_raw_;
  rgb_.r = val.r;
  rgb_.g = val.g;
  rgb_.b = val.b;
}

void Luminous::UpdateHsv() {
  float r = static_cast<float>(rgb_.r);
  float g = static_cast<float>(rgb_.g);
  float b = static_cast<float>(rgb_.b);

  float max = r > g ? r : g;
  max = max > b ? max : b;
  float min = r < g ? r : g;
  min = min < b ? min : b;
  float c = max - min;

  float h;
  if (c == 0) {
    h = -1;
  } else if (max == r) {
    h = fmodf(((g - b) / c), 6);
  } else if (max == g) {
    h = ((b - r) / c) + 2;
  } else if (max == b) {
    h = ((r - g) / c) + 4;
  } else {
    h = -1;
  }

  if (h != -1) {
    h = 60 * h;
  }

  float s;
  if (max == 0) {
    s = 0;
  } else {
    s = c / max;
  }

  float v = max;
  if (v > 100) {
    v = 100;
  }

  hsv_.h = h;
  hsv_.s = s * 100;
  hsv_.v = v;
}


void Luminous::CheckCurrHsv() {
  char str[256];
  sprintf(str, "%f, %f, %f\n ", hsv_.h, hsv_.s, hsv_.v);
  syslog(LOG_NOTICE, str);
}

void Luminous::UpdateColor() {
}

Localize::Localize(MotorIo* motor_io)
    : motor_io_(motor_io) {
}

void Localize::Update() {
  int32_t counts_r_ = motor_io_->counts_r_;
  int32_t counts_l_ = motor_io_->counts_l_;

  counts_rs[curr_index] = counts_r_;
  counts_ls[curr_index] = counts_l_;
  curr_index += 1;
}

void Localize::SaveOdometri() {
  char str [256];
  FILE* fp = fopen("Odometri.csv", "w");

  for (int i=0; i<curr_index; i++) {
    sprintf(str, "%d, %d\n", counts_rs[i], counts_ls[i]);
    fprintf(fp, str);
  }

  fclose(fp);
}
