#pragma once

#include <stdint.h>

#include "parametros/Config.h"
#include "interfaces/Hal.h"
#include "control/LatencyPredictor.h"
#include "sensores/LineSensorArray.h"
#include "control/OscillationGuard.h"
#include "control/PdController.h"
#include "utilidades/Ramp.h"
#include "turbina/TurbineControl.h"
#include "control/SpeedGovernor.h"
#include "aprendizaje/SpeedPlanner.h"
#include "aprendizaje/TrackMap.h"

namespace atlas {

struct MotorCommand {
  int16_t left = 0;
  int16_t right = 0;
  int16_t impeller = 0;
};

enum class Side : uint8_t { Left, Right };

enum class RunMode : uint8_t { Plain, Mapping, MapGuided };

class LineFollower {
 public:
  LineFollower(LineSensorArray& sensors, IDrivetrain& drivetrain, const RobotConfig& config);

  void useConfig(const RobotConfig& config);
  void attachTrackMap(TrackMap* map) { map_ = map; }
  void start(int16_t cruisePwm, uint32_t nowMs, RunMode mode = RunMode::Plain,
             int16_t initialImpellerPwm = 0);

  bool finishMapping();

  bool runFailed() const;
  uint32_t longestLostMs() const { return longestLostMs_; }
  uint16_t lostPerMille() const { return runTicks_ ? static_cast<uint16_t>(runLostTicks_ * 1000 / runTicks_) : 0; }

  bool correctMapAfterFailedRun();

  uint16_t failureBin() const { return failureBin_; }
  RunMode mode() const { return mode_; }
  uint16_t currentBin() const;

  uint16_t mapBin() const;
  void requestStop(uint32_t nowMs);
  void update(uint32_t nowMs);

  bool isRunning() const { return running_; }
  bool isStopping() const { return stopping_; }
  bool isBridging() const { return bridging_; }
  bool isRecovering() const { return recovering_; }
  const MotorCommand& lastCommand() const { return command_; }
  const LineReading& lastReading() const { return reading_; }
  uint8_t gainPercent() const { return guard_.gainPercent(); }
  uint8_t speedPercent() const { return governor_.speedPercent(); }

  const int8_t* neuralInputs() const { return neuralInputs_; }
  const uint8_t* situationWeights() const { return situationWeights_; }

  const int8_t* derivativeInputs() const { return derivativeInputs_; }
  int32_t classicDerivative() const { return pd_.filteredDelta(); }
  uint32_t controlCycles() const { return runTicks_; }

 private:
  int16_t currentVelocity(uint32_t nowMs) const;
  void scaleCrossingHoldToSpeed(int16_t velocity);
  MotorCommand followLine(int16_t velocity, uint32_t nowMs);
  int16_t slowDownForCurve(int16_t velocity, int32_t error) const;
  void detectCorner(int32_t error, uint32_t nowMs);
  uint8_t cornerSpeedPercent(uint32_t nowMs) const;
  int16_t scaleForCorner(int16_t pwm, uint32_t nowMs) const;
  MotorCommand recoverLine(uint32_t nowMs) const;
  bool isCrossingGap(uint32_t nowMs) const;
  MotorCommand bridgeGap(int16_t velocity) const;
  void rememberLastSide();
  void trackStraightRun(int32_t error, uint32_t nowMs);
  bool looksStraight(int32_t error, int16_t tolerance) const;
  int16_t clampWheel(int16_t pwm) const;
  void apply(const MotorCommand& command);
  int16_t compensateDeadband(int16_t pwm) const;
  int16_t guidedVelocity(int16_t velocity) const;

  uint8_t curvatureAhead() const;
  void rememberError(int16_t error, int16_t velocity);
  int32_t neuralDerivative() const;
  void trackDistance();
  void onGapEntered();
  void recordCurvature();
  void trackLineLoss(uint32_t nowMs);
  void noteHowRunEnded(uint32_t nowMs);

  LineSensorArray& sensors_;
  IDrivetrain& drivetrain_;
  const RobotConfig* config_;
  PdController pd_;
  LatencyPredictor predictor_;
  OscillationGuard guard_;
  SpeedGovernor governor_;
  SpeedPlanner planner_;
  TrackMap* map_ = nullptr;
  RunMode mode_ = RunMode::Plain;
  uint32_t distanceUnits_ = 0;
  uint32_t mappingTicks_ = 0;
  uint32_t mappingLostTicks_ = 0;
  uint32_t runTicks_ = 0;
  uint32_t runLostTicks_ = 0;
  uint32_t lostSinceMs_ = 0;
  uint32_t longestLostMs_ = 0;
  uint16_t lostStartBin_ = 0;
  uint16_t failureBin_ = 0;
  bool stoppedWhileLost_ = false;
  bool stoppedIncomplete_ = false;
  bool bridging_ = false;
  bool bridgedOnce_ = false;
  bool recovering_ = false;

  LinearRamp velocityRamp_;
  TurbineControl turbine_;
  LinearRamp brakeRamp_;

  uint32_t startMs_ = 0;
  bool running_ = false;
  bool stopping_ = false;
  uint32_t lastOnLineMs_ = 0;
  uint32_t lastBridgeMs_ = 0;
  uint32_t centeredSinceMs_ = 0;
  uint32_t lastCornerMs_ = 0;
  bool cornerSeen_ = false;
  bool centered_ = false;
  Side lastSide_ = Side::Left;

  int32_t lastError_ = 0;
  uint32_t reacquiredMs_ = 0;
  int8_t neuralInputs_[8] = {};
  static constexpr uint8_t kErrorHistory = 17;
  int16_t errorHistory_[kErrorHistory] = {};
  uint8_t historyCount_ = 0;
  int8_t derivativeInputs_[7] = {};
  uint8_t situationWeights_[4] = {};
  LineReading reading_;
  MotorCommand command_;
};

}
