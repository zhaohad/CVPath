cmake_minimum_required(VERSION 3.16)
project(039_FindingContoursInYourImage)

set(CMAKE_CXX_STANDARD 14)

set(PATH_OPENCV_HOME /home/zhaohad/bin/opencv/build)

set(OpenCV_DIR /home/zhaohad/bin/opencv/build)
set(CMAKE_CXX_FLAGS "-g")
find_package(OpenCV REQUIRED)
message("OpenCV library status:")
message("    version: ${OpenCV_VERSION}")
message("    headers: ${OpenCV_INCLUDE_DIRS}")
message("    libraries: ${OpenCV_LIBS}")

include_directories(${OpenCV_INCLUDE_DIRS})
aux_source_directory(. SRC_LIST)
add_executable(039_FindingContoursInYourImage ${SRC_LIST})
target_link_libraries(039_FindingContoursInYourImage ${OpenCV_LIBS})
