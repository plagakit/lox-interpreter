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

	tokens.push_back(Token(END_OF_FILE, "", "", line));
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
		case 't':
			break;
		case '\n':
			line++;
			break;
		case '"': string(); break;
		default:
			Lox::error(line, "Unexpected character '" + std::string(1, c) + "'.");
			break;
	}
}

void Scanner::addToken(TokenType type)
{
	addToken(type, "");
}

void Scanner::addToken(TokenType type, std::any literal)
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
	addToken(STRING, std::make_any<std::string>(value));
}

bool Scanner::isAtEnd() const
{
	return current >= source.length();
}

char Scanner::peek() const
{
	if (isAtEnd())
		return '\0';
	return source[current];
}
