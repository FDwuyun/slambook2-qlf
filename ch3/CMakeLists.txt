cmake_minimum_required(VERSION 3.22)
project(chapter3)

set(CMAKE_CXX_FLAGS "-std=c++11")

# 添加Eigen头文件
include_directories("/usr/include/eigen3")
# 加入各子工程
add_subdirectory(useEigen)
add_subdirectory(useGeometry)
add_subdirectory(visualizeGeometry)
add_subdirectory(examples)
