// args.hpp
#pragma once
#include <string>
#include <filesystem>

typedef struct MArgs {
	std::string filepath;
	std::string type; // compress | remove | clean | list | show | return
	std::string ct; // Compression type
} MArgs;

void parse_margs(MArgs* fmt, const char** src, int slen);
