/**
 *------------------------------------------------------------------------------
 * @file        gContext
 * @brief       Declares ownership of process-wide runtime systems.
 * @details     The shared global context exposes startup and shutdown hooks and holds the
 *              runtime logger.
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
 *    - Declared RuntimeGlobalContext and its global instance.
 *  [V1.0.0] - 2026/11/26 by XSilver
 *    - Recorded the MIT license adopted by the project.
 * ------------------------------------------------------------------------------
 */

#ifndef XENGINE_G_CONTEXT_H
#define XENGINE_G_CONTEXT_H

#include <memory>
#include <string>

namespace XEngine
{

    class LogSystem;

    /// Manage the lifetime and creation/destruction order of all global system
    class RuntimeGlobalContext
    {
    public:
        // create all global systems and initialize these systems
        void startSystems(const std::string& config_file_path);
        // destroy all global systems
        void shutdownSystems();

    public:
        std::shared_ptr<LogSystem>  m_logger_system;
    };

    extern RuntimeGlobalContext g_runtime_global_context;

} // namespace XEngine

#endif // XENGINE_G_CONTEXT_H