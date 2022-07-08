#include <stdio.h>

int main() {
	printf("microtrash: version 1.0\nusage:\n\t'trash <FILE...>': push file(s) to trash.\n\t\tflags: -r: removes file from directory\n\n\t'trash compress': Compress trash directory into tar.gz file.\n\n\t'trash expand': Expand trash file out to directory. Run automatically on default 'trash <FILE...>' command if directory is compressed.");
	return 0;
};
