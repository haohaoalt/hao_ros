cmake_minimum_required(VERSION 2.8.3)
project(hw3-1)

find_package(catkin REQUIRED COMPONENTS
  geometry_msgs
  roscpp
)

catkin_package( )

include_directories(

  ${catkin_INCLUDE_DIRS}
)


add_executable(vel_pose src/vel_pose.cpp)
target_link_libraries(vel_pose ${catkin_LIBRARIES})



