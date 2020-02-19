#include "parser.h"
#include "exceptions.h"
#include <map>

namespace parser {
	list<uint8_t> getByteCode(lexer::Token keyword, int *operands, int *operandType, map<string, uint8_t> *labels) {
		list<uint8_t> byteCode;

		if (keyword.type == lexer::KWMOV) {
			if (operandType[0] == lexer::REG && operandType[1] == lexer::REG) {
				byteCode.push_back(lexer::KWMOV);
			}
			else if (operandType[0] == lexer::REG && operandType[1] == lexer::ADDR) {
				byteCode.push_back(lexer::KWMOV + 1);
			}
			else if (operandType[0] == lexer::REG && operandType[1] == lexer::INT) {
				byteCode.push_back(lexer::KWMOV + 2);
			}
			else if (operandType[0] == lexer::ADDR && operandType[1] == lexer::REG) {
				byteCode.push_back(lexer::KWMOV + 3);
			}
			else if (operandType[0] == lexer::ADDR && operandType[1] == lexer::INT) {
				byteCode.push_back(lexer::KWMOV + 4);
			}
			else {
				throw asmExceptions::invalidArgumentsException();
			}
		}
		else if (keyword.type == lexer::KWADD) {
			if (operandType[0] == lexer::REG && operandType[1] == lexer::REG) {
				byteCode.push_back(lexer::KWADD + 4);
			}
			else if (operandType[0] == lexer::REG && operandType[1] == lexer::ADDR) {
				byteCode.push_back(lexer::KWADD + 5);
			}
			else if (operandType[0] == lexer::REG && operandType[1] == lexer::INT) {
				byteCode.push_back(lexer::KWADD + 6);
			}
			else {
				throw asmExceptions::invalidArgumentsException();
			}
		}
		else if (keyword.type == lexer::KWSUB) {
			if (operandType[0] == lexer::REG && operandType[1] == lexer::REG) {
				byteCode.push_back(lexer::KWSUB + 6);
			}
			else if (operandType[0] == lexer::REG && operandType[1] == lexer::ADDR) {
				byteCode.push_back(lexer::KWSUB + 7);
			}
			else if (operandType[0] == lexer::REG && operandType[1] == lexer::INT) {
				byteCode.push_back(lexer::KWSUB + 8);
			}
			else {
				throw asmExceptions::invalidArgumentsException();
			}
		}
		else if (keyword.type == lexer::KWAND) {
			if (operandType[0] == lexer::REG && operandType[1] == lexer::REG) {
				byteCode.push_back(lexer::KWAND + 8);
			}
			else if (operandType[0] == lexer::REG && operandType[1] == lexer::ADDR) {
				byteCode.push_back(lexer::KWAND + 9);
			}
			else if (operandType[0] == lexer::REG && operandType[1] == lexer::INT) {
				byteCode.push_back(lexer::KWAND + 10);
			}
			else {
				throw asmExceptions::invalidArgumentsException();
			}
		}
		else if (keyword.type == lexer::KWOR) {
			if (operandType[0] == lexer::REG && operandType[1] == lexer::REG) {
				byteCode.push_back(lexer::KWOR + 10);
			}
			else if (operandType[0] == lexer::REG && operandType[1] == lexer::ADDR) {
				byteCode.push_back(lexer::KWOR + 11);
			}
			else if (operandType[0] == lexer::REG && operandType[1] == lexer::INT) {
				byteCode.push_back(lexer::KWOR + 12);
			}
			else {
				throw asmExceptions::invalidArgumentsException();
			}
		}
		else if (keyword.type == lexer::KWXOR) {
			if (operandType[0] == lexer::REG && operandType[1] == lexer::REG) {
				byteCode.push_back(lexer::KWXOR + 12);
			}
			else if (operandType[0] == lexer::REG && operandType[1] == lexer::ADDR) {
				byteCode.push_back(lexer::KWXOR + 13);
			}
			else if (operandType[0] == lexer::REG && operandType[1] == lexer::INT) {
				byteCode.push_back(lexer::KWXOR + 14);
			}
			else {
				throw asmExceptions::invalidArgumentsException();
			}
		}
		else if (keyword.type == lexer::KWCMP) {
			if (operandType[0] == lexer::REG && operandType[1] == lexer::REG) {
				byteCode.push_back(lexer::KWCMP + 14);
			}
			else if (operandType[0] == lexer::REG && operandType[1] == lexer::ADDR) {
				byteCode.push_back(lexer::KWCMP + 15);
			}
			else if (operandType[0] == lexer::REG && operandType[1] == lexer::INT) {
				byteCode.push_back(lexer::KWCMP + 16);
			}
			else {
				throw asmExceptions::invalidArgumentsException();
			}
		}
		else if (keyword.type == lexer::KWPUSH) {
			if (operandType[0] == lexer::REG && operandType[1] == -1) {
				byteCode.push_back(lexer::KWPUSH + 16);
			}
			else if (operandType[0] == lexer::ADDR && operandType[1] == -1) {
				byteCode.push_back(lexer::KWPUSH + 17);
			}
			else if (operandType[0] == lexer::INT && operandType[1] == -1) {
				byteCode.push_back(lexer::KWPUSH + 18);
			}
			else {
				throw asmExceptions::invalidArgumentsException();
			}
		}
		else if (keyword.type == lexer::KWINC || keyword.type == lexer::KWDEC || keyword.type == lexer::KWNOT || keyword.type == lexer::KWSHL || keyword.type == lexer::KWSHR || keyword.type == lexer::KWPOP) {
			if (operandType[0] == lexer::REG && operandType[1] == -1) {
				byteCode.push_back(keyword.type + 18);
			}
			else {
				throw asmExceptions::invalidArgumentsException();
			}
		}
		else if (keyword.type == lexer::KWCALL || keyword.type == lexer::KWJMP || keyword.type == lexer::KWJC || keyword.type == lexer::KWJET || keyword.type == lexer::KWJGT || keyword.type == lexer::KWJLT || keyword.type == lexer::KWJNC || keyword.type == lexer::KWJNZ || keyword.type == lexer::KWJZ) {
			if (operandType[0] == lexer::ADDR && operandType[1] == -1) {
				byteCode.push_back(keyword.type + 18);
			}
			else {
				throw asmExceptions::invalidArgumentsException();
			}
		}
		else {
			if (operandType[0] == -1 && operandType[1] == -1) {
				byteCode.push_back(keyword.type + 18);
			}
			else {
				throw asmExceptions::invalidArgumentsException();
			}
		}

		int ops = getOperands(keyword);
		for (int i = 0; i < ops; i++) {
			if (operandType[i] == -1) throw asmExceptions::invalidArgumentNumberException();
			byteCode.push_back(operands[i]);
		}

		return byteCode;
	}

