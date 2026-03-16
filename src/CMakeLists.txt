set(controller_SRC
  DualArmLearning.cpp
)

set(controller_HDR
  DualArmLearning.h
)

add_controller(${PROJECT_NAME} ${controller_SRC} ${controller_HDR})
set_target_properties(${PROJECT_NAME} PROPERTIES COMPILE_FLAGS "-DDualArmLearning_EXPORTS")

