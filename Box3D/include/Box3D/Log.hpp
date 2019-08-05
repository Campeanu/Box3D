#ifndef __LOG_HPP_INCLUDED__
#define __LOG_HPP_INCLUDED__

#include <memory>

#include "Core.hpp"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace box3d {

    class Log
    {
    public:
        static void Init();
        inline static std::shared_ptr<spdlog::logger>& GetCoreLogger()   { return s_CoreLogger;   }
        inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
    private:
        static std::shared_ptr<spdlog::logger> s_CoreLogger;
        static std::shared_ptr<spdlog::logger> s_ClientLogger;
    };
    
}

// Core log macros
#define BOX3D_CORE_TRACE(...)    ::box3d::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define BOX3D_CORE_INFO(...)     ::box3d::Log::GetCoreLogger()->info(__VA_ARGS__)
#define BOX3D_CORE_WARN(...)     ::box3d::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define BOX3D_CORE_ERROR(...)    ::box3d::Log::GetCoreLogger()->error(__VA_ARGS__)
#define BOX3D_CORE_FATAL(...)    ::box3d::Log::GetCoreLogger()->fatal(__VA_ARGS__)

// Client log macros
#define BOX3D_TRACE(...)	     ::box3d::Log::GetClientLogger()->trace(__VA_ARGS__)
#define BOX3D_INFO(...)	     	 ::box3d::Log::GetClientLogger()->info(__VA_ARGS__)
#define BOX3D_WARN(...)	    	 ::box3d::Log::GetClientLogger()->warn(__VA_ARGS__)
#define BOX3D_ERROR(...)	     ::box3d::Log::GetClientLogger()->error(__VA_ARGS__)
#define BOX3D_FATAL(...)	     ::box3d::Log::GetClientLogger()->fatal(__VA_ARGS__)

#endif //!__LOG_HPP_INCLUDED__