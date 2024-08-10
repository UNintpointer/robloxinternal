#include "teleport_handler.hpp"

using namespace roblox_engine;

void teleport_handler_t::initialize_watcher()
{
    uintptr_t updated_data_model = 0, place_id = 0;
    for (;; std::this_thread::sleep_for(std::chrono::seconds(1)))
    {
        updated_data_model = data_model->get();
        if (globals.data_model != updated_data_model)
        {
            globals.data_model = updated_data_model;
            globals.render_view = graphics::render_view->get();
            globals.visual_engine = graphics::visual_engine->get();

            place_id = *reinterpret_cast<uintptr_t*>(globals.data_model + update::offsets::place_id);
            if (place_id != 0)
            {
                /*
                    // index 0 is local script lua state
                    uintptr_t deobf1 = (uint32_t)(obfuscated_lua_state) - *reinterpret_cast<uint32_t*>(obfuscated_lua_state + sizeof(uint32_t));
                    uintptr_t deobf2 = (uint32_t)(obfuscated_lua_state) - *reinterpret_cast<uint32_t*>(obfuscated_lua_state);

                    globals.lua_state = reinterpret_cast<lua_State*>(__PAIR64__(deobf1, deobf2));
                */

                place_id = 0;
            }

            std::this_thread::sleep_for(std::chrono::seconds(3));
        }
    }
}