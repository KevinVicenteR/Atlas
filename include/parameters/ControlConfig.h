#pragma once
#include "parameters/Constants.h"
namespace atlas {
struct ControlConfig {
  float kp = 0.014f;
  float kd = 1.0f;
  int16_t maxCorrectionPwm = 1000;

  uint8_t derivativeFilterShift = 1;

  uint8_t curveSlowdownPercent = 27;
  int16_t maxForwardPwm = 255;
  int16_t maxBackwardPwm = -134;

  int16_t minMotorPwm = 40;
  uint16_t loopPeriodUs = 750;
};
}
