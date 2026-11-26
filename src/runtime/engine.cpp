/**
 *------------------------------------------------------------------------------
 * @file        engine
 * @brief       Starts and shuts down the global engine systems.
 * @details     Passes the configuration path to the global context and logs both lifecycle
 *              transitions.
 *
 * @author      XSilver
 * @date        2026/3/30
 * @version     V1.0.0
 *
 * @copyright   Copyright (c) 2026 [XSilverWolf]
 *              Adapted portions: Copyright (c) 2022 Contributors to the Piccolo Engine.
 *              See LICENSES/Piccolo-MIT.txt for the upstream copyright and permission notice.
 *              Upstream source: https://github.com/BoomingTech/Piccolo
 *              This project is licensed under the MIT License.
 *              See the LICENSE file in the project root for license information.
 *              SPDX-License-Identifier: MIT
 *
 * ------------------------------------------------------------------------------
 *  REVISION HISTORY (Modify)
 * ------------------------------------------------------------------------------
 *  [7a759d8] - 2026/3/30 by 骇客速成计划
 *    - Connected engine startup and shutdown to the global context.
 *  [V1.0.0] - 2026/11/26 by XSilver
 *    - Recorded the MIT license adopted by the project.
 * ------------------------------------------------------------------------------
 */

#include "engine.h"
#include "core/meta/reflection/reflection.h"
#include "macro.h"
#include "gContext.h"

namespace XEngine
{

Engine::Engine()
{

}

Engine::~Engine()
{

}

void Engine::startEngine(const std::string& config_file_path)
{   
    g_runtime_global_context.startSystems(config_file_path);

    LOG_INFO("engine start");

}

void Engine::shutdownEngine()
{
    LOG_INFO("engine shutdown");
    g_runtime_global_context.shutdownSystems();
}

void Engine::initialize()
{

}

void Engine::clear()
{

}
} // namespace XEngine