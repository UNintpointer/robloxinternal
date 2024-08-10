#pragma once
#include "../library.hpp"

class file_system : public library_t
{
public:
	void initialize(lua_State* lua_state) override;
};