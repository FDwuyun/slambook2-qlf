cmake_minimum_required(VERSION 3.16)
project(ch6)

# set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_FLAGS "-std=c++14 -O3")

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

# OpenCV
find_package(OpenCV REQUIRED)
# message("OpenCV version: ${OpenCV_VERSION}")
# message("OpenCV include directories: ${OpenCV_INCLUDE_DIRS}")
# message("OpenCV libraries: ${OpenCV_LIBS}")
## OpenCV version: 4.2.0
## OpenCV include directories: /usr/include/opencv4

include_directories(${OpenCV_INCLUDE_DIRS})

# Ceres
find_package(Ceres REQUIRED)
if(Ceres_FOUND)
    message("Found Ceres Solver: ${Ceres_VERSION}")
    message("Ceres Solver include directories: ${CERES_INCLUDE_DIRS}")
    message("Ceres Solver libraries: ${Ceres_LIBRARIES}")
    ## Found Ceres Solver: 2.0.0
    ## 
else()
    message(FATAL_ERROR "Ceres Solver not found")
endif()
include_directories(${CERES_INCLUDE_DIRS})

# g2o
# find_package(G2O REQUIRED)
# include_directories(${G2O_INCLUDE_DIRS})

# Eigen
include_directories("/usr/include/eigen3")


add_executable(gaussNewton gaussNewton.cpp)
target_link_libraries(gaussNewton ${OpenCV_LIBS})

add_executable(ceresCurveFitting ceresCurveFitting.cpp)
target_link_libraries(ceresCurveFitting ${OpenCV_LIBS} ${CERES_LIBRARIES})

add_executable(g2oCurveFitting g2oCurveFitting.cpp)
target_link_libraries(g2oCurveFitting ${OpenCV_LIBS} ${G2O_CORE_LIBRARY} ${G2O_STUFF_LIBRARY})
