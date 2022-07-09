// args.cpp
#include "args.hpp"
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
/* 
 * MArgs {
 *	std::string filepath;
 *	std::string type; // compress | get | clean | list | show
 *	std::string ct; // Compression type
 *  }
 *
*/

void parse_margs(MArgs* fmt, const char** src, int slen) {
	// [argc == 1 without any other commands.]
	// argc == 2 implies command or file, let's check args[1]
	std::string cpsrc(src[1]);
	if (cpsrc != "compress" && cpsrc != "get" && cpsrc != "clean" && cpsrc != "list") {
		// expect file path, validate
		if (!std::filesystem::exists(src[1])) {
			// print error, exit 1
			printf("%serror: file does not exist. trash can't recycle a non-existent file, dummy!%s\n", "\e[31;49m", "\e[0m");
			printf("file: \e[34;3;4m%s\e[0m\n", src[1]);
			exit(1);
		}
		auto cpath = std::filesystem::canonical(src[1]);
		std::string fp(cpath);
		fmt->filepath = fp;
		fmt->type = "0";
		fmt->ct = "0";
		return;
	} else {
		// format.
		/* 
		 * clean: trash clean
		 * compress: trash compress [optional: -t=?]
		 * get: trash get <(FILE | DIRECTORY)...> [-o <OUTPUT_PATH>]
		 * list: trash list
		 * show: trash show <FILE>
		 */
		
		if("clean" == cpsrc) {
			fmt->type = "clean";
			fmt->filepath = "0";
			fmt->ct = "0";
		} else if ("compress" == cpsrc) {
			fmt->type = "compress";
			fmt->filepath = "0";
			// parse flags
			if (slen >= 3) {
				// check for t flag
				std::string t("-t");
				if (t == src[2]) {
					if (!(slen > 3)) {
						printf("\e[31;49mExpected compression type after '-t' flag!\e[0m\n");
						exit(1);
					};
					fmt->ct = src[3];
				} else {
					printf("\e[31;49mExpected '-t' flag!\e[0m\n");	
				}
			} else {
				fmt->ct = "tar";
			}
		} else if ("get" == cpsrc) {
			// get
			return;
		} else if ("list" == cpsrc) {
			// list
			return;
		} else if ("show" == cpsrc) { 
			// show
			return;
		} else {

			printf("\e[31;49mInvalid command! Expected: compress | get | clean | list | show\e[0m\n");
			exit(1);
		}
		return;
	}
};
