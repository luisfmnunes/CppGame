
#include<log.hpp>
#include<manager/logManager.hpp>

#include<memory>
#include<vector>
#include<spdlog/sinks/stdout_color_sinks.h>

namespace game::managers{

    void LogManager::Initialize(){

        auto consoleSink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        
        std::vector<spdlog::sink_ptr> sinks {consoleSink};
        auto logger = std::make_shared<spdlog::logger>(ENGINE_DEFAULT_LOGGER_NAME, sinks.begin(), sinks.end());

        logger->set_level(spdlog::level::trace);
        logger->flush_on(spdlog::level::trace);

        spdlog::register_logger(logger);

    }

    void LogManager::Shutdown(){
        spdlog::shutdown();
    }

}