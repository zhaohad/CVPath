cmake_minimum_required(VERSION 3.16)
project(002_StartWithImages)

set(CMAKE_CXX_STANDARD 14)

set(OpenCV_DIR /home/zhaohad/OpenCV/build)
FIND_PACKAGE(OpenCV REQUIRED)

AUX_SOURCE_DIRECTORY(. SRC_LIST)

add_executable(002_StartWithImages ${SRC_LIST})

TARGET_LINK_LIBRARIES(002_StartWithImages ${OpenCV_LIBS})