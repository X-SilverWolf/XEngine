#ifndef XENGINE_REFLECTION_H
#define XENGINE_REFLECTION_H

#include <functional>
#include "json.h"

namespace XEngine
{

    #if defined(__REFLECTION_PARSER__)
    #define META(...) __attribute__((annotate(#__VA_ARGS__)))
    #define CLASS(class_name, ...) class __attribute__((annotate(#__VA_ARGS__))) class_name
    #define STRUCT(struct_name, ...) struct __attribute__((annotate(#__VA_ARGS__))) struct_name
    //#define CLASS(class_name,...) class __attribute__((annotate(#__VA_ARGS__))) class_name:public Reflection::object
    #else
    #define META(...)
    #define CLASS(class_name, ...) class class_name
    #define STRUCT(struct_name, ...) struct struct_name
    //#define CLASS(class_name,...) class class_name:public Reflection::object
    #endif // __REFLECTION_PARSER__


    #define REFLECTION_BODY(class_name) \
        friend class Reflection::TypeFieldReflectionOperator::Type##class_name##Operator; \
        friend class Serializer;

    #define REFLECTION_TYPE(class_name) \
        namespace Reflection \
        { \
            namespace TypeFieldReflectionOperator \
            { \
                class Type##class_name##Operator; \
            } \
        }

    #define REGISTER_FIELD_TO_MAP(name, value) TypeFieldReflectionOperator::registerdToFieldMap(name, value);
    #define REGISTER_METHOD_TO_MAP(name, value) TypeFieldReflectionOperator::registerToMethodMap(name, value);
    #define REGISTER_BASE_TO_MAP(name, value) TypeFieldReflectionOperator::registerToClassMap(name, value);
    #define REGISTER_ARRAY_TO_MAP(name, value) TypeFieldReflectionOperator::registerToArrayMap(name, value);
    #define UNREGISTER_ALL() TypeFieldReflectionOperator::unregisterAll();

    // Create a new instance of the class
    #define XENGINE_REFLECTION_NEW(name, ...) Reflection::ReflectionPtr(#name, _new name(__VA_ARGS__));

    #define XENGINE_REFLECTION_DELETE(value) \
        if(value) { \
            delete value.operator->(); \
            value.getPtrReference() = nullptr; \
        }

    #define XENGINE_REFLECTION_DEEP_COPY(type, dst_ptr, src_ptr) \
        *static_cast<type*>(dst_ptr) = *static_cast<type*>(src_ptr.getPtr());

    #define TYPE_META_DEF(class_name, ptr) \
        XEngine::Reflection::ReflectionInstance(XEngine::Reflection::TypeMeta::newMetaFromName(#class_name), (class_name*)ptr);

    #define TYPE_META_DEF_PTR(class_name, ptr) \
        new XEngine::Reflection::ReflectionInstance(XEngine::Reflection::TypeMeta::newMetaFromName(#class_name), (class_name*)ptr);

    template <typename T, typename U, typename = void>
    struct is_safely_castable : std::false_type {};

    template <typename T, typename U>
    struct is_safely_castable <T, U, std::void_t<decltype(static_cast<U>(std::declval<T>()))>> : std::true_type {};

namespace Reflection
{
    // The meta classes for reflection
    class TypeMeta;
    class FieldAccessor;
    class MethodAccessor;
    class ArrayAccessor;
    class ReflectionInstance;

} // namespace Reflection

    // The type of functions
    typedef std::function<void(void*, void*)>      SetFuncion;
    typedef std::function<void*(void*)>            GetFuncion;
    typedef std::function<const char*()>           GetNameFuncion;
    typedef std::function<void(int, void*, void*)> SetArrayFunc;
    typedef std::function<void*(int, void*)>       GetArrayFunc;
    typedef std::function<int(void*)>              GetSizeFunc;
    typedef std::function<bool()>                  GetBoolFunc;
    typedef std::function<void(void*)>             InvokeFunction;

    typedef std::function<void*(const Json&)>      ConstructorWithJson;
    typedef std::function<Json(void*)>             WriteJsonByName;
    typedef std::function<int(Reflection::ReflectionInstance*&, void*)> GetBaseClassReflectionInstanceListFunc;

    typedef std::tuple<SetFuncion, GetFuncion, GetNameFuncion, GetNameFuncion, GetNameFuncion, GetBoolFunc> FieldFunctionTuple;
    typedef std::tuple<GetNameFuncion, InvokeFunction> MethodFunctionTuple;
    typedef std::tuple<GetBaseClassReflectionInstanceListFunc, ConstructorWithJson, WriteJsonByName> ClassFunctionTuple;
    typedef std::tuple<SetArrayFunc, GetArrayFunc, GetSizeFunc, GetNameFuncion, GetNameFuncion>      ArrayFunctionTuple;


} // namespace XEngine

#endif