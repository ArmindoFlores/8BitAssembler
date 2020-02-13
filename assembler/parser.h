#ifndef __PARSER_H_INLCUDED__
#define __PARSER_H_INCLUDED__

#include "lexer.h"
#include <list>
#include <vector>
#include <map>

using namespace std;

namespace parser {

	list<uint8_t> getByteCode(lexer::Token keyword, int *operands, int *operandType, map<string, uint8_t> *labels);
	int getOperands(lexer::Token token);
	list<uint8_t> parse(vector<lexer::Token> *tokens, string *source);

}

#endif