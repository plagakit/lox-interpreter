#include "token.h"

#include <sstream>

Token::Token(TokenType type, const std::string& lexeme, const std::any& literal, int line) :
	type(type), 
	lexeme(lexeme), 
	literal(literal), 
	line(line)
{}

std::string Token::toString() const
{
	std::ostringstream ss;
	ss << tokenTypeNames.at(type) << " ";
	ss << lexeme << " ";
	
	if (type == STRING)
		ss << std::any_cast<std::string>(literal);
	else if (type == NUMBER)
		ss << std::any_cast<double>(literal);
	else
		ss << "null";
	
	ss << " " << std::to_string(line);
	return ss.str();
}