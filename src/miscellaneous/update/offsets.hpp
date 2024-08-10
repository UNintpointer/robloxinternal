#pragma once
#include <Windows.h>
#include <cmath>

#define REBASE(x) ((x - 0x400000) + reinterpret_cast<uintptr_t>(GetModuleHandleA(nullptr)))

namespace update
{
	namespace addresses
	{
		const uintptr_t luao_nilobject = REBASE(0xDEADBEEF);
		const uintptr_t luah_dummynode = REBASE(0xDEADBEEF);
		const uintptr_t luavm_load = REBASE(0xDEADBEEF);
	}

	namespace offsets
	{
		const uintptr_t place_id = 0x168;

		namespace instance
		{
			const uintptr_t name = 0x48;
			const uintptr_t children = 0x50;
			const uintptr_t parent = 0x60;

			namespace class_descriptor
			{
				const uintptr_t get = 0x18;
				const uintptr_t name = 0x8;
			}
		}
	}
}