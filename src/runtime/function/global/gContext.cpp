/**
 *------------------------------------------------------------------------------
 * @file        gContext
 * @brief       Creates and releases the runtime's global logging system.
 * @details     Defines the shared runtime context and controls the lifetime of its LogSystem
 *              instance.
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
 *    - Implemented global logger creation and shutdown.
 *  [V1.0.0] - 2026/11/26 by XSilver
 *    - Recorded the MIT license adopted by the project.
 * ------------------------------------------------------------------------------
 */

#include "gContext.h"
#include "logSystem.h"
#include <memory>

namespace XEngine
{

    RuntimeGlobalContext g_runtime_global_context;

    void RuntimeGlobalContext::startSystems(const std::string& config_file_path)
    {
        m_logger_system = std::make_shared<LogSystem>();
    }

    void RuntimeGlobalContext::shutdownSystems()
    {
        m_logger_system.reset();
    }

} // namespace XEngine