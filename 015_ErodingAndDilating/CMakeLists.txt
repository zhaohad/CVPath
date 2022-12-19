cmake_minimum_required(VERSION 3.16)
project(015_ErodingAndDilating)

set(CMAKE_CXX_STANDARD 14)

set(PATH_OPENCV_HOME /home/zhaohad/OpenCV)

set(OpenCV_DIR /home/zhaohad/OpenCV/build)
find_package(OpenCV REQUIRED)
message("OpenCV library status:")
message("    version: ${OpenCV_VERSION}")
message("    headers: ${OpenCV_INCLUDE_DIRS}")
message("    libraries: ${OpenCV_LIBS}")


include_directories(${OpenCV_INCLUDE_DIRS})
aux_source_directory(. SRC_LIST)
add_executable(015_ErodingAndDilating ${SRC_LIST})
target_link_libraries(015_ErodingAndDilating ${OpenCV_LIBS})