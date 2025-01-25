cmake_minimum_required(VERSION 3.22.1)
project(traineesensoriamento)

find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(traineesensoriamento src/bsb.cpp)

target_link_libraries(traineesensoriamento ${OpenCV_LIBS})