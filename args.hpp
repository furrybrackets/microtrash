#pragma once

typedef struct MArgs {
	const char* filepath;
	const char* type; // compress | remove | clean | list | show
	int cores; // up to 8, if not specified, -1
	const char* ct; // Compression type
} MArgs;

void parse_margs(MArgs* fmt, const char* src);
