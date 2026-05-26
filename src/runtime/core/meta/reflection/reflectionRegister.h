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