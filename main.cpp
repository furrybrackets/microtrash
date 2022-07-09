#include <stdio.h>
#include "args.hpp"
#include <iostream>

int main(int argc, const char** argv) {
	if (argc < 2) {
		printf("%smicrotrash: version 1.0%s\nusage:\n\t'trash <FILE...>': push file(s) to trash. \n\n\t'trash compress': Compress trash directory into tar.gz file.\n\n\t'trash expand': Expand trash file out to directory. Run automatically on default 'trash <FILE...>' command if directory is compressed.\n",
			"\x1b[35;49m", "\x1b[39;49m");
		return 1; // bro, otherwise segfault LMAO

	}

	MArgs _args;
	parse_margs(&_args, argv, argc);
	
	std::cout << "\e[32;49m" << "filepath (absolute): " << "\e[0m" << (_args.filepath == "0" ? "none" : _args.ct) << std::endl;
	std::cout << "\e[32;49m" << "command: " << "\e[0m" << _args.type << std::endl;
	std::cout << "\e[32;49m" << "compression type: " << "\e[0m" <<  (_args.ct == "0" ? "none" : _args.ct) << std::endl;
	return 0;
};
