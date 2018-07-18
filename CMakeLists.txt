cmake_minimum_required(VERSION 2.8.3)
project(save_image)

set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_CXX_FLAGS "-std=c++11 -march=native -O3")

find_package(catkin REQUIRED COMPONENTS
  cv_bridge
  image_transport
  roscpp
  sensor_msgs
)
include_directories(${catkin_INCLUDE_DIRS})


set(OpenCV_DIR /home/jh/opencv-3.2.0/build)
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

set(THIRD_PARTY_LIBS
        ${OpenCV_LIBS}
        ${catkin_LIBRARIES}
        )
include_directories(${PROJECT_SOURCE_DIR}/include )

catkin_package()

add_executable(save_node 
src/node.cpp)

target_link_libraries(save_node ${THIRD_PARTY_LIBS})



