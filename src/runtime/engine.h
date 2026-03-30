#ifndef RUNTIME_ENGINE_H
#define RUNTIME_ENGINE_H

#include <chrono>
#include <string>


namespace XEngine
{

class Engine
{
public:
    Engine();
    ~Engine();

public:
    void startEngine(const std::string& config_file_path);
    void shutdownEngine();

    void initialize();
    void clear();

    bool isQuit() const { return m_is_quit; }
    void run(){}
    bool tickOneFrame(float delta_time){ return true; }

    int getFPS() const { return m_fps; }

protected:
    void logicalTick(float delta_time){}
    bool rendererTick(float delta_time){ return true; }
    void calculateFPS(float delta_time){}

    /**
    *  Each frame can only be called once
    */
    float calculateDeltaTime(){ return 0.f; }

protected:
    // whether the engine is quit
    bool m_is_quit {false};

    // save the last tick time point
    std::chrono::steady_clock::time_point m_last_tick_time_point {std::chrono::steady_clock::now()};

    // average duration of one frame
    float m_average_duration {0.f};
    int   m_frame_count {0};
    int   m_fps {0};

    static const float s_fps_alpha;
};

} // namespace XEngine

#endif // RUNTIME_ENGINE_H