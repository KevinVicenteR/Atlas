#pragma once
#include "parameters/RobotConfig.h"
namespace atlas {
void applyUserSettings(RobotConfig& config);
RobotConfig makeConfig(RobotConfig profile);
RobotConfig makeFastConfig();
}
