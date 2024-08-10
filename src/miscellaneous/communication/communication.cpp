#include "communication.hpp"

bool communication_t::setup()
{
	const auto cleanup = [&](bool status, addrinfo * info, SOCKET server_socket = 0)
	{
		if (!status)
		{
			int code = WSAGetLastError();
			if (server_socket)
				closesocket(server_socket);

			WSACleanup();
		}

		freeaddrinfo(info);
		return status;
	};

	WSADATA wsa_data{ 0 };
	if (WSAStartup(MAKEWORD(2, 2), &wsa_data))
		return false;

	addrinfo* result = nullptr, hints{ 0 };
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;

	if (getaddrinfo(NULL, port, &hints, &result))
		return cleanup(false, result);

	if (server_socket = socket(hints.ai_family, hints.ai_socktype, hints.ai_protocol); server_socket == INVALID_SOCKET)
		return cleanup(false, result);

	if (bind(server_socket, result->ai_addr, result->ai_addrlen) == SOCKET_ERROR)
		return cleanup(false, result, server_socket);

	if (listen(server_socket, SOMAXCONN) == SOCKET_ERROR)
		return cleanup(false, result, server_socket);

	return cleanup(true, result);
}

void communication_t::receive_data()
{
	if (server_socket == INVALID_SOCKET)
		return;

	while (true)
	{
		if (client_socket = accept(server_socket, nullptr, nullptr); client_socket == INVALID_SOCKET)
			return;

		std::string script{};
		{
			std::string buffer{};
			buffer.resize(buffer_size, '\0');

			while (std::size_t received = recv(client_socket, &buffer[0], buffer.size(), 0))
			{
				if (!received)
					break;

				script += std::string{ buffer.c_str(), received };
				buffer.resize(buffer_size, '\0');

				if (received < buffer_size)
					break;
			}

			shutdown(client_socket, SD_BOTH);
			closesocket(client_socket);
		}

		script_scheduler->add_to_queue(script.c_str());
	}
	return;
}

void communication_t::finish()
{
	closesocket(server_socket);
	WSACleanup();
}