# XEngine

Configure this checkout with CMake 3.28 or later. The runtime links spdlog for asynchronous logging and includes json11's header to declare reflection callbacks. In standalone mode it obtains spdlog 1.17.0 and the json11 1.0.0 headers from `X_RELEASE_BASE_URL` and uses the local `extern/` directory. In XGitRoot, the parent supplies their targets from XThirdParty. [Runtime dependencies](src/runtime/cmake/Dependencies.cmake)

使用 CMake 3.28 或更高版本配置本工程。运行库链接 spdlog 来处理异步日志，通过 json11 头文件声明反射回调。独立构建从 `X_RELEASE_BASE_URL` 获取 spdlog 1.17.0 与 json11 1.0.0 头文件，使用本工程内的 `extern/` 目录。在 XGitRoot 中，这些目标由根工程通过 XThirdParty 提供。[运行库依赖](src/runtime/cmake/Dependencies.cmake)

```sh
cmake -S . -B build/intermediate/local -G Ninja -DCMAKE_BUILD_TYPE=Debug "-DX_RELEASE_BASE_URL=<release-location>"
cmake --build build/intermediate/local --target engine
```

The engine executable and runtime library can also start from separate checkouts of `src/engine` and `src/runtime`. The executable uses its sibling runtime sources when available. A copy of the executable project alone retrieves the matching private runtime from the pinned XEngine source revision. The executable links `X::runtime`. Run it from the selected output tree, for example `build/build-Win-MSVC-Debug/bin/`.

也可分别复制 `src/engine` 和 `src/runtime` 来独立构建可执行程序和运行库。独立构建可执行程序时，优先使用同级运行库源码。单独复制可执行程序工程后，脚本会从固定版本的 XEngine 源码中获取配套的私有运行库。可执行程序链接 `X::runtime`。从所选输出目录运行它，例如 `build/build-Win-MSVC-Debug/bin/`。
