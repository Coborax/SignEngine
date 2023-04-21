//
// Created by Mikkel Mouridsen on 17/12/2022.
//

#ifndef SIGNEPROJECT_LOG_H
#define SIGNEPROJECT_LOG_H

#include <string>
#include <spdlog/spdlog.h>

namespace SignE::Core::Log {
    static void LogInfo(std::string msg) { spdlog::info(msg); }
    static void LogError(std::string msg) { spdlog::error(msg); }
}

#endif //SIGNEPROJECT_LOG_H
