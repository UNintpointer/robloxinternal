#pragma once
#include "../graphics/render_view/render_view.hpp"

#include <update/offsets.hpp>

namespace roblox_engine
{
    class data_model_t
    {
    public:
        uintptr_t get();
    };

    inline auto data_model = std::make_unique<data_model_t>();
}