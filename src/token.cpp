#include "token.h"

#include <sstream>

Token::Token(TokenType type, const std::string& lexeme, const Object& literal, int line) :
	type(type), 
	lexeme(lexeme), 
	literal(literal), 
	line(line)
{}

std::string Token::toString() const
{
	std::ostringstream ss;
	ss << tokenTypeNames.at(type) << " ";

	if (lexeme != "")
		ss << lexeme << " ";
	
	if (type == STRING)
		ss << std::get<std::string>(literal) << " ";
	else if (type == NUMBER)
		ss << std::get<double>(literal) << " ";

	ss << std::to_string(line);
	return ss.str();
}

TokenType Token::getType() const
{
	return type;
}

std::string Token::getLexeme() const
{
	return lexeme;
}

Object Token::getLiteral() const
{
	return literal;
}

int Token::getLine() const
{
	return line;
}