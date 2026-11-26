add_library(runtime SHARED
    "${runtime_source}/engine.cpp"
    "${runtime_source}/function/global/gContext.cpp"
    "${runtime_source}/core/meta/reflection/reflection.cpp"
    "${runtime_source}/core/meta/reflection/reflectionRegister.cpp")
add_library(X::runtime ALIAS runtime)
target_compile_features(runtime PUBLIC cxx_std_23)
target_include_directories(runtime PUBLIC "${runtime_source}" PRIVATE
    "${runtime_source}/core/base" "${runtime_source}/core/log"
    "${runtime_source}/core/meta" "${runtime_source}/function/global")
target_link_libraries(runtime PRIVATE spdlog::spdlog json11::headers)
# This runtime version constructs its log format strings at run time.
target_compile_definitions(runtime PRIVATE FMT_USE_CONSTEVAL=0)
set_target_properties(runtime PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS ON)

# This pinned release leaves the async worker running during Windows DLL unload.
# Use a build-tree header so a shared Git checkout stays intact.
file(READ "${runtime_source}/core/log/logSystem.h" legacy_log_header)
string(REPLACE "spdlog::drop_all();" "spdlog::shutdown();" legacy_log_header "${legacy_log_header}")
file(CONFIGURE OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/legacy-runtime/logSystem.h"
    CONTENT "${legacy_log_header}" @ONLY)
target_include_directories(runtime BEFORE PRIVATE "${CMAKE_CURRENT_BINARY_DIR}/legacy-runtime")
