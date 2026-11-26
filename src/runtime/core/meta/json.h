/**
 *------------------------------------------------------------------------------
 * @file        json
 * @brief       Names the JSON value type used by engine reflection.
 * @details     The Json alias gives metadata callbacks a common spelling for json11::Json.
 *
 * @author      XSilver
 * @date        2026/4/1
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
 *  [bde3098] - 2026/4/1 by 骇客速成计划
 *    - Added the engine's json11 value alias.
 *  [V1.0.0] - 2026/11/26 by XSilver
 *    - Recorded the MIT license adopted by the project.
 * ------------------------------------------------------------------------------
 */

#ifndef XENGINE_JSON_H
#define XENGINE_JSON_H
#include <json11.hpp>

using Json = json11::Json;


#endif