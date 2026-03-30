if(PROJ_ARCH MATCHES "x64" OR PROJ_ARCH MATCHES "win64")
    message(STATUS "Configuring for Windows x64")

    if(MSVC)
        set(SYSTEM_LIBS
                ws2_32
                mswsock
                advapi32
                user32
                kernel32
        )
    else()
        set(SYSTEM_LIBS
                mingwex
                ws2_32
                mswsock
                advapi32
                user32
                kernel32
        )
    endif()
    #set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_FLAGS} -lmingwex -lmsvcrt")

    # set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,--allow-multiple-definition")

else()
    message(STATUS "Configuring for Unix/Linux")

    set(SYSTEM_LIBS
            pthread
            stdc++fs
            stdc++
            m
            dl
            rt
    )
endif()

set(THIRD_PARTY_PREFIX "${PROJ_TRD_DIR}/${PROJ_ARCH}")
set(GTEST_LIBS gtest gmock)

option(ENABLE_QT "Enable Qt support" OFF)
option(ENABLE_GTEST "Enable Google Test" ON)
option(ENABLE_GFLAGS "Enable gflags library" OFF)
option(ENABLE_GLOG "Enable glog library" OFF)
option(BUILD_THIRD_PARTY_GTEST "Build gtest" ON)

if(CMAKE_SYSTEM_NAME MATCHES "Windows")
    message(STATUS "Windows platform detected")
    set(PLATFORM_DEPENDENT_LIBS "")

    if(ENABLE_QT)
        message(STATUS "Qt support enabled - remember to set QT5_DIR")
    endif()

    if(ENABLE_GTEST)
        message(STATUS "GTest enabled - remember to set GTEST_DIR")
    endif()

elseif(CMAKE_SYSTEM_NAME MATCHES "Linux")
    message(STATUS "Linux platform detected")
    set(PLATFORM_DEPENDENT_LIBS pthread dl)

    if(ENABLE_QT)
        message(STATUS "Qt support enabled - remember to set QT5_DIR")
    endif()

    if(ENABLE_GTEST)
        message(STATUS "GTest enabled - remember to set GTest_DIR")
    endif()

else()
    message(STATUS "Unsupported platform: ${CMAKE_SYSTEM_NAME}")
endif()

if(ENABLE_QT)
    find_package(Qt5 REQUIRED COMPONENTS
            Core
            Widgets
            Gui
            Charts
            PrintSupport
            OpenGL
            Xml
            Network
            UiTools
    )

    set(QT5_LIBS
            Qt5::Core
            Qt5::Widgets
            Qt5::Gui
            Qt5::Charts
            Qt5::PrintSupport
            Qt5::OpenGL
            Qt5::Xml
            Qt5::Network
            Qt5::UiTools
    )

    set(CMAKE_AUTOMOC ON)
    set(CMAKE_AUTORCC ON)
    set(CMAKE_AUTOUIC ON)

    message(STATUS "Qt5 support enabled")
endif()

#list(APPEND CMAKE_MODULE_PATH "${PROJ_TRD_DIR}/cmake")
#include(ThirdPartyBuild)

# CUDA Toolkit
find_package(CUDAToolkit REQUIRED)
message(STATUS "CUDA Toolkit found: ${CUDAToolkit_VERSION}")


# set(GTEST_DIR "${THIRD_PARTY_PREFIX}/GTest")
# list(APPEND CMAKE_PREFIX_PATH ${GTEST_DIR})
# find_package(GTest REQUIRED)

# set(OPENCV_DIR "${THIRD_PARTY_PREFIX}/OpenCV")
# list(APPEND CMAKE_PREFIX_PATH ${OPENCV_DIR})
# find_package(OpenCV REQUIRED)

#find_package(Python3 COMPONENTS Interpreter Development REQUIRED)


# add cmake templates
list(APPEND CMAKE_MODULE_PATH "${PROJ_TRD_DIR}/cmake")

#set(PYBIND11_DIR "${THIRD_PARTY_PREFIX}/pybind11")
#list(APPEND CMAKE_PREFIX_PATH ${PYBIND11_DIR})
#find_package(pybind11 REQUIRED)

#file(GLOB GTEST_BINARY "${GTEST_DIR}/bin/*")
#file(COPY ${GTEST_BINARY} DESTINATION "${EXECUTABLE_OUTPUT_PATH}/")

#set(GTEST_DIR "${THIRD_PARTY_PREFIX}/GTest")
#list(APPEND CMAKE_MODULE_PATH ${GTEST_DIR}/lib)
#find_package(GTest REQUIRED)
#link_directories(${GTEST_DIR}/lib)
#include_directories(${GTEST_DIR}/include)

function(check_libraries_exist LIB_LIST)
    if(NOT ${LIB_LIST})
        return()
    endif()

    foreach(LIB ${${LIB_LIST}})
        if(EXISTS "${LIB}" OR NOT LIB MATCHES ".*/.*")
            message(STATUS "Library ${LIB} - found")
        else()
            message(WARNING "Library ${LIB} - not found")
        endif()
    endforeach()
