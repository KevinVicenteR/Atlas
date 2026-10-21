#pragma once
#include "parameters/Constants.h"
namespace atlas {
struct AdaptiveConfig {

  bool autoDamping = true;
  int16_t oscillationAmplitude = 700;
  uint16_t oscillationWindowMs = 250;
  uint8_t oscillationCrossings = 4;
  uint8_t minGainPercent = 52;
  uint8_t gainStepDownPercent = 10;
  uint16_t gainRecoverMs = 80;

  bool speedGovernor = true;
  uint8_t minSpeedPercent = 60;
  uint8_t speedDropOnLoss = 6;
  uint8_t speedDropOnOscillation = 4;
  uint16_t speedRecoverMs = 60;
};
}
