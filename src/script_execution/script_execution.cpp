#include "script_execution.hpp"

void script_execution_t::execute_script(const char* script)
{
	const auto compress_bytecode = [&](std::string_view bytecode) -> std::string
	{
		const auto data_size = bytecode.size();
		const auto max_size = ZSTD_compressBound(data_size);
		auto buffer = std::vector<char>(max_size + 8);

		strcpy_s(&buffer[0], buffer.capacity(), "RSB1");
		memcpy_s(&buffer[4], buffer.capacity(), &data_size, sizeof(data_size));

		const auto compressed_size = ZSTD_compress(&buffer[8], max_size, bytecode.data(), data_size, ZSTD_maxCLevel());
		if (ZSTD_isError(compressed_size))
			throw new std::runtime_error("Failed to compress bytecode.");

		const auto size = compressed_size + 8;
		const auto key = XXH32(buffer.data(), size, 42u);
		const auto bytes = reinterpret_cast<const uint8_t*>(&key);

		for (auto i = 0u; i < size; ++i)
			buffer[i] ^= bytes[i % 4] + i * 41u;

		return std::string(buffer.data(), size);
	};

	class bytecode_encoder_t : public Luau::BytecodeEncoder
	{
		inline void encode(uint32_t* data, size_t count) override
		{
			for (auto i = 0u; i < count;)
			{
				auto& opcode = *reinterpret_cast<uint8_t*>(data + i);
				i += Luau::getOpLength(LuauOpcode(opcode));
				opcode *= 227;
			}
		}
	};

	static auto encoder = bytecode_encoder_t();
	auto bytecode = Luau::compile(script, {}, {}, &encoder);
	bytecode = compress_bytecode(bytecode);

	// ...
}