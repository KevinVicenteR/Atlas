#pragma once
#include "parameters/Constants.h"
namespace atlas {
struct CornerConfig {
  bool enabled = true;
  int16_t triggerError = 2000;
  uint8_t speedPercent = 74;
  uint16_t holdMs = 7;
  uint16_t recoveryMs = 291;
};
}
