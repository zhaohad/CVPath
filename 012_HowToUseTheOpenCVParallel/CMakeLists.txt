cmake_minimum_required(VERSION 3.16)
project(012_HowToUseTheOpenCVParallel)

set(CMAKE_CXX_STANDARD 14)

set(PATH_OPENCV_HOME /home/zhaohad/OpenCV)

set(OpenCV_DIR ~/bin/opencv/build_opencv)
FIND_PACKAGE(OpenCV REQUIRED)
message(STATUS "OpenCV library status:")
message(STATUS "    version: ${OpenCV_VERSION}")
message(STATUS "    headers: ${OpenCV_INCLUDE_DIRS}")
message(STATUS "    libraries: ${OpenCV_LIBS}")

INCLUDE_DIRECTORIES({OpenCV_INCLUDE_DIRS})
AUX_SOURCE_DIRECTORY(. SRC_LIST)
ADD_EXECUTABLE(012_HowToUseTheOpenCVParallel ${SRC_LIST})
TARGET_LINK_LIBRARIES(012_HowToUseTheOpenCVParallel ${OpenCV_LIBS})