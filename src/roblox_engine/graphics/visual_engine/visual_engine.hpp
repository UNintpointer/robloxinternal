#pragma once
#include "../render_view/render_view.hpp"

namespace roblox_engine
{
    namespace graphics
    {
        class visual_engine_t
        {
        public:
            uintptr_t get();
        };

        inline auto visual_engine = std::make_unique<visual_engine_t>();
    }
}