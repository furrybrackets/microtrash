#include <stdio.h>

int main(int argc, const char** argv) {
	if (argc < 2) {
		printf("%smicrotrash: version 1.0%s\nusage:\n\t'trash <FILE...>': push file(s) to trash.\n\t\tflags: -r: removes file from directory\n\n\t'trash compress': Compress trash directory into tar.gz file.\n\n\t'trash expand': Expand trash file out to directory. Run automatically on default 'trash <FILE...>' command if directory is compressed.",
			"\x1b[35;49m", "\x1b[39;49m");

	}

	// newline
	printf("\n");
	return 0;
};
