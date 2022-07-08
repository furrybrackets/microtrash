#pragma once
#include <string>

typedef struct MArgs {
	string filepath;
	string type; // compress | remove | clean | list | show | return
	string ct; // Compression type
} MArgs;

void parse_margs(MArgs* fmt, string src);
