#include "reflection.h"
#include <map>
namespace XEngine
{
namespace Reflection
{
    const char* k_unknown_type = "UnknownType";
    const char* k_unknown = "Unknown";

    static std::map<std::string, ClassFunctionTuple*> m_class_map;
    static std::map<std::string, FieldFunctionTuple*> m_field_map;
    static std::map<std::string, MethodFunctionTuple*> m_method_map;
    static std::map<std::string, ArrayFunctionTuple*> m_array_map;

    void TypeMetaRegisterInterface::registerToClassMap(const char* name, ClassFunctionTuple* value)
    {
        m_class_map.insert(std::make_pair(name, value));
    }
    
    void TypeMetaRegisterInterface::registerToFieldMap(const char* name, FieldFunctionTuple* value)
    {
        m_field_map.insert(std::make_pair(name, value));
    }

    void TypeMetaRegisterInterface::registerToMethodMap(const char* name, MethodFunctionTuple* value)
    {
        if(m_method_map.find(name) != m_method_map.end())
        {
            delete value;
        }
        m_method_map.insert(std::make_pair(name, value));
    }

    void TypeMetaRegisterInterface::registerToArrayMap(const char* name, ArrayFunctionTuple* value)
    {
        if(m_array_map.find(name) != m_array_map.end())
        {
            delete value;
        }
        m_array_map.insert(std::make_pair(name, value));
    }

    void TypeMetaRegisterInterface::unregisterAll()
    {
        for(const auto& itr : m_class_map)
        {
            delete itr.second;
        }
        for(const auto& itr : m_field_map)
        {
            delete itr.second;
        }
        for(const auto& itr : m_method_map)
        {
            delete itr.second;
        }
        for(const auto& itr : m_array_map)
        {
            delete itr.second;
        }
        m_class_map.clear();
        m_field_map.clear();
        m_method_map.clear();
        m_array_map.clear();
    }

    TypeMeta::TypeMeta() 
    : m_name(k_unknown_type)
    , m_is_valid(false)
    {
        m_fields.clear();
        m_methods.clear();
    }

    TypeMeta TypeMeta::newMetaFromName(std::string name)
    {
        return TypeMeta(name);
    }

    TypeMeta::TypeMeta(std::string name)
    : m_name(name)
    , m_is_valid(false)
    {
        m_fields.clear();
        m_methods.clear();

        auto fields_iter = m_field_map.equal_range(name);

        for(auto itr = fields_iter.first; itr != fields_iter.second; ++itr)
        {
            FieldAccessor f_field(itr->second);
            m_fields.push_back(f_field);
             m_is_valid = true;
        }

        auto methods_iter = m_method_map.equal_range(name);
        for(auto itr = methods_iter.first; itr != methods_iter.second; ++itr)
        {
            MethodAccessor m_method(itr->second);
            m_methods.push_back(m_method);
            m_is_valid = true;
        }
    }



    FieldAccessor::FieldAccessor()
    : m_func(nullptr)
    , m_name(k_unknown)
    , m_type(k_unknown_type)
    {

    }

    void* FieldAccessor::get(void* instance)
    {
        // get the value of the field
        return static_cast<void*>(std::get<1>(*m_func)(instance));
    }

    void FieldAccessor::set(void* instance, void* value)
    {
        std::get<0>(*m_func)(instance, value);
    }
    
    TypeMeta FieldAccessor::getOwnerTypeMeta()
    {
        return TypeMeta (std::get<2>(*m_func)());
    }

    bool FieldAccessor::getTypeMeta(TypeMeta& field_type)
    {
        TypeMeta f_type(m_type);
        field_type = f_type;
        return f_type.m_is_valid;
    }

    const char* FieldAccessor::getFieldName() 
    {
        return m_name;
    }

    const char* FieldAccessor::getFieldType()
    {
        return m_type;
    }

    bool FieldAccessor::isArray()
    {
        return std::get<5>(*m_func)();
    }

    FieldAccessor& FieldAccessor::operator=(const FieldAccessor& other)
    {
        if(this == &other)
        {
            return *this;
        }

        m_func = other.m_func;
        m_name = other.m_name;
        m_type = other.m_type;
        return *this;
    }

    FieldAccessor::FieldAccessor(FieldFunctionTuple* func)
    : m_func(func)
    , m_name(k_unknown)
    , m_type(k_unknown_type)
    {

    }

    MethodAccessor::MethodAccessor()
    : m_func(nullptr)
    , m_name(k_unknown)
    {

    }

    MethodAccessor::MethodAccessor(MethodFunctionTuple* func)
    : m_func(func)
    , m_name(k_unknown)
    {

    }
    


} // namespace Reflection
} // namespace XEngine