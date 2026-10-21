#pragma once

#include <stdint.h>

namespace atlas {

class PdController {
 public:
  PdController(float kp, float kd, int16_t outputLimit, uint8_t derivativeFilterShift = 0);

  void configure(float kp, float kd, int16_t outputLimit, uint8_t derivativeFilterShift);
  void reset();

  int16_t update(int32_t error, uint8_t gainPercent = 100);

 private:
  float kp_;
  float kd_;
  int16_t outputLimit_;
  uint8_t filterShift_;
  int32_t previousError_ = 0;
  int32_t filteredDelta_ = 0;
};

}
