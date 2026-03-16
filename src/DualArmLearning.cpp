#include "DualArmLearning.h"

DualArmLearning::DualArmLearning(mc_rbdyn::RobotModulePtr rm, double dt, const mc_rtc::Configuration & config)
: mc_control::MCController(rm, dt)
{
  solver().addConstraintSet(contactConstraint);
  solver().addConstraintSet(kinematicsConstraint);
  solver().addTask(postureTask);
  solver().setContacts({{}});

  mc_rtc::log::success("DualArmLearning init done ");
}

bool DualArmLearning::run()
{
  return mc_control::MCController::run();
}

void DualArmLearning::reset(const mc_control::ControllerResetData & reset_data)
{
  mc_control::MCController::reset(reset_data);
}

CONTROLLER_CONSTRUCTOR("DualArmLearning", DualArmLearning)
