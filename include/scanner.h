#pragma once

#include "token.h"
#include <string>
#include <vector>

class Scanner {
	
public:
	Scanner(const std::string& source);
	std::vector<Token> scanTokens();

private:
	const std::string source;
	std::vector<Token> tokens;
	int start = 0;
	int current = 0;
	int line = 1;

	void scanToken();
	void addToken(TokenType type);
	void addToken(TokenType type, std::any literal);

	char advance();
	bool match(char expected);
	void string();
	bool isAtEnd() const;
	char peek() const;

};