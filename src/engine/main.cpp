/**
 *------------------------------------------------------------------------------
 * @file        main
 * @brief       Starts the engine with the project configuration deployed beside bin.
 * @details     Sets the working directory to the executable's directory and runs the engine
 *              lifecycle.
 *
 * @author      XSilver
 * @date        2026/3/14
 * @version     V1.0.0
 *
 * @copyright   Copyright (c) 2026 [XSilverWolf]
 *              This project is licensed under the MIT License.
 *              See the LICENSE file in the project root for license information.
 *              SPDX-License-Identifier: MIT
 *
 * ------------------------------------------------------------------------------
 *  REVISION HISTORY (Modify)
 * ------------------------------------------------------------------------------
 *  [48cdc63] - 2026/3/14 by 骇客速成计划
 *    - Added the console entry point with a greeting.
 *  [7a759d8] - 2026/3/30 by 骇客速成计划
 *    - Resolved XEngine.ini and invoked engine startup, run and shutdown.
 *  [V1.0.0] - 2026/11/26 by XSilver
 *    - Recorded the MIT license adopted by the project.
 *    - Pass the selected build's configs/project.json to the engine runtime.
 * ------------------------------------------------------------------------------
 */

#include <iostream>
#include <filesystem>
#include "engine.h"

int main(int argc, char* argv[])
{
    std::filesystem::path executable_path = std::filesystem::absolute(argv[0]);
    std::filesystem::path executable_dir = executable_path.parent_path();
    std::filesystem::current_path(executable_dir);
    const auto config_file_path = executable_dir.parent_path() / "configs" / "project.json";
    std::cout << "Config file path: " << config_file_path << std::endl;

    

    XEngine::Engine engine;
    engine.startEngine(config_file_path.string());
    engine.run();
    engine.shutdownEngine();


    return 0;
}

