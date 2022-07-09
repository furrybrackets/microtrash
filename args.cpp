#include "args.hpp"

/* 
 * MArgs {
 *	std::string filepath;
 *	std::string type; // compress | remove | clean | list | show
 *	std::string ct; // Compression type
 *  }
 *
*/

void parse_margs(MArgs* fmt, std::string src) {
	MArgs _fmt;
	_fmt.filepath = "example";
	_fmt.type = "remove";
	_fmt.ct = "";
	*fmt=_fmt;
};
