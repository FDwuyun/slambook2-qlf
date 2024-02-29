find_package(Sophus REQUIRED)
include_directories(${Sophus_INCLUDE_DIRS})

find_package(Pangolin REQUIRED)
find_package(fmt REQUIRED)
set(FMT_LIBRARIES fmt::fmt)
if(fmt_FOUND)
    message("Found fmt: ${fmt_VERSION}")
    message("fmt include directories: ${fmt_INCLUDE_DIRS}")
    message("fmt libraries: ${FMT_LIBRARIES}")
else()
    message(FATAL_ERROR "fmt not found")
endif()


add_executable(joinMap joinMap.cpp)
target_link_libraries(joinMap ${OpenCV_LIBS} ${Pangolin_LIBRARIES} ${FMT_LIBRARIES})