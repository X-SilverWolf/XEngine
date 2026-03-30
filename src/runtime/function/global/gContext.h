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