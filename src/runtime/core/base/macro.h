/**
 *------------------------------------------------------------------------------
 * @file        macro
 * @brief       Defines the engine's severity-specific logging macros.
 * @details     LOG_HELPER adds the calling function name before sending the message to the
 *              global logger.
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
 *    - Introduced the debug, info, warning, error and fatal logging entry points.
 *  [V1.0.0] - 2026/11/26 by XSilver
 *    - Recorded the MIT license adopted by the project.
 * ------------------------------------------------------------------------------
 */

#ifndef XENGINE_MACRO_H
#define XENGINE_MACRO_H

#include "logSystem.h"
#include "gContext.h"

#define LOG_HELPER(LOG_LEVEL, ...) \
    g_runtime_global_context.m_logger_system->log(LOG_LEVEL, "[" + std::string(__FUNCTION__) + "] " + __VA_ARGS__);

#define LOG_DEBUG(...) LOG_HELPER(LogSystem::LogLevel::debug, __VA_ARGS__);

#define LOG_INFO(...) LOG_HELPER(LogSystem::LogLevel::info, __VA_ARGS__);

#define LOG_WARN(...) LOG_HELPER(LogSystem::LogLevel::warn, __VA_ARGS__);

#define LOG_ERROR(...) LOG_HELPER(LogSystem::LogLevel::error, __VA_ARGS__);

#define LOG_FATAL(...) LOG_HELPER(LogSystem::LogLevel::fatal, __VA_ARGS__);


#endif // XENGINE_MACRO_H