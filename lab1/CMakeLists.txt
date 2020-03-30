cmake_minimum_required(VERSION 2.8)
project(lab1)

find_package(VTK REQUIRED)
include(${VTK_USE_FILE})

add_executable(lab1 src/main.cpp src/utils.h src/PlaneMoveCallback.h)

target_link_libraries(lab1 ${VTK_LIBRARIES})
