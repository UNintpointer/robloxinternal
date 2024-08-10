#include "script_scheduler.hpp"

void script_scheduler_t::add_to_queue(const char* script)
{
	this->script_queue.emplace(script);
}

void script_scheduler_t::initialize()
{
	std::thread([&]() -> void {
		auto script = "";

		while (true)
		{
			if (this->script_queue.empty())
				continue;

			script = this->script_queue.back();
			this->script_queue.pop();

			script_execution->execute_script(script);
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}
	}).detach();;
}