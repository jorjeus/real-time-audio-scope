cmake_minimum_required (VERSION 2.6)


# set project anme
project (Spring)

# setup version numbers
set(VERSION_MAJOR 1)
set(VERSION_MINOR 0)
set(VERSION_PATCH 0)

set(CMAKE_CXX_STANDARD 14)
# add spring header path
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/spring/common)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/third_party/QCustomPlot)

# add the subdirectories
add_subdirectory(src/spring)
add_subdirectory(third_party/QCustomPlot)
