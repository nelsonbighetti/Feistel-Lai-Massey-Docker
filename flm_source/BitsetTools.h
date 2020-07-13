#pragma once

#include <bitset>
#include <string>

namespace bits
{
	template <int N>
	std::bitset<N> LittleBigConvert(const std::bitset<N>& bitsetLittleEndian)
	{
		std::bitset<N> bitsetBigEndian;
		for (auto bytes = 0; bytes < N / 8; bytes++)
			for (auto bits = 0; bits < 8; bits++)
				bitsetBigEndian[bytes * 8 + bits] = bitsetLittleEndian[(bytes + 1) * 8 - 1 - bits];

		return bitsetBigEndian;
	}

	template <int N>
	std::bitset<N> StringToBitset(const std::string& input)
	{
		auto val = (*((uint32_t*)input.c_str()));
		return LittleBigConvert<N>(std::bitset<N>(val));
	}

	template<int N>
	std::string BitsetToString(const std::bitset<N>& input)
	{
		auto val = LittleBigConvert<N>(input).to_ulong();
		return std::string((char*)&val, N / 8);
	}
}
