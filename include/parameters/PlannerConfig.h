#pragma once
#include "parameters/Constants.h"
namespace atlas {
struct PlannerConfig {
  uint32_t binUnits = 80000;
  int16_t maxPwm = 240;
  int16_t offMapPwm = 110;
  int16_t fullTurnPwm = 90;
  uint8_t straightCurvature = 25;
  uint8_t brakePwmPerBin = 8;
  uint8_t lookaheadBins = 25;
  uint16_t minimumBins = 30;
  uint16_t resyncWindowBins = 25;

  uint16_t easyLostPerMille = 30;
  uint8_t slowdownPerLostPerMille = 1;
  uint8_t minConfidencePercent = 70;

  uint16_t failedRunLostMs = 1500;
  uint16_t stoppedWhileLostMs = 200;
  uint8_t completedMapPercent = 95;
  uint8_t dangerZoneBinsBefore = 10;
  uint8_t dangerZoneBinsAfter = 3;
  uint8_t dangerCurvatureBoost = 90;
  uint8_t curveSpeedStepPercent = 10;
  uint8_t minCurveSpeedPercent = 60;
};
}
