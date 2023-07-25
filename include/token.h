#pragma once

#include "token_type.h"
#include "object.h"

class Token {

public:
	Token(TokenType type, const std::string& lexeme, const Object& any, int line);
	std::string toString() const;

	TokenType getType() const;
	std::string getLexeme() const;
	Object getLiteral() const;
	int getLine() const;

private:
	const TokenType type;
	const std::string lexeme;
	const Object literal;
	const int line;

};