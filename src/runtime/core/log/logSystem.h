#ifndef XENGINE_LOG_SYSTEM_H
#define XENGINE_LOG_SYSTEM_H

#include <spdlog/spdlog.h>
#include <spdlog/async.h>
#include <spdlog/fmt/bundled/format.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#include <cstdint>
#include <stdexcept>
#include <memory>
namespace XEngine
{

class LogSystem final
{
public:
    enum class LogLevel : uint8_t
    {
        debug,
        info,
        warn,
        error,
        fatal
    };

public:
    LogSystem()
    {
        auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        console_sink->set_level(spdlog::level::trace);
        console_sink->set_pattern("[%^%l%$] %v");

        const spdlog::sinks_init_list sink_list = {console_sink};

        spdlog::init_thread_pool(8192, 1);

        m_logger = std::make_shared<spdlog::async_logger>("muggle_logger",
                                                          sink_list.begin(),
                                                          sink_list.end(),
                                                          spdlog::thread_pool(),
                                                          spdlog::async_overflow_policy::block);
        m_logger->set_level(spdlog::level::trace);

        spdlog::register_logger(m_logger);
    };
    ~LogSystem()
    {
        m_logger->flush();
        spdlog::drop_all();
    };

    template<typename... TARGS>
    void log(LogLevel level, TARGS&&... args)
    {
        switch (level)
        {
            case LogLevel::debug:
                m_logger->debug(std::forward<TARGS>(args)...);
                break;
            case LogLevel::info:
                m_logger->info(std::forward<TARGS>(args)...);
                break;
            case LogLevel::warn:
                m_logger->warn(std::forward<TARGS>(args)...);
                break;
            case LogLevel::error:
                m_logger->error(std::forward<TARGS>(args)...);
                break;
            case LogLevel::fatal:
                m_logger->critical(std::forward<TARGS>(args)...);
                fatalCallback(std::forward<TARGS>(args)...);
                break;
            default:
                break;
        }
    }

    template<typename... TARGS>
    void fatalCallback(TARGS&&... args)
    {
        const std::string format_str = fmt::format(std::forward<TARGS>(args)...);
        throw std::runtime_error(format_str);
    }

private:
    std::shared_ptr<spdlog::logger> m_logger;
};

} // namespace XEngine

#endif // XENGINE_LOG_SYSTEM_H