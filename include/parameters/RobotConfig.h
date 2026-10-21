#pragma once
#include "parameters/SensorConfig.h"
#include "parameters/ControlConfig.h"
#include "parameters/SpeedConfig.h"
#include "parameters/ImpellerConfig.h"
#include "parameters/LostLineConfig.h"
#include "parameters/CornerConfig.h"
#include "parameters/AdaptiveConfig.h"
#include "parameters/PlannerConfig.h"
namespace atlas {
struct RobotConfig {
  SensorConfig sensors;
  ControlConfig control;
  SpeedConfig speed;
  ImpellerConfig impeller;
  LostLineConfig lostLine;
  CornerConfig corner;
  AdaptiveConfig adaptive;
  PlannerConfig planner;
  bool motorsEnabled = true;
};
}
