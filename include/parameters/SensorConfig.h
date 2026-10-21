#pragma once
#include "parameters/Constants.h"
namespace atlas {
struct SensorConfig {

  LineColor lineColor = LineColor::Black;
  uint8_t thresholdPercent = 50;
  uint8_t averageSamples = 8;
  uint8_t collectorSamples = 10;

  uint8_t minCalibrationSpan = 40;

  uint8_t requiredCalibratedSensors = kSensorCount - 2;

  bool trackNearestCluster = true;

  uint8_t maxLineWidthSensors = 3;

  uint16_t maxPositionJump = 1000;

  uint8_t reacquireFreeReads = 40;

  uint16_t maxHeldReads = 150;
  int16_t heldReadsReferencePwm = 250;
};
}
