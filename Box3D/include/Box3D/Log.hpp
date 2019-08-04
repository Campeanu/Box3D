#ifndef __LOG_HPP_INCLUDED__
#define __LOG_HPP_INCLUDED__

#include <memory>

#include "Core.hpp"
#include "spdlog/spdlog.h"

namespace box3d {

    class Log
    {
    public:
        static void Init();
        inline static std::shared_ptr<spdlog::logger>& getCoreLogger()   { return s_CoreLogger;   }
        inline static std::shared_ptr<spdlog::logger>& getClientLogger() { return s_ClientLogger; }
    private:
        static std::shared_ptr<spdlog::logger> s_CoreLogger;
        static std::shared_ptr<spdlog::logger> s_ClientLogger;
    };
    
}

#endif //!__LOG_HPP_INCLUDED__