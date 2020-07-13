#pragma once

#include "Core.h"
#include <string>

void Encrypt(const std::string& path,
	const std::string& path_key,
	const std::string& output_path,
	bool display = false);

void Decrypt(const std::string& path,
	const std::string& path_key,
	const std::string& output_path,
	bool display, bool truncate = true);