#pragma once
#include <lobject.h>
#include <lgc.h>

class library_t
{
public:
	virtual void initialize(lua_State* lua_state) {};
};