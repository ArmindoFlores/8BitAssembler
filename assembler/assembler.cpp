#include <iostream>
#include <string>
#include <vector>
#include <list>

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

		if (io::writeToFile(filename + ".bin", &byteCode)) {
		}
		else {
			cout << "Error writing to file";
		}
	}
	else {
		cout << "Error opening file";
	}
	return 0;
}