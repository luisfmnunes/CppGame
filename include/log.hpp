#pragma once

#include<spdlog/spdlog.h>
#include<filesystem>
#include<source_location>

#define ENGINE_DEFAULT_LOGGER_NAME "defaultlogger"

#ifdef _WIN32
#define DEBUG_BREAK __debugbreak();
#elif __APPLE__
#define DEBUG_BREAK __builtin_debugtrap();
#else
#define DEBUG_BREAK __builtin_trap();
#endif

#ifndef GAME_RELEASE
    #define LOG_TRACE(...) if(spdlog::get(ENGINE_DEFAULT_LOGGER_NAME) != nullptr) spdlog::get(ENGINE_DEFAULT_LOGGER_NAME)->trace(__VA_ARGS__);
    #define LOG_DEBUG(...) if(spdlog::get(ENGINE_DEFAULT_LOGGER_NAME) != nullptr) spdlog::get(ENGINE_DEFAULT_LOGGER_NAME)->debug(__VA_ARGS__);
    #define LOG_INFO(...) if(spdlog::get(ENGINE_DEFAULT_LOGGER_NAME) != nullptr) spdlog::get(ENGINE_DEFAULT_LOGGER_NAME)->info(__VA_ARGS__);
    #define LOG_WARN(...) if(spdlog::get(ENGINE_DEFAULT_LOGGER_NAME) != nullptr) spdlog::get(ENGINE_DEFAULT_LOGGER_NAME)->warn(__VA_ARGS__);
    #define LOG_ERROR(...) if(spdlog::get(ENGINE_DEFAULT_LOGGER_NAME) != nullptr) spdlog::get(ENGINE_DEFAULT_LOGGER_NAME)->error(__VA_ARGS__);
    #define LOG_FATAL(...) if(spdlog::get(ENGINE_DEFAULT_LOGGER_NAME) != nullptr) spdlog::get(ENGINE_DEFAULT_LOGGER_NAME)->critical(__VA_ARGS__); 
    #define LOG_ASSERT(x, msg) if ((x)) {} else {auto s = std::source_location::current(); LOG_FATAL("ASSERT - {} | MSG: {}, {}({}:{}) `{}`", #x, msg, std::filesystem::path(s.file_name()).filename().c_str(), s.line(), s.column(), s.function_name()) DEBUG_BREAK}
#else
    #define LOG_TRACE(...) (void)0
    #define LOG_DEBUG(...) (void)0
    #define LOG_INFO(...) (void)0
    #define LOG_WARN(...) (void)0
    #define LOG_ERROR(...) (void)0
    #define LOG_FATAL(...) (void)0
    #define LOG_ASSERT(...) (void)0
#endif