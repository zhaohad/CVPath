cmake_minimum_required(VERSION 3.16)
project(013_VectorizingYourCodeUsingUniversalIntrinsics)

set(CMAKE_CXX_STANDARD  14)

set(PATH_OPENCV_HOME /home/zhaohad/OpenCV)

set(OpenCV_DIR /home/zhaohad/OpenCV/build)
find_package(OpenCV REQUIRED)
message(STATUS "OpenCV library status:")
message(STATUS "    version: ${OpenCV_VERSION}")
message(STATUS "    headers: ${OpenCV_INCLUDE_DIRS}")
message(STATUS "    libraries: ${OpenCV_LIBS}")

include_directories(${OpenCV_INCLUDE_DIRS})
aux_source_directory(. SRC_LIST)
add_executable(013_VectorizingYourCodeUsingUniversalIntrinsics ${SRC_LIST})
target_link_libraries(013_VectorizingYourCodeUsingUniversalIntrinsics ${OpenCV_LIBS})