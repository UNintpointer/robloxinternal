#pragma once
#include <iostream>
#include <vector>

#include "libraries/cache/cache.hpp"
#include "libraries/closure/closure.hpp"
#include "libraries/crypt/crypt.hpp"
#include "libraries/drawing/drawing.hpp"
#include "libraries/file_system/file_system.hpp"
#include "libraries/http/http.hpp"
#include "libraries/input/input.hpp"
#include "libraries/metatable/metatable.hpp"
#include "libraries/websocket/websocket.hpp"

#include <globals.hpp>

class script_environment_t
{
public:
	void initialize();
};

inline auto script_environment = std::make_unique<script_environment_t>();