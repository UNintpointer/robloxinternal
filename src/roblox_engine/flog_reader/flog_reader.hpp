#pragma once
#include <filesystem>
#include <shlobj.h>

namespace roblox_engine
{
    class flog_reader_t
    {
    public:
        std::filesystem::path get_log_info();
    };

    inline auto flog_reader = std::make_unique<flog_reader_t>();
}