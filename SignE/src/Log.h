//
// Created by Mikkel Mouridsen on 17/12/2022.
//

#ifndef SIGNEPROJECT_LOG_H
#define SIGNEPROJECT_LOG_H

#include <memory>
#include <string>
#include <mutex>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/base_sink.h>

namespace SignE::Core::Log {

    static void LogInfo(std::string msg) { spdlog::info(msg); }
    static void LogError(std::string msg) { spdlog::error(msg); }

    template<typename Mutex>
    class InMemorySink : public spdlog::sinks::base_sink<Mutex>
    {
    public:
        InMemorySink() {};
        const std::vector<std::string>& get_logs() const
        {
            return logs_;
        }

    protected:
        void sink_it_(const spdlog::details::log_msg& msg) override
        {
            spdlog::memory_buf_t formatted;
            spdlog::sinks::base_sink<Mutex>::formatter_->format(msg, formatted);
            logs_.push_back(fmt::to_string(formatted));
            if (logs_.size() > 500) {
                logs_.erase(logs_.begin());
            }
        }

        void flush_() override {}

    private:
        std::vector<std::string> logs_;
    };


    static std::shared_ptr<InMemorySink<std::mutex>> sink;
    static void SetupInMemoryLog() {
        sink = std::make_shared<InMemorySink<std::mutex>>();
        auto logger = spdlog::default_logger();
        logger->sinks().push_back(sink);
    }


    static std::vector<std::string> GetAllLogs() { 
        return sink->get_logs();
    }
}

#endif //SIGNEPROJECT_LOG_H
