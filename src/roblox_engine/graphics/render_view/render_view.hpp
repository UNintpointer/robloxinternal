#pragma once
#include <filesystem>
#include <fstream>

#include "../../flog_reader/flog_reader.hpp"

namespace roblox_engine
{
    namespace graphics
    {
        class render_view_t
        {
        public:
            uintptr_t get();
        };

        inline auto render_view = std::make_unique<render_view_t>();
    }
}