#include <vector>
#include "Encryption.h"


enum class Action
{
    Encrypt,
    Decrypt,
    Undefined
};

struct argsParsed
{
    std::vector<std::string> argsVec;
    Action number = Action::Undefined;
    bool verbose = false;
};

bool showHelp()
{
    std::cout << "Usage:\n" << std::endl;
    std::cout << "run -enc plain_text_path path_key crypted_text_path [-verbose]" << std::endl;
    std::cout << "run -dec crypted_text_path path_key decrypted_text_path [-verbose]" << std::endl;
    return false;
}

bool parseArgs(int argc, char** argv, argsParsed& args)
{
    if (argc < 3)
        return showHelp();

    std::vector<std::string> argsVecSource;
    for (int i = 0; i < argc; i++)
        argsVecSource.push_back(argv[i]);

    if (argsVecSource[1] == "run")
    {
        if (argsVecSource[2] == "-enc" || argsVecSource[2] == "-dec" || argsVecSource[2] == "-dec_weak")
        {
            if (argsVecSource[2] == "-enc")
                args.number = Action::Encrypt;
            else
                args.number = Action::Decrypt;

            if (argc < 6)
                return showHelp();

            for (int i = 3; i < 6; i++)
                args.argsVec.push_back(argsVecSource[i]);

            if (argc == 7 && argsVecSource[6] == "-verbose")
                args.verbose = true;

            return true;
        }
    }
    else
        return showHelp();
}

void EncRun(argsParsed args)
{
    std::string plain_text_path = args.argsVec[0];
    std::string path_key = args.argsVec[1];
    std::string crypted_text_path = args.argsVec[2];

    Encrypt(plain_text_path, path_key, crypted_text_path, args.verbose);
}

void DecRun(argsParsed args)
{
    std::string crypted_text_path = args.argsVec[0];
    std::string path_key = args.argsVec[1];
    std::string decrypted_text_path = args.argsVec[2];

    Decrypt(crypted_text_path, path_key, decrypted_text_path, args.verbose);
}

int main(int argc, char** argv)
{
    argsParsed args;
    if (parseArgs(argc, argv, args))
    {
        switch (args.number)
        {
        case Action::Encrypt:
            std::cout << "Encrypt" << std::endl;
            EncRun(args);
            break;

        case Action::Decrypt:
            std::cout << "Decrypt" << std::endl;
            DecRun(args);
            break;

        default:
            std::cout << "Unknown error" << std::endl;
        }
    }
    return 0;
}