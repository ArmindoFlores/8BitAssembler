#include "exceptions.h"
#include <iostream>

void catchException(exception *exc, int line, int col, string *source) {
	string lineContent = "";
	int l = 1;
	for (int chr = 0; chr < source->size(); chr++) {
		if (source->at(chr) == '\n' && !(l == line)) {
			l++;
		}
		else if (source->at(chr) == '\n' && l == line) {
			break;
		}
		else if (l == line) {
			lineContent += source->at(chr);
		}
	}

	string padding = "";
	for (int i = 1; i < col; i++) padding += " ";

	cout << exc->what() << '\n';
	cout << "Line " << line << ", at\n";
	cout << lineContent << '\n';
	cout << padding << "^\n";
}