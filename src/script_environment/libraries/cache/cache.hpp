#pragma once
#include "../library.hpp"

class cache : public library_t
{
public:
	void initialize(lua_State* lua_state) override;
};