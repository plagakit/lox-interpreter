#include "scanner.h"

#include "lox.h"

Scanner::Scanner(const std::string& source) :
	source(source)
{}

std::vector<Token> Scanner::scanTokens()
{
	while (!isAtEnd())
	{
		start = current;
		scanToken();
	}

	tokens.push_back(Token(END_OF_FILE, "", std::monostate(), line));
	return tokens;
}

void Scanner::scanToken()
{
	char c = advance();
	switch (c)
	{
		case '(': addToken(LEFT_PAREN); break;
		case ')': addToken(RIGHT_PAREN); break;
		case '{': addToken(LEFT_BRACE); break;
		case '}': addToken(RIGHT_BRACE); break;
		case ',': addToken(COMMA); break;
		case '.': addToken(DOT); break;
		case '-': addToken(MINUS); break;
		case '+': addToken(PLUS); break;
		case ';': addToken(SEMICOLON); break;
		case '*': addToken(STAR); break;
		case '!':
			addToken(match('=') ? BANG_EQUAL : BANG);
			break;
		case '=':
			addToken(match('=') ? EQUAL_EQUAL : EQUAL);
			break;
		case '<':
			addToken(match('=') ? LESS_EQUAL : LESS);
			break;
		case '>':
			addToken(match('=') ? GREATER_EQUAL : GREATER);
			break;
		case '/':
			if (match('/'))
				while (peek() != 'n' && !isAtEnd()) advance();
			else
				addToken(SLASH);
			break;
		case ' ':
		case '\r':
		case '\t':
			break;
		case '\n':
			line++;
			break;
		case '"': string(); break;
		default:
			if (isDigit(c))
				number();
			else if (isAlpha(c))
				identifier();
			else
				Lox::error(line, "Unexpected character '" + std::string(1, c) + "'.");
			break;
	}
}

void Scanner::addToken(TokenType type)
{
	addToken(type, std::monostate());
}

void Scanner::addToken(TokenType type, Object literal)
{
	std::string text = source.substr(start, current-start);
	tokens.push_back(Token(type, text, literal, line));
}

char Scanner::advance()
{
	return source[current++];
}

bool Scanner::match(char expected)
{
	if (isAtEnd()) return false;
	if (source[current] != expected) return false;

	current++;
	return true;
}

void Scanner::string()
{
	while (peek() != '"' && !isAtEnd())
	{
		if (peek() == '\n')
			line++;
		advance();
	}

	if (isAtEnd())
	{
		Lox::error(line, "Unterminated string.");
		return;
	}

	advance();

	std::string value = source.substr(start + 1, current - start - 2);
	addToken(STRING, Object(value));
}

void Scanner::number()
{
	while (isDigit(peek()))
		advance();

	if (peek() == '.' && isDigit(peekNext()))
	{
		advance();
		while (isDigit(peek()))
			advance();
	}
	
	double value = std::stod(source.substr(start, current - start));           
	addToken(NUMBER, Object(value));
}

void Scanner::identifier()
{
	while (isAlphaNumeric(peek()))
		advance();

	std::string text = source.substr(start, current - start);
	TokenType type = IDENTIFIER;

	auto keyword = keywords.find(text);
	if (keyword != keywords.end())
	{
		type = keyword->second;
		
		if (type == TRUE)
		{
			addToken(type, true);
			return;
		}
		else if (type == FALSE)
		{
			addToken(type, false);
			return;
		}
		else if (type == NIL)
		{
			addToken(type, std::monostate());
			return;
		}
	}
		
	addToken(type);
}

bool Scanner::isAtEnd() const
{
	return current >= source.length();
}

bool Scanner::isDigit(char c) const
{
	return c >= '0' && c <= '9';
}

bool Scanner::isAlpha(char c) const
{
	return (c >= 'a' && c <= 'z')
		|| (c >= 'A' && c <= 'Z')
		|| c == '_';
}

bool Scanner::isAlphaNumeric(char c) const
{
	return isDigit(c) || isAlpha(c);
}

char Scanner::peek() const
{
	if (isAtEnd())
		return '\0';
	return source[current];
}

char Scanner::peekNext() const
{
	if (current + 1 >= source.length())
		return '\0';
	return source[current + 1];
}
