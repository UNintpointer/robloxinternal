#include "data_model.hpp"

using namespace roblox_engine;

uintptr_t data_model_t::get()
{
	return *reinterpret_cast<uintptr_t*>(*reinterpret_cast<uintptr_t*>(graphics::render_view->get() + 0x118) + 0x198);
}