#pragma once

#include "token.h"
#include <string>
#include <vector>
#include <unordered_map>

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

	const std::unordered_map<std::string, TokenType> keywords
	{
		{"and",    AND},
		{"class",  CLASS},
		{"else",   ELSE},
		{"false",  FALSE},
		{"for",    FOR},
		{"fun",    FUN},
		{"if",     IF},
		{"nil",    NIL},
		{"or",     OR},
		{"print",  PRINT},
		{"return", RETURN},
		{"super",  SUPER},
		{"this",   THIS},
		{"true",   TRUE},
		{"var",    VAR},
		{"while",  WHILE}
	};

	void scanToken();
	void addToken(TokenType type);
	void addToken(TokenType type, std::any literal);

	char advance();
	bool match(char expected);
	void string();
	void number();
	void identifier();

	bool isAtEnd() const;
	bool isDigit(char c) const;
	bool isAlpha(char c) const;
	bool isAlphaNumeric(char c) const;
	char peek() const;
	char peekNext() const;

};