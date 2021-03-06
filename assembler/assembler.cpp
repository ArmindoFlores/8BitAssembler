#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <algorithm>

#include "lexer.h"
#include "parser.h"
#include "io.h"

using namespace std;

void printVector(vector<lexer::Token> *v) {
	cout << "{";
	for (int i = 0; i < v->size(); i++) {
		cout << "(";
		cout << v->at(i).type;
		cout << ", ";
		cout << v->at(i).data;
		cout << ", ";
		cout << v->at(i).sdata;
		cout << ")";
		if (i + 1 < v->size()) cout << ", ";
	}
	cout << "}\n";
}

string getFilename(string filename) {
	reverse(filename.begin(), filename.end());
	int pos = filename.find('.');
	string new_filename = filename.substr(pos+1, filename.length());
	reverse(new_filename.begin(), new_filename.end());
	return new_filename + ".bin";
}

int main(int argc, char **argv)
{
	vector<lexer::Token> tokens;
	list<uint8_t> byteCode;
	string filename;

	if (argc == 2) {
		filename = argv[1];
	}
	else {
		cout << "Error: Wrong number of arguments\n";
		return -1;
	}

	string content = io::getFileContent(filename);

	if (content != "") {
		tokens = lexer::tokenize(content);

		byteCode = parser::parse(&tokens, &content);

		if (io::writeToFile(getFilename(filename), &byteCode)) {
		}
		else {
			cout << "Error writing to file\n";
		}
	}
	else {
		cout << "Error opening file\n";
	}
	return 0;
}