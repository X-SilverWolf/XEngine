#include <iostream>
#include <filesystem>
#include "engine.h"

int main(int argc, char* argv[])
{
    std::filesystem::path executable_path = std::filesystem::absolute(argv[0]);
    std::filesystem::path executable_dir = executable_path.parent_path();
    std::filesystem::current_path(executable_dir);
    std::filesystem::path config_file_path = executable_dir / "XEngine.ini";
    std::cout << "Config file path: " << config_file_path << std::endl;

    

    XEngine::Engine engine;
    engine.startEngine(config_file_path.string());
    engine.run();
    engine.shutdownEngine();


    return 0;
}

