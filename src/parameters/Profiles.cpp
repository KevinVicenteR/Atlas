#include "parameters/Profiles.h"

namespace atlas {

RobotConfig safeProfile() { return RobotConfig(); }

RobotConfig fastProfile() {
  RobotConfig config;
  config.control.kp = 0.008f;
  config.control.kd = 1.0f;
  config.control.derivativeFilterShift = 1;
  config.control.curveSlowdownPercent = 0;
  config.lostLine.outerMotorPwm = 201;

  config.planner.maxPwm = 255;
  config.planner.fullTurnPwm = 255;
  config.planner.straightCurvature = 26;
  config.planner.brakePwmPerBin = 5;
  config.planner.lookaheadBins = 18;
  return config;
}

}
