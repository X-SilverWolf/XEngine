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