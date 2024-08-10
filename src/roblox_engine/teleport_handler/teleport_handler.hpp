#pragma once
#include <iostream>
#include <thread>
#include <chrono>

#include "../data_model/data_model.hpp"
#include "../graphics/graphics.hpp"
#include <globals.hpp>

namespace roblox_engine
{
    class teleport_handler_t
    {
    public:
        void initialize_watcher();
    };

    inline auto teleport_handler = std::make_unique<teleport_handler_t>();
}