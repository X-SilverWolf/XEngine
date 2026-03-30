#include "engine.h"
#include "macro.h"

namespace XEngine
{

Engine::Engine()
{

}

Engine::~Engine()
{

}

void Engine::startEngine(const std::string& config_file_path)
{   
    g_runtime_global_context.startSystems(config_file_path);
    LOG_INFO("engine start");

}

void Engine::shutdownEngine()
{
    LOG_INFO("engine shutdown");
    g_runtime_global_context.shutdownSystems();
}

void Engine::initialize()
{

}

void Engine::clear()
{

}
} // namespace XEngine