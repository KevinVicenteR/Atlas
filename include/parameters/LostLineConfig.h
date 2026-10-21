#pragma once
#include "parameters/Constants.h"
namespace atlas {
struct LostLineConfig {
  int16_t outerMotorPwm = 175;
  int16_t innerMotorPwm = -134;
  uint16_t innerBrakeMs = 54;

  uint16_t gapBridgeMs = 200;
  int16_t gapCenterTolerance = 1500;
  uint16_t gapStraightMs = 25;

  uint16_t gapChainMs = 300;
};
}
