option(USE_UBUNTU_20 "Set to ON if you are using Ubuntu 20.04" OFF)
if(USE_UBUNTU_20)
    message("You are using Ubuntu 20.04, fmt::fmt will be linked")
    find_package(fmt REQUIRED)
    set(FMT_LIBRARIES fmt::fmt)
endif()

# 安装fmt包,参考链接 https://blog.csdn.net/CSSDCC/article/details/121854773
find_package(fmt REQUIRED)
set(FMT_LIBRARIES fmt::fmt)
if(fmt_FOUND)
    message("Found fmt: ${fmt_VERSION}")
    message("fmt include directories: ${fmt_INCLUDE_DIRS}")
    message("fmt libraries: ${FMT_LIBRARIES}")
else()
    message(FATAL_ERROR "fmt not found")
endif()


find_package(Pangolin REQUIRED)
include_directories(${Pangolin_INCLUDE_DIRS})
add_executable(trajectoryError trajectoryError.cpp)
target_link_libraries(trajectoryError ${Pangolin_LIBRARIES} ${FMT_LIBRARIES})
