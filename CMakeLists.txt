cmake_minimum_required(VERSION 3.15)

set(XENGINE_VERSION 1.0.0)
project(XENGINE VERSION ${XENGINE_VERSION})

set(PROJECT_NAME_CAPITALIZED "XEngine")

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})


set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


set(PROJ_ROOT_DIR ${PROJECT_SOURCE_DIR})
set(PROJ_SRC_DIR ${PROJ_ROOT_DIR}/src)
set(PROJ_TRD_DIR ${PROJ_ROOT_DIR}/thirdParty)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

#get the hash value of the git repository
execute_process(
                COMMAND git log -1 --format=%h
                WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
                OUTPUT_VARIABLE GIT_HASH
                OUTPUT_STRIP_TRAILING_WHITESPACE
)
message(STATUS "GIT_HASH:${GIT_HASH}")

# pass the GIT_HASH to the source code
add_definitions(-DGIT_HASH="${GIT_HASH}")

# DMAI_API_SHARED is used to control the export, all platforms are defined
add_definitions(-DDMAI_API_SHARED)


option(BUILD_SHARED_LIBS "Build as shared libraries" ON)
option(ENABLE_LARGEFILE "Enable large file support" ON)
option(ENABLE_LOGGING "Enable logging system" ON)

#set(CMAKE_BUILD_TYPE Debug)

if(CMAKE_SYSTEM_NAME MATCHES "Windows")
  set(PROJ_ARCH "x64")
else ()
  set(PROJ_ARCH "x86")
  add_definitions(-DPLAT_LINUX)
endif ()

if(CMAKE_BUILD_TYPE STREQUAL Debug)
  set(PROJ_OUTPUT_DIR "${PROJECT_SOURCE_DIR}/build/build-${PROJ_ARCH}-Debug")
  if(${PROJ_ARCH} STREQUAL "x86")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -rdynamic")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -rdynamic")
  endif ()
else ()
  set(PROJ_OUTPUT_DIR "${PROJECT_SOURCE_DIR}/build/build-${PROJ_ARCH}-Release")
endif()

set(PROJ_BIN_DIR "${PROJ_OUTPUT_DIR}/bin")
set(PROJ_RLUGIN_DIR "${PROJ_OUTPUT_DIR}/lib/plugins")

if(${PROJ_ARCH} STREQUAL "x64")
  set(PROJ_LIB_DIR "${PROJ_OUTPUT_DIR}/bin")
else ()
  set(PROJ_LIB_DIR "${PROJ_OUTPUT_DIR}/lib")
endif ()

# add cmake templates
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

include(ManageThirdPartyLibrary)
include(Utility)

if(CMAKE_BUILD_TYPE STREQUAL Debug)
  add_definitions(-DPALT_DEBUG)
elseif(CMAKE_BUILD_TYPE STREQUAL Release)
else()
  set(CMAKE_BUILD_TYPE Release)
endif ()

if(NOT WIN32)
  # Position Independent Code is only needed/valid on ELF platforms (Linux, etc.)
  # and is not supported by MSVC/clang-cl on Windows, so guard it.
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
endif()

if(CMAKE_BUILD_TYPE STREQUAL Debug)
  if(MSVC)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /Od /Zi")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Od /Zi")
  else()
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0 -Wall -g -ggdb -Wno-psabi")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -Wall -g -ggdb -Wno-psabi")
  endif()
endif ()


INCLUDE_DIRECTORIES(
        ${CMAKE_CURRENT_SOURCE_DIR}
)

LINK_DIRECTORIES(

)

add_subdirectory(src)


if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/examples)
  add_subdirectory(examples)
endif()

if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/tests)
  add_subdirectory(tests)
endif()