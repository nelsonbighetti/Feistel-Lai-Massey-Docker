#include "Core.h"

namespace core
{
	std::string ReadFile(const std::string& filename)
	{
		std::ifstream file(filename, std::ios::binary);
		if (!file.is_open())
		{
			std::cout << "Error opening file" << std::endl; 
			return std::string();
		}
		std::stringstream ss;
		ss << file.rdbuf();
		return ss.str();
	}

	void WriteFile(const std::string& filename, const std::string& data)
	{
		std::ofstream file(filename, std::ios::binary);
		file.clear();
		file << data;
		file.close();
	}

	std::bitset<16> SP(std::bitset<16> right_block, const std::bitset<16> key)
	{
		std::bitset<4> new_right_little_endian; 
		std::bitset<16> tmp_result, result;

		right_block ^= key;

		//substisution 
		for (char i = 0; i < 4; i++)
		{
			for (char j = 0; j < 4; j++)
			{
				new_right_little_endian[3-j] = right_block[4 * i + j];
			}

			unsigned long tmp = new_right_little_endian.to_ulong(); //Obtaining result for Big-Endian
			tmp = sub[tmp];

			std::bitset<4> tmp_bitset_little_endian(tmp); 

			for (int j = 0; j < 4; j++)
			{
				tmp_result[4 * i + j] = tmp_bitset_little_endian[3-j];
			}
		}

		//permutation 
		for (int i = 0; i < 16; i++)
		{
			result[15-(13 * i + 7) % 16] = tmp_result[15-i];
		}

		return result;
	}

	void Feistel(std::string& text, const std::string& key)
	{
		auto block_x1 = bits::StringToBitset<16>(text.substr(0, 2));
		auto block_x2 = bits::StringToBitset<16>(text.substr(2, 2));
		text = bits::BitsetToString<16>(block_x2) + bits::BitsetToString<16>(block_x1 ^ SP(block_x2, bits::StringToBitset<16>(key)));
	}

	void LaiMassey(std::string& text, const std::string& key)
	{
		auto block_x1 = bits::StringToBitset<16>(text.substr(0, 2));
		auto block_x2 = bits::StringToBitset<16>(text.substr(2, 2));

		text = bits::BitsetToString<16>(block_x1 ^ SP(block_x1 ^ block_x2, bits::StringToBitset<16>(key))) +
			bits::BitsetToString<16>(block_x2 ^ SP(block_x2 ^ block_x1, bits::StringToBitset<16>(key)));
	}

	void TauSub(std::string& text)
	{
		text = text.substr(2, 2) + text.substr(0, 2);
	}

	void LastBlockSupplement(std::string& opentext)
	{
		int addition = (4 - (opentext.size() % 4)) % 4;
		if (addition)
			opentext.resize(opentext.size() + addition, 0);
		opentext.resize(opentext.size() + 3, 0);
		opentext.push_back(4-addition);
	}

	void LastBlockTruncate(std::string& crypted_text)
	{
		char count = 4 - (*(crypted_text.rbegin()));
		crypted_text.resize(crypted_text.size() - 4 - count);
	}

	std::string EncryptBlock(const std::string& openblock, const std::string& key)
	{
		const std::string first_key = key.substr(0, 2);
		const std::string second_key = key.substr(2, 2);
		std::string result = openblock;

		Feistel(result, first_key);
		Feistel(result, second_key);
		
		TauSub(result);

		LaiMassey(result, first_key);
		LaiMassey(result, second_key);

		return result;
	}

	std::string DecryptBlock(const std::string& crypted_block, const std::string& key)
	{
		auto subkey_1 = key.substr(0, 2);
		auto subkey_2 = key.substr(2, 2);
		std::string result = crypted_block;

		LaiMassey(result, subkey_2);
		LaiMassey(result, subkey_1);

		Feistel(result, subkey_2);
		Feistel(result, subkey_1);
		TauSub(result);

		return result;
	}
}