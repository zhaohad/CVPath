cmake_minimum_required(VERSION 3.16)
project(008_BasicDrawing)

set(CMAKE_CXX_STANDARD 14)

set(OpenCV_DIR /home/zhaohad/OpenCV/build)

find_package(OpenCV REQUIRED)

aux_source_directory(. SRC_LIST)

add_executable(008_BasicDrawing main.cpp)

target_link_libraries(008_BasicDrawing ${OpenCV_LIBS})