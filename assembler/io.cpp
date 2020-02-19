#include "io.h"
#include <fstream>
#include <iostream>

namespace io {
	void log(string message) {
		cout << message << endl;
	}

	bool writeToFile(string filename, list<uint8_t> *byteCode) {
		fstream file;
		file.open(filename, ios::binary | ios::out | ios::trunc);
		if (file.is_open()) {
			int size = byteCode->size();
			for (int i = 0; i < size; i++) {
				file << byteCode->front();
				byteCode->pop_front();
			}
			file.close();
			return true;
		}
		else {
			return false;
		}
	}

	string getFileContent(string filename) {
		string line;
		string content = "";
		ifstream file;
		file.open(filename);
		if (file.is_open()) {
			while (getline(file, line)) {
				content += line + "\n";
			}
			file.close();
			content += "\n";
			return content;
		}
		else {
			return "";
		}
	}


}