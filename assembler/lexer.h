#ifndef __LEXER_H_INCLUDED__
#define __LEXER_H_INCLUDED__

#include <string>
#include <vector>

using namespace std;

namespace lexer {

	class Token {
	public:
		int type, data, line, col;
		string sdata;

		Token(int _type, const int _line = 0, const int _col = 0, const int _data = 0, const string _sdata = "");
	};

	enum token {
		ERROR,
		KWMOV,
		KWADD,
		KWSUB,
		KWINC,
		KWDEC,
		KWSHL,
		KWSHR,
		KWAND,
		KWOR,
		KWXOR,
		KWCMP,
		KWPUSH,
		KWNOT,
		KWJMP,
		KWJC,
		KWJLT,
		KWJET,
		KWJGT,
		KWJZ,
		KWJNZ,
		KWJNC,
		KWCALL,
		KWRET,
		KWPOP,
		KWHLT,
		LABEL,
		REG,
		ADDR,
		INT,
		SEP
	};

	enum mode {
		KEYWORD,
		OPERAND
	};

	bool isKeyWord(Token token);
	Token getKeyWord(string keyword);
	bool addToken(string token, vector<Token> *tokenList, int line, int chr);
	vector<Token> tokenize(string source);
}

#endif