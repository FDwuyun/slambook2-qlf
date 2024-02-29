cmake_minimum_required(VERSION 3.2)
project(ch5)

# Release构建模式不会生成
# set(CMAKE_BUILD_TYPE "Release")
# 添加c++ 11标准支持
set(CMAKE_CXX_FLAGS "-std=c++11 -O2")

# Eigen
include_directories("/usr/include/eigen3")

# 寻找OpenCV库
find_package(OpenCV REQUIRED)
# message("OpenCV version: ${OpenCV_VERSION}")
# # OpenCV version: 3.2.0
# message("OpenCV include directories: ${OpenCV_INCLUDE_DIRS}")
# # OpenCV include directories: /usr/include;/usr/include/opencv
# message("OpenCV libraries: ${OpenCV_LIBS}")
# 添加头文件
include_directories(${OpenCV_INCLUDE_DIRS})

add_subdirectory(imageBasics)
add_subdirectory(stereo)
add_subdirectory(rgbd)
