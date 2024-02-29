find_package(Pangolin REQUIRED)
include_directories(${Pangolin_INCLUDE_DIRS})

# find_package(fmt REQUIRED)
# set(FMT_LIBRARIES fmt::fmt)
# if(fmt_FOUND)
#     message("Found fmt: ${fmt_VERSION}")
#     message("fmt include directories: ${fmt_INCLUDE_DIRS}")
#     message("fmt libraries: ${FMT_LIBRARIES}")
# else()
#     message(FATAL_ERROR "fmt not found")
# endif()


add_executable(stereoVision stereoVision.cpp)
target_link_libraries(stereoVision ${OpenCV_LIBS} ${Pangolin_LIBRARIES}  ${FMT_LIBRARIES})