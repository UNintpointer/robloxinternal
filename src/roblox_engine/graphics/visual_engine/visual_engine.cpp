#include "visual_engine.hpp"

using namespace roblox_engine::graphics;

uintptr_t visual_engine_t::get()
{
    return *reinterpret_cast<uintptr_t*>(render_view->get() + 0x10);
}