project(engine)


set(SRC_DIRS
    "${CMAKE_CURRENT_SOURCE_DIR}/"
)


set(PROJECT_SOURCES)
foreach(dir ${SRC_DIRS})
    file(GLOB_RECURSE dir_sources
            "${dir}/*.cpp"
            "${dir}/*.cxx"
            "${dir}/*.cc"
    )
    list(APPEND PROJECT_SOURCES ${dir_sources})
endforeach()

set(PROJECT_HEADERS)
foreach(dir ${SRC_DIRS})
    file(GLOB_RECURSE dir_headers
            "${dir}/*.h"
            "${dir}/*.hpp"
            "${dir}/*.hxx"
    )
    list(APPEND PROJECT_HEADERS ${dir_headers})
endforeach()

set(EXECUTABLE_OUTPUT_PATH ${PROJ_BIN_DIR})

if(PROJ_ARCH MATCHES "x64")
    add_executable(${PROJECT_NAME}
            ${PROJECT_SOURCES}
            ${PROJECT_HEADERS}
    )
else()
    add_executable(${PROJECT_NAME}
            ${PROJECT_SOURCES}
            ${PROJECT_HEADERS}
    )
endif()


if(SYSTEM_LIBS)
    target_link_libraries(${PROJECT_NAME} PRIVATE ${SYSTEM_LIBS} runtime)
endif()

target_include_directories(${PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${PROJ_SRC_DIR}/runtime
)
