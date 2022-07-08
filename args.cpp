#include <args.hpp>

/* 
 * MArgs {
 *	string filepath;
 *	string type; // compress | remove | clean | list | show
 *	string ct; // Compression type
 *  }
 *
*/

void parse_margs(MArgs* fmt, string src) {
	MArgs _fmt;
	_fmt.filepath = "example";
	_fmt.type = "remove";
	_fmt.ct = "";
	return _fmt;
};
