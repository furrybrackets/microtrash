// args.cpp
#include "args.hpp"
#include <fstream>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>

/* 
 * MArgs {
 *	std::string filepath;
 *	std::string type; // compress | get | clean | list | show
 *	std::string ct; // Compression type
 *  }
 *
*/


void parse_margs(MArgs* fmt, const char** src, int slen) {
      char* __HOMEDIR__ = "";
      if (getenv("HOME") == NULL) {
            __HOMEDIR__ = getpwuid(geteuid())->pw_dir;
      } else {
          __HOMEDIR__ = getenv("HOME");
      };
	// [argc == 1 without any other commands.]
	// argc == 2 implies command or file, let's check args[1]
	std::string cpsrc(src[1]);
	if (cpsrc != "compress" && cpsrc != "get" && cpsrc != "clean" && cpsrc != "list" && cpsrc != "clear") {
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
                fmt->output = "0";
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
		
		if("clean" == cpsrc || "clear" == cpsrc) {
			fmt->type = "clean";
			fmt->filepath = "0";
			fmt->ct = "0";
                        fmt->output = "0";
		} else if ("compress" == cpsrc) {
			fmt->type = "compress";
			fmt->filepath = "0";
                        fmt->output = "0";
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
                                        exit(1);
				}
			} else {
				fmt->ct = "tar";
			}
		} else if ("get" == cpsrc) {
			fmt->type = "get";
                        // parse filepath
                        // we expect arguments: trash get file
                        if (slen < 3) {
                            // print error
                            printf("\e[31;49mExpected input file after 'get' command!\e[0m\n");
                            exit(1);
                            return;
                        }
                        std::filesystem::path TRASHDIR = std::filesystem::path(__HOMEDIR__) / ".trash";
                        // search for file
                        std::filesystem::path LOCDIR = TRASHDIR / std::string(src[2]);
                        if (!std::filesystem::exists(LOCDIR)) {
                            printf("\e[31;49mFile: \e[34;49;3m%s\e[31;49m does not exist.\e[0m\n", src[2]);
                            exit(1);
                        }
                        fmt->filepath = std::string(LOCDIR);
                        if (slen < 4) {
                            printf("using default, cwd\n");
                            fmt->output = std::string(std::filesystem::current_path());
                        } else {
                          // check for existence
                          if (!std::filesystem::exists(src[3])) {
                              printf("\e[31;49mDirectory: \e[34;49;3m%s\e[0m\e[31;49m does not exist.\e[0m\n", src[3]);
                              exit(1);
                          }
                          fmt->output = src[3];
                        };
                        fmt->ct = "0";
		} else if ("list" == cpsrc) {
			fmt->type = "list";
                        if (slen < 3) {
                            printf("\e[34;49musing default, root directory.\e[0m\n");
                            fmt->filepath = std::string(std::filesystem::path(__HOMEDIR__) / ".trash");
                        } else {
                        // get absolute path
                        std::filesystem::path TRASHDIR = std::filesystem::path(__HOMEDIR__) / ".trash";
                        if (!std::filesystem::exists(TRASHDIR / src[2])) {
                            printf("\e[31;49mdirectory doesn't exist.\n");
                            exit(1);
                        };
                        fmt->filepath = src[2];
                      }
                        fmt->ct = "0";
                        fmt->output = "0";
                        fmt->filepath = std::string(std::filesystem::path(__HOMEDIR__) / ".trash");
		} else {

			printf("\e[31;49mInvalid command! Expected: compress | get | clean | list | show\e[0m\n");
			exit(1);
		}
		// return;
	}
}
