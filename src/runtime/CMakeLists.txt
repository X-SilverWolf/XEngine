
include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/core/base
        ${CMAKE_CURRENT_SOURCE_DIR}/core/log
        ${CMAKE_CURRENT_SOURCE_DIR}/function/global
        ${PROJ_TRD_DIR}/spdlog/include
)

build_shared_library_with_test(runtime spdlog::spdlog)

# setting the include directories, ensure can find System/Standard.h etc. header files
# target_include_directories(runtime
# PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
# PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
# )