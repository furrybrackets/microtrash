#include <stdio.h>
#include "args.hpp"
#include <iostream>
#include <filesystem>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <fstream>

int main(int argc, const char** argv) {
	if (argc < 2) {
		printf("%smicrotrash: version 1.0%s\nusage:\n\t'trash <FILE...>': push file(s) to trash. \n\n\t'trash compress': Compress trash directory into tar.gz file.\n\n\t'trash expand': Expand trash file out to directory. Run automatically on default 'trash <FILE...>' command if directory is compressed.\n",
			"\x1b[35;49m", "\x1b[39;49m");
		return 1; // bro, otherwise segfault LMAO

	}
        char* __HOMEDIR__ = "";
        if (getenv("HOME") == NULL) {
            __HOMEDIR__ = getpwuid(geteuid())->pw_dir;
        } else {
          __HOMEDIR__ = getenv("HOME");
        };
        const std::filesystem::path __TRASHDIR__ = std::filesystem::path(__HOMEDIR__) / ".trash";
        // check if .trash directory exists 
        if (!std::filesystem::exists(__TRASHDIR__)) {
          // create directory
          std::filesystem::create_directory(__TRASHDIR__);
          std::cout << "no trash directory. creating at: " << __TRASHDIR__ << std::endl;
        };
      	MArgs _args;
	parse_margs(&_args, argv, argc);
	
	std::cout << "\e[32;49m" << "filepath (absolute): " << "\e[0m" << (_args.filepath == "0" ? "none" : _args.filepath) << std::endl;
	std::cout << "\e[32;49m" << "command: " << "\e[0m" << (_args.type == "0" ? "trash file" : _args.type) << std::endl;
	std::cout << "\e[32;49m" << "compression type: " << "\e[0m" <<  (_args.ct == "0" ? "none" : _args.ct) << std::endl;
	std::cout << "\e[32;49m" << "output: " << "\e[0m" <<  (_args.output == "0" ? "none" : _args.output) << std::endl;

        // here's where the magic happens, first, clean
        if (_args.type == "clean") {
          // remove all files in directory. First ask for confirmation.
          std::filesystem::remove_all(__TRASHDIR__);
          return 0;
        }

        if (_args.type == "get") {
            // time to copy the files
          std::filesystem::copy(_args.filepath, _args.output);
          return 0;
        };

        if (_args.type == "0") {
          std::filesystem::copy(_args.filepath, __TRASHDIR__);
          return 0;
        }
        return 0;
};
