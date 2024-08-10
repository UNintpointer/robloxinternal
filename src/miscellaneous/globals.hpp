#pragma once
#include <cmath>

#include <lobject.h>
#include <lgc.h>

struct
{
	uintptr_t data_model;
	uintptr_t render_view;
	uintptr_t visual_engine;

	lua_State* lua_state;
} globals;