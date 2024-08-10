#pragma once
#include <iostream>
#include <queue>
#include <thread>

#include <script_execution/script_execution.hpp>

class script_scheduler_t
{
public:
	std::queue<const char*> script_queue;

	void add_to_queue(const char* script);
	void initialize();
};

inline auto script_scheduler = std::make_unique<script_scheduler_t>();