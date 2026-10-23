#pragma once
#include <stdint.h>

namespace atlas {

struct ImpellerConfig {
  int16_t pwm = 200;
  uint16_t startRampMs = 1000;
  uint16_t runRampMs = 250;
  bool spinWithReady = true;
};
}