endfunction()


function(copy_directory_files SOURCE_DIR DEST_DIR)
    if(NOT SOURCE_DIR)
        message(FATAL_ERROR "copy_directory_files: missing source directory parameter")
    endif()

    if(NOT DEST_DIR)
        message(FATAL_ERROR "copy_directory_files: missing destination directory parameter")
    endif()

    if(NOT EXISTS ${SOURCE_DIR})
        message(WARNING "copy_directory_files: source directory does not exist: ${SOURCE_DIR}")
        return()
    endif()

    set(PATTERN "*")
    set(RECURSE FALSE)

    set(EXTRA_ARGS ${ARGN})
    list(LENGTH EXTRA_ARGS EXTRA_COUNT)

    if(EXTRA_COUNT GREATER 0)
        list(GET EXTRA_ARGS 0 FIRST_ARG)
        string(TOUPPER "${FIRST_ARG}" FIRST_ARG_UPPER)

        if(FIRST_ARG_UPPER STREQUAL "RECURSE")
            set(RECURSE TRUE)
            if(EXTRA_COUNT GREATER 1)
                set(PATTERN "${EXTRA_ARGS}")
                list(REMOVE_AT EXTRA_ARGS 0)
                string(REPLACE ";" " " PATTERN "${EXTRA_ARGS}")
            endif()
        else()
            set(PATTERN "${FIRST_ARG}")
            if(EXTRA_COUNT GREATER 1)
                list(GET EXTRA_ARGS 1 SECOND_ARG)
                string(TOUPPER "${SECOND_ARG}" SECOND_ARG_UPPER)
                if(SECOND_ARG_UPPER STREQUAL "RECURSE")
                    set(RECURSE TRUE)
                endif()
            endif()
        endif()
    endif()

    if(NOT EXISTS ${DEST_DIR})
        file(MAKE_DIRECTORY ${DEST_DIR})
        message(STATUS "Create directory: ${DEST_DIR}")
    endif()

    if(RECURSE)
        file(GLOB_RECURSE FILES_TO_COPY "${SOURCE_DIR}/${PATTERN}")
        message(STATUS "Recursive copy: ${SOURCE_DIR}/${PATTERN} -> ${DEST_DIR}")
    else()
        file(GLOB FILES_TO_COPY "${SOURCE_DIR}/${PATTERN}")
        message(STATUS "Copy: ${SOURCE_DIR}/${PATTERN} -> ${DEST_DIR}")
    endif()

    set(FILES_ONLY "")
    foreach(FILE_PATH ${FILES_TO_COPY})
        if(EXISTS ${FILE_PATH} AND NOT IS_DIRECTORY ${FILE_PATH})
            list(APPEND FILES_ONLY ${FILE_PATH})
        endif()
    endforeach()

    set(COPIED_COUNT 0)
    foreach(FILE_PATH ${FILES_ONLY})
        get_filename_component(FILE_NAME ${FILE_PATH} NAME)

        if(RECURSE)
            file(RELATIVE_PATH RELATIVE_PATH ${SOURCE_DIR} ${FILE_PATH})
            get_filename_component(RELATIVE_DIR ${RELATIVE_PATH} DIRECTORY)

            if(RELATIVE_DIR)
                set(TARGET_SUBDIR "${DEST_DIR}/${RELATIVE_DIR}")
                if(NOT EXISTS ${TARGET_SUBDIR})
                    file(MAKE_DIRECTORY ${TARGET_SUBDIR})
                endif()
                set(TARGET_PATH "${TARGET_SUBDIR}/${FILE_NAME}")
            else()
                set(TARGET_PATH "${DEST_DIR}/${FILE_NAME}")
            endif()
        else()
            set(TARGET_PATH "${DEST_DIR}/${FILE_NAME}")
        endif()

        add_custom_command(
                OUTPUT ${TARGET_PATH}
                COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "${FILE_PATH}"
                "${TARGET_PATH}"
                DEPENDS ${FILE_PATH}
                COMMENT "Copy: ${FILE_NAME}"
        )

        list(APPEND ALL_TARGETS ${TARGET_PATH})

        math(EXPR COPIED_COUNT "${COPIED_COUNT} + 1")
    endforeach()

    if(COPIED_COUNT EQUAL 0)
        message(STATUS "No matching files found")
        return()
    endif()

    if(NOT "${DEST_DIR}" MATCHES "^\\$<")
        string(MAKE_C_IDENTIFIER "copy_${SOURCE_DIR}_to_${DEST_DIR}" TARGET_NAME)

        add_custom_target(${TARGET_NAME} ALL
                DEPENDS ${ALL_TARGETS}
                COMMENT "Copy files from ${SOURCE_DIR} to ${DEST_DIR}"
        )
    endif()

    message(STATUS "Copied ${COPIED_COUNT} files")
endfunction()

