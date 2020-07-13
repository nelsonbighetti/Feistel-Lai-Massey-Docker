#include "Encryption.h"

void Encrypt(const std::string& path, 
	const std::string& path_key, 
	const std::string& output_path,
	bool display)
{
	const std::string key = core::ReadFile(path_key);
	if (key.size() != 4)
	{
		std::cout << "Key length must be 4 characters" << std::endl;
		return;
	}

	std::string plain_text = core::ReadFile(path), crypted_text;
	
	if (display)
		std::cout << "Open text : \n\n" << plain_text << std::endl;

	core::LastBlockSupplement(plain_text);

	for (auto it = plain_text.begin(); it != plain_text.end(); it += 4)
	{
		std::string block = plain_text.substr(it - plain_text.begin(), 4);
		crypted_text += core::EncryptBlock(block, key);
	}

	if(display)
		std::cout << std::endl << "Crypted text : \n" << crypted_text << std::endl;

	core::WriteFile(output_path, crypted_text);

	std::cout << "\nDone." << std::endl;
}

void Decrypt(const std::string& path,
	const std::string& path_key,
	const std::string& output_path,
	bool display, bool truncate)
{
	const std::string key = core::ReadFile(path_key);
	if (key.size() != 4)
	{
		std::cout << "Key length must be 4 characters" << std::endl;
		return;
	}

	std::string crypted_text = core::ReadFile(path), decrypted_text;
	if (display)
		std::cout << "Crypted text : \n\n" << crypted_text << std::endl;

	if (crypted_text.size() % 4)
	{
		std::cout << "crypted_text.size() % 4 is not zero" << std::endl;
		return;
	}

	for (auto it = crypted_text.begin(); it != crypted_text.end(); it += 4)
	{
		std::string block = crypted_text.substr(it - crypted_text.begin(), 4);
		decrypted_text += core::DecryptBlock(block, key);
	}

	if (truncate)
		core::LastBlockTruncate(decrypted_text);

	if (display)
		std::cout << std::endl << "\tDecrypted text:" << std::endl << decrypted_text << std::endl;

	core::WriteFile(output_path, decrypted_text);

	std::cout << "\nDone." << std::endl;
}
