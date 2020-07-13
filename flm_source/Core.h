#pragma once

#include "BitsetTools.h"

#include <iostream>
#include <string>
#include <sstream> 
#include <fstream>

namespace core
{
	const unsigned char sub[16] = { 4,10,9,2,13,8,0,14,6,11,1,12,7,15,5,3 };

	std::string ReadFile(const std::string& filename);

	void WriteFile(const std::string& filename, const std::string& data);

	std::bitset<16> SP(std::bitset<16> right_block, const std::bitset<16> key);

	void Feistel(std::string& text, const std::string& key);

	void LaiMassey(std::string& text, const std::string& key);

	void TauSub(std::string& text);

	void LastBlockSupplement(std::string& opentext);

	void LastBlockTruncate(std::string& crypted_text);

	std::string EncryptBlock(const std::string& openblock, const std::string& key);

	std::string DecryptBlock(const std::string& crypted_block, const std::string& key);
}
