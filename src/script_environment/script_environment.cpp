#include "script_environment.hpp"

void script_environment_t::initialize()
{
	std::vector<library_t*> libraries;
	libraries.push_back(new cache());
	libraries.push_back(new closure());
	libraries.push_back(new crypt());
	//libraries.push_back(new debug());
	libraries.push_back(new drawing());
	libraries.push_back(new file_system());
	libraries.push_back(new http());
	libraries.push_back(new input());
	libraries.push_back(new metatable());
	libraries.push_back(new websocket());

	for (auto& library : libraries)
		library->initialize(globals.lua_state);
}