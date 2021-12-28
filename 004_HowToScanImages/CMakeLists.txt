cmake_minimum_required(VERSION 3.16)
project(004_HowToScanImages)

set(CMAKE_CXX_STANDARD 14)

set(OpenCV_DIR /home/zhaohad/OpenCV/build)
find_package(OpenCV REQUIRED)

aux_source_directory(. SRC_LIST)

add_executable(004_HowToScanImages ${SRC_LIST})
target_link_libraries(004_HowToScanImages ${OpenCV_LIBS})