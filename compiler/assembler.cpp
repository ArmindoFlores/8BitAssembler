#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <cctype>
#include <list>

using namespace std;

class Token {
public:
	int type, data, line;
	string sdata;

	Token(int _type, const int _line = 0, const int _data = 0, const string _sdata = "") {
		type = _type;
		data = _data;
		sdata = _sdata;
		line = _line;
	}

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
	KWNOT,
	KWCMP,
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
	KWPUSH,
	KWPOP,
	KWHLT,
	LABEL,
	REG,
	ADDR,
	INT,
	SEP,
	PROGMEM
};

enum mode {
	KEYWORD,
	OPERAND
};


bool is_number(const std::string& s)
{
	return !s.empty() && find_if(s.begin(),
		s.end(), [](unsigned char c) { return !isdigit(c); }) == s.end();
}

bool writeToFile(string filename, list<uint8_t> *byteCode) {
	fstream file;
	file.open(filename, ios::binary | ios::out);
	if (file.is_open()) {
		for (int i = 0; i < byteCode->size(); i--) {
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

bool addToken(string token, vector<Token> *tokenList, int line) {
	// Check if the token is a keyword
	Token t = getKeyWord(token);
	if (t.type != ERROR) {
		t.line = line;
		tokenList->push_back(t);
		return true;
	} // If not, check if it is a label
	else if (token[0] == '.') {
		t = Token(LABEL, line, -1, token.substr(1));
		tokenList->push_back(t);
		return true;
	} // Else, check if it's a number / register / address
	else if (token[0] == '$') {
		t = Token(ADDR, line, atoi(token.substr(1).c_str()));
		tokenList->push_back(t);
		return true;
	}
	else if (token[0] == '%') {
		t = Token(REG, line, atoi(token.substr(1).c_str()));
		tokenList->push_back(t);
		return true;
	}
	else if (is_number(token)) {
		t = Token(INT, line, atoi(token.c_str()));
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

bool isKeyWord(Token token) {
	return (1 <= token.type) && (token.type <= 25);
}

int getOperands(Token token) {
	if (token.type == KWADD || token.type == KWMOV || token.type == KWSUB || token.type == KWAND || token.type == KWOR || token.type == KWXOR || token.type == KWCMP) {
		return 2;
	}
	else if (token.type == KWRET || token.type == KWHLT) {
		return 0;
	}
	else {
		return 1;
	}
}

vector<Token> tokenize(string source) {
	map<string, int> labels;
	string buffer = "";
	vector<Token> tokens;
	int line = 1;
	int addr = 0;
	int operands;
	bool comment = false;

	for (int i = 0; i < source.size(); i++) {
		if (!comment) cout << source[i];
		if (source[i] == ' ' || source[i] == '\n' || source[i] == '\t') {
			if (!comment) {
				if (!addToken(buffer, &tokens, line)) {
					cout << "Error: couldn't decifer token \"" << buffer << "\" on line " << (line) << '\n';
				}
			}
			if (source[i] == '\n') {
				line++;
				comment = false;
			}
			buffer = "";
		}
		else if (source[i] == ',' && !comment) {
			if (!addToken(buffer, &tokens, line)) {
				cout << "Error: couldn't decifer token " << buffer << " on line " << (line) << '\n';
			}
			tokens.push_back(Token(SEP, line));
			buffer = "";
		}
		else if (source[i] == ';') {
			if (!addToken(buffer, &tokens, line)) {
				cout << "Error: couldn't decifer token " << buffer << " on line " << (line) << '\n';
			}
			buffer = ";";
			comment = true;
		}
		else {
			buffer += toupper(source[i]);
		}
	}
	return tokens;
}

list<uint8_t> getByteCode(Token keyword, int *operands, int *operandType) {
	list<uint8_t> byteCode;
	return byteCode;
}

list<uint8_t> parse(vector<Token> *tokens) {
	list<uint8_t> byteCode;
	map<string, uint8_t> labels;
	int mode = KEYWORD;
	Token keyword = -1;
	int operandCount = 0;
	int operands[2] = { 0, 0 };
	int operandType[2] = { 0, 0 };
	bool expectSep = false;

	for (int i = 0; i < tokens->size(); i++) {
		Token t = tokens->at(i);
		if (mode == KEYWORD) {
			cout << "Type: " << t.type << '\n';
			if (t.type == LABEL) {
				if (t.sdata != "") {
					labels[t.sdata] = t.data;
				}
				else {
					cout << "Error: Labels cannot be blank. Line: " << t.line << '\n';
				}
			}
			else if (isKeyWord(t)) {
				operandCount = getOperands(t);
				keyword = t;
				mode = OPERAND;
				expectSep = false;
			}
			else {
				cout << "Error: Expected a keyword, got an operand instead. Line: " << t.line << '\n';
				break;
			}
		}
		else if (mode == OPERAND) {
			cout << "Operand Count: " << operandCount << '\n';
			if (operandCount <= 0) {
				list<uint8_t> bc = getByteCode(keyword, operands, operandType);
				for (int i = 0; i < bc.size(); i++) {
					byteCode.push_back(bc.front());
					bc.pop_front();
				}
				operandCount = 0;
				mode = KEYWORD;
				i--;
				continue;
			}

			if (isKeyWord(t.type)) {
				cout << "Error: Expected an operand, got a keyword instead. Line: " << t.line << '\n';
				break;
			}

			if (t.type == REG && !expectSep) {
				int index = getOperands(keyword) - operandCount;
				operands[index] = t.data;
				operandType[index] = REG;
				expectSep = true;
				operandCount--;
			}
			else if (t.type == ADDR && !expectSep) {
				int index = getOperands(keyword) - operandCount;
				operands[index] = t.data;
				operandType[index] = ADDR;
				expectSep = true;
				operandCount--;
			}
			else if (t.type == INT && !expectSep) {
				int index = getOperands(keyword) - operandCount;
				operands[index] = t.data;
				operandType[index] = INT;
				expectSep = true;
				operandCount--;
			}
			else if (t.type == LABEL && !expectSep) {
				int index = getOperands(keyword) - operandCount;
				operands[index] = t.data;
				operandType[index] = PROGMEM;
				expectSep = true;
				operandCount--;
			}
			else if (expectSep) {
				if (!(t.type == SEP)) {
					cout << "Error: expected comma. Line: " << t.line << '\n';
					break;
				}
				expectSep = false;
			}
		}
	}
	return byteCode;
}



void printVector(vector<Token> *v) {
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

int main()
{
	vector<Token> tokens;
	list<uint8_t> byteCode;
	string filename;
	cout << "Filename: ";
	cin >> filename;

	string content = getFileContent(filename);

	if (content != "") {
		tokens = tokenize(content);
		printVector(&tokens);
		byteCode = parse(&tokens);
		if (writeToFile(filename + ".s", &byteCode)) {
			cout << "Done";
		}
		else {
			cout << "Error writing to file";
		}
	}
	else {
		cout << "Error opening file";
	}
}