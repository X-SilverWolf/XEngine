/**
 *------------------------------------------------------------------------------
 * @file        reflectionRegister
 * @brief       Declares the lifecycle entry points for reflection registration.
 * @details     TypeMetaRegister exposes a static pair of hooks for installing and removing type
 *              metadata.
 *
 * @author      XSilver
 * @date        2026/5/27
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
 *  [550ea68] - 2026/5/27 by 骇客速成计划
 *    - Declared the TypeMetaRegister entry points.
 *  [V1.0.0] - 2026/11/26 by XSilver
 *    - Recorded the MIT license adopted by the project.
 * ------------------------------------------------------------------------------
 */

#include "reflection.h"
#ifndef XENGINE_REFLECTION_REGISTER_H

namespace XEngine
{
    namespace Reflection
    {
        class TypeMetaRegister
        {
        public:
            static void metaRegister();
            static void metaUnregister();
        };
    }
}

#endif // XENGINE_REFLECTION_REGISTER_H