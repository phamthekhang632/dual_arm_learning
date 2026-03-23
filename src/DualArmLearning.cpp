#include "DualArmLearning.h"

#include <mc_rbdyn/RobotLoader.h>

DualArmLearning::DualArmLearning(mc_rbdyn::RobotModulePtr rm, double dt, const mc_rtc::Configuration & config)
: mc_control::MCController({rm, mc_rbdyn::RobotLoader::get_robot_module("Kinova")}, dt)
{
  solver().addConstraintSet(contactConstraint);
  solver().addConstraintSet(kinematicsConstraint);
  // postureTask->setGains(0.5, 1.4);
  // postureTask->weight(1);
  // solver().addTask(postureTask);
  solver().setContacts({{}});

  // double iDist = 0.1;
  // double sDist = 0.05;
  // addCollisions("ur5e", "ur10", {{"*", "*", iDist, sDist, 0}});

  mc_rtc::log::success("DualArmLearning init done ");
}

bool DualArmLearning::run()
{
  return mc_control::MCController::run();
}

void DualArmLearning::reset(const mc_control::ControllerResetData & reset_data)
{
  mc_control::MCController::reset(reset_data);

  auto robot_with_gripper = attachTool("ur5e", "robotiq_arg85", "wrist_3_link", "robotiq_85_base_link", "gripper");
  loadRobot(robot_with_gripper, robot_with_gripper.name);
  gui()->removeElement({"Robots"}, robot().name());
  robots().robot(2).posW(sva::PTransformd(Eigen::Vector3d(0, 0.5, 0)));
  ur_posture_task_ = std::make_shared<mc_tasks::PostureTask>(solver(), robots().robotIndex(robot_with_gripper.name));
  solver().addTask(ur_posture_task_);

  auto kinova_with_gripper = attachTool("kinova_default", "robotiq_arg85", "bracelet_link", "robotiq_85_base_link", "gripper");
  loadRobot(kinova_with_gripper, kinova_with_gripper.name);
  gui()->removeElement({"Robots"}, "kinova_default");
  robots().robot(3).posW(sva::PTransformd(Eigen::Vector3d(0, -0.5, 0)));
  kinova_posture_task_ = std::make_shared<mc_tasks::PostureTask>(solver(), robots().robotIndex(kinova_with_gripper.name));
  solver().addTask(kinova_posture_task_);
}

CONTROLLER_CONSTRUCTOR("DualArmLearning", DualArmLearning)

mc_rbdyn::RobotModule DualArmLearning::attachTool(std::string robot_name,
                                                  std::string tool_name,
                                                  std::string robot_body,
                                                  std::string tool_body,
                                                  std::string attach_name)
{
  auto robot_module = robot(robot_name).module();
  auto connect_rm = mc_rbdyn::RobotLoader::get_robot_module(tool_name);
  mc_rtc::log::info("Connecting robot module {} to robot {}", tool_name, robot_name);
  // Connect two robot modules
  auto connect = robot_module.connect(
      *connect_rm, robot_body, tool_body, "",
      mc_rbdyn::RobotModule::ConnectionParameters{}.X_other_connection(sva::RotZ(mc_rtc::constants::PI)));

  connect.name = robot_name + "_" + ((!attach_name.empty()) ? attach_name : tool_name);

  mc_rtc::log::info("Robot new name: {}", connect.name);

  return connect;
}
