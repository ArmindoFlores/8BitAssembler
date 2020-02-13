#ifndef __IO_H_INLCUDED__
#define __IO_H_INCLUDED__

#include <string>
#include <list>

using namespace std;

namespace io {

	string getFileContent(string filename);
	bool writeToFile(string filename, list<uint8_t> *byteCode);

}

#endif