if(CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
    cmake_minimum_required(VERSION 3.28)
    project(XEngineEditor VERSION 1.0.0 LANGUAGES CXX)
endif()

# The editor has no compiled sources yet.
add_library(editor INTERFACE)
