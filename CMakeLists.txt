if(CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
    cmake_minimum_required(VERSION 3.28)
    project(XEngine VERSION 1.0.0 LANGUAGES CXX)
    include("${CMAKE_CURRENT_LIST_DIR}/src/runtime/cmake/Standalone.cmake")
    x_enable_business_releases()
    include("${CMAKE_CURRENT_LIST_DIR}/src/runtime/cmake/Dependencies.cmake")
endif()

add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/src")
