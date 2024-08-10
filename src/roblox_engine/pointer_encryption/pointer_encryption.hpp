#pragma once
#include <cmath>

namespace roblox_engine
{
	namespace pointer_encryption
	{
		enum class encryption_type_t
		{
			ENC_NONE,
			ENC_ADD, // *reinterpret_cast<uintptr_t*>(val + offset) = new_value + (val + offset);
			ENC_SUB1, // *reinterpret_cast<uintptr_t*>(val + offset) = new_value - (val + offset);
			ENC_SUB2, // *reinterpret_cast<uintptr_t*>(val + offset) = (val + offset) - new_value;
			ENC_XOR // *reinterpret_cast<uintptr_t*>(val + offset) = new_value ^ (val + offset);
		};

		template<typename T>
		constexpr T get(uintptr_t value, encryption_type_t t)
		{
			uintptr_t val;

			switch (t)
			{
			case encryption_type_t::ENC_NONE:
				return *reinterpret_cast<T*>(value);
				break;
			case encryption_type_t::ENC_ADD:
				val = *reinterpret_cast<uintptr_t*>(value) - value;
				break;
			case encryption_type_t::ENC_SUB1:
				val = *reinterpret_cast<uintptr_t*>(value) + value;
				break;
			case encryption_type_t::ENC_SUB2:
				val = value - *reinterpret_cast<uintptr_t*>(value);
				break;
			case encryption_type_t::ENC_XOR:
				val = *reinterpret_cast<uintptr_t*>(value) ^ value;
				break;
			}

			return *reinterpret_cast<T*>(&val);
		}

		constexpr void set(uintptr_t value, uintptr_t new_value, encryption_type_t t)
		{
			switch (t)
			{
			case encryption_type_t::ENC_NONE:
				*reinterpret_cast<uintptr_t*>(value) = new_value;
				break;
			case encryption_type_t::ENC_ADD:
				*reinterpret_cast<uintptr_t*>(value) = new_value + value;
				break;
			case encryption_type_t::ENC_SUB1:
				*reinterpret_cast<uintptr_t*>(value) = new_value - value;
				break;
			case encryption_type_t::ENC_SUB2:
				*reinterpret_cast<uintptr_t*>(value) = value - new_value;
				break;
			case encryption_type_t::ENC_XOR:
				*reinterpret_cast<uintptr_t*>(value) = new_value ^ value;
				break;
			}
		}
	}

	template<typename T>
	struct offset
	{
	private:
		const uintptr_t offset_value;
		const pointer_encryption::encryption_type_t enc = pointer_encryption::encryption_type_t::ENC_NONE;
	public:
		offset(uintptr_t value, pointer_encryption::encryption_type_t enc = pointer_encryption::encryption_type_t::ENC_NONE) : offset_value{ value }, enc{ enc } {};

		uintptr_t bind(uintptr_t base)
		{
			return base + this->offset_value;
		}

		template<typename OV>
		OV custom_typed_bind(uintptr_t base)
		{
			return reinterpret_cast<OV>(base + this->offset_value);
		}

		T* typed_bind_ptr(uintptr_t base)
		{
			return reinterpret_cast<T*>(base + this->offset_value);
		}

		T get(uintptr_t base)
		{
			return pointer_encryption::get<T>(this->bind(base), this->enc);
		}

		uintptr_t get_offset()
		{
			return this->offset_value;
		}

		void set(uintptr_t base, uintptr_t new_value)
		{
			pointer_encryption::set(this->bind(base), new_value, this->enc);
		}
	};
}