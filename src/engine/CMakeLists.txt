if(CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
    cmake_minimum_required(VERSION 3.28)
    project(XEngineApp VERSION 1.0.0 LANGUAGES CXX)
    include("${CMAKE_CURRENT_LIST_DIR}/cmake/Standalone.cmake")
    x_enable_business_releases()
    include("${CMAKE_CURRENT_LIST_DIR}/cmake/Dependencies.cmake")
    cmake_path(GET CMAKE_CURRENT_SOURCE_DIR PARENT_PATH project_sources)
    set(runtime_source "${project_sources}/runtime")
    if(EXISTS "${runtime_source}/cmake/RuntimeTarget.cmake" AND EXISTS "${runtime_source}/engine.h")
        add_subdirectory("${runtime_source}" "${CMAKE_CURRENT_BINARY_DIR}/runtime")
    else()
        # The application's private runtime ships in the XEngine source repository.
        include(FetchContent)
        FetchContent_Declare(xengine_runtime
            GIT_REPOSITORY https://github.com/X-SilverWolf/XEngine.git
            GIT_TAG 2bef0c71d17ee8d70b16312c3acd11dc7a31128e
            GIT_SUBMODULES ""
            SOURCE_SUBDIR no-cmake-subproject)
        FetchContent_MakeAvailable(xengine_runtime)
        set(runtime_source "${xengine_runtime_SOURCE_DIR}/src/runtime")
        include("${CMAKE_CURRENT_LIST_DIR}/cmake/RuntimeTarget.cmake")
    endif()
endif()

add_executable(engine "${CMAKE_CURRENT_LIST_DIR}/main.cpp")
target_compile_features(engine PRIVATE cxx_std_23)
target_link_libraries(engine PRIVATE X::runtime)
