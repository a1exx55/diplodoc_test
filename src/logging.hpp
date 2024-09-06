#ifndef LOGGING_HPP
#define LOGGING_HPP

#include <string_view>
#include <source_location>
#include <iostream>

namespace logging
{
    enum class level
    {
        info,
        debug,
        error
    };

    inline void log(
        level logging_level, 
        const std::string_view message, 
        const std::source_location location = std::source_location::current())
    {
        std::clog << std::format(
            "[{}] <{}> [{}:{}] [{}]: {}\n",
            std::chrono::time_point_cast<std::chrono::seconds>(
                std::chrono::current_zone()->to_local(
                    std::chrono::system_clock::now())),
            logging_level == level::info ? "info" : (logging_level == level::debug ? "debug" : "error"),
            location.file_name(),
            location.line(),
            location.function_name(),
            message);
    }

    inline void log_info(
        const std::string_view message, 
        const std::source_location location = std::source_location::current())
    {
        log(level::info, message, location);
    } 

    inline void log_debug(
        const std::string_view message, 
        const std::source_location location = std::source_location::current())
    {
        log(level::debug, message, location);
    } 

    inline void log_error(
        const std::string_view message, 
        const std::source_location location = std::source_location::current())
    {
        log(level::error, message, location);
    } 
}

#endif