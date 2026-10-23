#include "aplicacion/AtlasApp.h"
#include "parametros/AppParameters.h"

namespace atlas {

AtlasApp::AtlasApp(IClock& clock, IOperatorInput& input, IIndicators& indicators, LineSensorArray& sensors,
                   IDrivetrain& drivetrain, LineFollower& follower, const RobotConfig& config,
                   const AppOptions& options)
    : clock_(clock),
      input_(input),
      leds_(indicators, clock),
      sensors_(sensors),
      drivetrain_(drivetrain),
      follower_(follower),
      config_(config),
      diagnostics_(options.diagnostics),
      fastConfig_(options.fastConfig),
      thirdConfig_(options.thirdConfig),
      storage_(options.storage),
      trackMap_(options.trackMap),
      cruisePwm_(config.speed.basePwm) {
  follower_.attachTrackMap(trackMap_);
}

void AtlasApp::begin() {
  leds_.bootAnimation();

  if (diagnostics_ != nullptr && anyButton()) {
    leds_.confirm(500, 1);
    diagnostics_->run();
  }
  loadSavedSpeed();
  state_ = loadSavedCalibration() ? AppState::Ready : AppState::WaitCalibration;
}

void AtlasApp::loadSavedSpeed() {
  if (storage_ == nullptr) return;
  int16_t saved = 0;
  if (!SpeedSettingStore(*storage_).load(&saved)) return;
  if (saved >= config_.speed.minPwm && saved <= config_.speed.maxPwm) cruisePwm_ = saved;
}

void AtlasApp::saveSpeed() {
  if (storage_ != nullptr) SpeedSettingStore(*storage_).save(cruisePwm_);
}

bool AtlasApp::loadSavedCalibration() {
  if (storage_ == nullptr) return false;
  if (!CalibrationStore(*storage_).load(sensors_) || !sensors_.isCalibrationValid()) {
    sensors_.resetCalibration();
    return false;
  }
  if (trackMap_ != nullptr && !TrackMapStore(*storage_).load(*trackMap_)) trackMap_->clear();
  leds_.blink(Led::Led2, kUiBlinkMs);
  leds_.blink(Led::Led2, kUiBlinkMs);
  updateReadyIndicator();
  return true;
}

void AtlasApp::tick() {
  switch (state_) {
    case AppState::Boot:
      begin();
      break;
    case AppState::WaitCalibration:
      waitCalibration();
      break;
    case AppState::Calibrating:
      calibrate();
      break;
    case AppState::Ready:
      prepareToRun();
      break;
    case AppState::Running:
      run();
      break;
  }
}

void AtlasApp::waitCalibration() {
  if (anyButton()) startCalibration();
}

void AtlasApp::forgetTrackMap() {
  if (trackMap_ == nullptr) return;
  trackMap_->clear();
  if (storage_ != nullptr) TrackMapStore(*storage_).erase();
}

void AtlasApp::startCalibration() {
  drivetrain_.impeller().setPwm(0);
  turbine_.stop();
  rounds_.reset();
  forgetTrackMap();
  leds_.blink(Led::Led2, kUiBlinkMs);
  sensors_.resetCalibration();
  state_ = AppState::Calibrating;
}

void AtlasApp::calibrate() {
  if (anyButton()) {
    finishCalibration();
    return;
  }

  const bool black = sensors_.lineColor() == LineColor::Black;
  leds_.set(Led::Led0, black && calibrationBlink_);
  leds_.set(Led::Led1, black && calibrationBlink_);
  leds_.set(Led::Led2, !black && calibrationBlink_);
  calibrationBlink_ = !calibrationBlink_;

  sensors_.collectCalibrationSamples();
}

void AtlasApp::finishCalibration() {
  sensors_.finishCalibration();
  leds_.setAll(false);
  clock_.delayMs(kUiBlinkMs);

  if (!sensors_.isCalibrationValid()) {
    leds_.calibrationError();
    state_ = AppState::WaitCalibration;
    return;
  }

  leds_.confirm(kConfirmHalfPeriodMs, 2);
  if (sensors_.calibratedSensorCount() < kSensorCount) leds_.damagedSensorsWarning();
  if (storage_ != nullptr) CalibrationStore(*storage_).save(sensors_);
  updateReadyIndicator();
  clock_.delayMs(kUiBlinkMs);
  state_ = AppState::Ready;
}

void AtlasApp::updateReadyIndicator() {
  if (!hasTrackMap()) {
    leds_.showCalibrated();
    return;
  }
  const bool phase = (clock_.millis() / kFastIndicatorHalfPeriodMs) % 2;
  leds_.set(Led::Led0, phase);
  leds_.set(Led::Led1, !phase);
}

}
