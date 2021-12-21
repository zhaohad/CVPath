cmake_minimum_required(VERSION 3.16)
project(1_HelloCV)

set(CMAKE_CXX_STANDARD 14)

set(PATH_OPENCV_HOME /home/zhaohad/OpenCV)

#include_directories(
#        ${PATH_OPENCV_HOME}/opencv-master/modules/core/include
#        ${PATH_OPENCV_HOME}/opencv-master/modules/imgcodecs/include
#        ${PATH_OPENCV_HOME}/opencv-master/modules/highgui/include
#        ${PATH_OPENCV_HOME}/opencv-master/modules/videoio/include
#        ${PATH_OPENCV_HOME}/build)

set(OpenCV_DIR /home/zhaohad/OpenCV/build)
FIND_PACKAGE(OpenCV REQUIRED)
message(STATUS "OpenCV library status:")
message(STATUS "    version: 	${OpenCV_VERSION}")
message(STATUS "    headers: 	${OpenCV_INCLUDE_DIRS}")
message(STATUS "    libraries: 	${OpenCV_LIBS}")
INCLUDE_DIRECTORIES({OpenCV_INCLUDE_DIRS})
AUX_SOURCE_DIRECTORY(. SRC_LIST)
ADD_EXECUTABLE(1_HelloCV ${SRC_LIST})
TARGET_LINK_LIBRARIES(1_HelloCV ${OpenCV_LIBS})

#link_directories(${PATH_OPENCV_HOME}/build/lib) #添加动态连接库的路径

#add_executable(1_HelloCV main.cpp)

#target_link_libraries(1_HelloCV -lopencv_core -lopencv_highgui) #添加libmxnet.so