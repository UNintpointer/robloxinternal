#pragma once
#include <ws2tcpip.h>
#include <string>
#include <stack>
#include <shared_mutex>

#include <script_scheduler/script_scheduler.hpp>

class communication_t
{
private:
	const char* port = "42069";
	const std::size_t buffer_size = 0x4000;

	SOCKET server_socket = INVALID_SOCKET;
	SOCKET client_socket = INVALID_SOCKET;
public:
	bool setup();
	void receive_data();
	void finish();
};

inline auto communication = std::make_unique<communication_t>();