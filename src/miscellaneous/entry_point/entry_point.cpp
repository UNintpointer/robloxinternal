#include "entry_point.hpp"

void main_thread(HMODULE dll_module)
{
	std::thread([]() -> void { roblox_engine::teleport_handler->initialize_watcher(); }).detach();

	script_environment->initialize();
	script_scheduler->initialize();

	script_scheduler->add_to_queue(R"(
		print("Hello, world!")
	)");

	if (communication->setup())
		std::thread([]() -> void { communication->receive_data(); }).detach();
}

bool __stdcall DllMain(HMODULE dll_module, uintptr_t reason_for_call, void*)
{
	if (reason_for_call == DLL_PROCESS_ATTACH)
		std::thread(main_thread, dll_module).detach();

	return true;
}