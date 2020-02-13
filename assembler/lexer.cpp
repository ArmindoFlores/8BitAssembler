#include "lexer.h"
#include "exceptions.h"
#include <algorithm>

bool is_number(const std::string& s)
{
	return !s.empty() && find_if(s.begin(),
		s.end(), [](unsigned char c) { return !isdigit(c); }) == s.end();
}

namespace lexer {
	Token::Token(int _type, const int _line, const int _col, const int _data, const string _sdata) {
		type = _type;
		data = _data;
		sdata = _sdata;
		line = _line;
		col = _col;
	}	

	bool isKeyWord(Token token) {
		return (1 <= token.type) && (token.type <= 25);
	}

	Token getKeyWord(string keyword) {
		if (keyword == "MOV") {
			return Token(KWMOV);
		}
		else if (keyword == "ADD") {
			return Token(KWADD);
		}
		else if (keyword == "SUB") {
			return Token(KWSUB);
		}
		else if (keyword == "INC") {
			return Token(KWINC);
		}
		else if (keyword == "DEC") {
			return Token(KWDEC);
		}
		else if (keyword == "SHL") {
			return Token(KWSHL);
		}
		else if (keyword == "SHR") {
			return Token(KWSHR);
		}
		else if (keyword == "AND") {
			return Token(KWAND);
		}
		else if (keyword == "OR") {
			return Token(KWOR);
		}
		else if (keyword == "XOR") {
			return Token(KWXOR);
		}
		else if (keyword == "NOT") {
			return Token(KWNOT);
		}
		else if (keyword == "CMP") {
			return Token(KWCMP);
		}
		else if (keyword == "JMP") {
			return Token(KWJMP);
		}
		else if (keyword == "JC") {
			return Token(KWJC);
		}
		else if (keyword == "JLT") {
			return Token(KWJLT);
		}
		else if (keyword == "JET") {
			return Token(KWJET);
		}
		else if (keyword == "JGT") {
			return Token(KWJGT);
		}
		else if (keyword == "JZ") {
			return Token(KWJZ);
		}
		else if (keyword == "JNZ") {
			return Token(KWJNZ);
		}
		else if (keyword == "JNC") {
			return Token(KWJNC);
		}
		else if (keyword == "CALL") {
			return Token(KWCALL);
		}
		else if (keyword == "RET") {
			return Token(KWRET);
		}
		else if (keyword == "PUSH") {
			return Token(KWPUSH);
		}
		else if (keyword == "POP") {
			return Token(KWPOP);
		}
		else if (keyword == "HLT") {
			return Token(KWHLT);
		}
		else {
			return ERROR;
		}
	}

	bool addToken(string token, vector<Token> *tokenList, int line, int chr) {
		// Check if the token is a keyword
		Token t = getKeyWord(token);
		if (t.type != ERROR) {
			t.line = line;
			tokenList->push_back(t);
			return true;
		} // If not, check if it is a label
		else if (token[0] == '.') {
			t = Token(LABEL, line, chr, -1, token.substr(1));
			tokenList->push_back(t);
			return true;
		} // Else, check if it's a number / register / address
		else if (token[0] == '$') {
			t = Token(ADDR, line, chr, atoi(token.substr(1).c_str()));
			tokenList->push_back(t);
			return true;
		}
		else if (token[0] == '%') {
			t = Token(REG, line, chr, atoi(token.substr(1).c_str()));
			tokenList->push_back(t);
			return true;
		}
		else if (is_number(token)) {
			t = Token(INT, line, chr, atoi(token.c_str()));
			tokenList->push_back(t);
			return true;
		}
		else if (token == "") {
			return true;
		}
		else if (token[0] == ';') {
			return true;
		}
		else {
			return false;
		}
	}

	vector<Token> tokenize(string source) {
		string buffer = "";
		vector<Token> tokens;

		int line = 1;
		int chr = 0;

		bool comment = false;

		try {
			for (int i = 0; i < source.size(); i++) {
				chr++;
				if (source[i] == ' ' || source[i] == '\n' || source[i] == '\t') {
					if (!comment) {
						if (!addToken(buffer, &tokens, line, chr)) {
							chr -= buffer.size();
							throw asmExceptions::invalidTokenException();
						}
					}
					if (source[i] == '\n') {
						line++;
						chr = 0;
						comment = false;
					}
					buffer = "";
				}
				else if (source[i] == ',' && !comment) {
					if (!addToken(buffer, &tokens, line, chr)) {
						chr -= buffer.size();
						throw asmExceptions::invalidTokenException();
					}
					tokens.push_back(Token(SEP, line, chr-1));
					buffer = "";
				}
				else if (source[i] == ';') {
					if (!addToken(buffer, &tokens, line, chr)) {
						chr -= buffer.size();
						throw asmExceptions::invalidTokenException();
					}
					buffer = ";";
					comment = true;
				}
				else {
					buffer += toupper(source[i]);
				}
			}
		}
		catch (exception &e) {
			catchException(&e, line, chr, &source);
		}
		return tokens;
	}
}