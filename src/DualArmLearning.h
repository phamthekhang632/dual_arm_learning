#pragma once

#include <mc_control/mc_controller.h>

#include "api.h"

struct DualArmLearning_DLLAPI DualArmLearning : public mc_control::MCController
{
  DualArmLearning(mc_rbdyn::RobotModulePtr rm, double dt, const mc_rtc::Configuration & config);
  bool run() override;
  void reset(const mc_control::ControllerResetData & reset_data) override;

private:
  mc_rbdyn::RobotModule attachTool(std::string robot_name,
                                   std::string tool_name,
                                   std::string robot_body,
                                   std::string tool_body,
                                   
                                   std::string attach_name = "");

  std::shared_ptr<mc_tasks::PostureTask> ur_posture_task_;
  std::shared_ptr<mc_tasks::PostureTask> kinova_posture_task_;

  // std::shared_ptr<mc_tasks::PostureTask> ur10PostureTask;

  // std::map<std::string, std::vector<double>> ur7ePose = {{"shoulder_pan_joint", {25 * M_PI / 180}},
  //                                                        {"shoulder_lift_joint", {-M_PI / 2}},
  //                                                        {"elbow_joint", {-M_PI / 2}},
  //                                                        {"wrist_1_joint", {0.0}},
  //                                                        {"wrist_2_joint", {M_PI / 2}},
  //                                                        {"wrist_3_joint", {0.0}}};
  // std::map<std::string, std::vector<double>> ur10Pose = {
  //     {"shoulder_pan_joint", {0.0}}, {"shoulder_lift_joint", {-M_PI / 2}}, {"elbow_joint", {-M_PI / 2}},
  //     {"wrist_1_joint", {0.0}},      {"wrist_2_joint", {M_PI / 2}},        {"wrist_3_joint", {0.0}}};

  // std::map<std::string, std::vector<double>> gripperOpen = {{"finger_joint", {0.0}}};
  // std::map<std::string, std::vector<double>> gripperClose = {{"finger_joint", {0.725}}};
  // std::shared_ptr<mc_tasks::PostureTask> gripperPostureTask_;
};
