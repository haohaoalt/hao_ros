cmake_minimum_required(VERSION 2.8.3)
project(hw3-2)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_srvs
)
catkin_package()

include_directories(
  ${catkin_INCLUDE_DIRS}
)

add_executable(spawn_client src/spawn_client.cpp)
target_link_libraries(spawn_client ${catkin_LIBRARIES})


