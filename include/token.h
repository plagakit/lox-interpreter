#pragma once

#include "token_type.h"
#include <any>

class Token {

public:
	Token(TokenType type, const std::string& lexeme, const std::any& any, int line);
	std::string toString() const;

	TokenType getType() const;
	std::string getLexeme() const;
	std::any getLiteral() const;
	int getLine() const;

private:
	const TokenType type;
	const std::string lexeme;
	const std::any literal;
	const int line;

};