	int getOperands(lexer::Token token) {
		if (token.type == lexer::KWADD || token.type == lexer::KWMOV || token.type == lexer::KWSUB || token.type == lexer::KWAND || token.type == lexer::KWOR || token.type == lexer::KWXOR || token.type == lexer::KWCMP) {
			return 2;
		}
		else if (token.type == lexer::KWRET || token.type == lexer::KWHLT) {
			return 0;
		}
		else {
			return 1;
		}
	}

	list<uint8_t> parse(vector<lexer::Token> *tokens, string *source) {
		list<uint8_t> byteCode;
		map<string, uint8_t> labels;

		int mode = lexer::KEYWORD;

		lexer::Token keyword = -1;
		lexer::Token t = lexer::Token(lexer::ERROR);

		int addr = -1;
		int operandCount = 0;
		int operands[2] = { 0, 0 };
		int operandType[2] = { -1, -1 };
		bool expectSep = false;

		try {
			// First iterate through every token and process labels
			for (int i = 0; i < tokens->size(); i++) {
				t = tokens->at(i);
				if (t.type == lexer::LABELDEF) {
					if (t.sdata != "") {
						labels[t.sdata] = addr + 1;
					}
				}
				else if (t.type != lexer::SEP) {
					addr++;
				}
			}

			addr = 0;

			// And then decode every other token
			for (int i = 0; i < tokens->size(); i++) {
				t = tokens->at(i);
				if (mode == lexer::KEYWORD) {
					if (t.type == lexer::LABELDEF) {
						if (t.sdata == "") {
							throw asmExceptions::blankLabelException();
						}
					}
					else if (t.type == lexer::LABELCALL) {
						throw asmExceptions::misplacedTokenException();
					}
					else if (isKeyWord(t)) {
						addr++;
						operandCount = getOperands(t);
						operandType[0] = -1;
						operandType[1] = -1;
						keyword = t;
						mode = lexer::OPERAND;
						expectSep = false;
					}
					else {
						throw asmExceptions::misplacedTokenException();
					}
				}
				else if (mode == lexer::OPERAND) {
					if (operandCount <= 0) {
						t = keyword;
						list<uint8_t> bc = getByteCode(keyword, operands, operandType, &labels);

						int size = bc.size();
						for (int i = 0; i < size; i++) {
							byteCode.push_back(bc.front());
							bc.pop_front();
						}
						operandCount = 0;
						mode = lexer::KEYWORD;
						i--;
						continue;
					}

					if (lexer::isKeyWord(t.type)) {
						throw asmExceptions::misplacedTokenException();
					}
					else {

						if (t.type == lexer::REG && !expectSep) {
							int index = getOperands(keyword) - operandCount;
							operands[index] = t.data;
							operandType[index] = lexer::REG;
							expectSep = true;
							operandCount--;
							addr++;
						}
						else if (t.type == lexer::ADDR && !expectSep) {
							int index = getOperands(keyword) - operandCount;
							operands[index] = t.data;
							operandType[index] = lexer::ADDR;
							expectSep = true;
							operandCount--;
							addr++;
						}
						else if (t.type == lexer::INT && !expectSep) {
							int index = getOperands(keyword) - operandCount;
							operands[index] = t.data;
							operandType[index] = lexer::INT;
							expectSep = true;
							operandCount--;
							addr++;
						}
						else if (t.type == lexer::LABELCALL && !expectSep) {
							int index = getOperands(keyword) - operandCount;
							operands[index] = labels[t.sdata];
							operandType[index] = lexer::ADDR;
							expectSep = true;
							operandCount--;
							addr++;
						}
						else if (expectSep) {
							if (!(t.type == lexer::SEP)) {
								throw asmExceptions::noSeparatorException();
							}
							expectSep = false;
						}
					}
				}

				if (mode == lexer::OPERAND) {
					if (operandCount <= 0) {
						t = keyword;
						list<uint8_t> bc = getByteCode(keyword, operands, operandType, &labels);
						int size = bc.size();
						for (int i = 0; i < size; i++) {
							byteCode.push_back(bc.front());
							bc.pop_front();
						}
						operandCount = 0;
						mode = lexer::KEYWORD;
					}
				}
			}
		}
		catch (exception &e) {
			catchException(&e, t.line, t.col, source);
		}
		return byteCode;
	}

}