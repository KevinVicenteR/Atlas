#pragma once
#include "parameters/Constants.h"
namespace atlas {
struct SpeedConfig {
  int16_t basePwm = 100;
  int16_t minPwm = 60;
  int16_t maxPwm = 250;
  int16_t stepPwm = 10;
  uint16_t runRampMs = 150;
  uint16_t stopBrakeMs = 500;

  int16_t startKickPwm = 100;
  uint16_t startKickMs = 200;
};
}
