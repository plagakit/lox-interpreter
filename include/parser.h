#pragma once

#include "token.h"
#include "expr/expr.h"
#include <vector>
#include <memory>

struct ParseError {};

class Parser {

public:
	Parser(const std::vector<Token>& tokens);
	std::unique_ptr<Expr> parse();

private:
	const std::vector<Token>& tokens;
	int current = 0;

	std::unique_ptr<Expr> expression();
	std::unique_ptr<Expr> equality();
	std::unique_ptr<Expr> comparison();
	std::unique_ptr<Expr> term();
	std::unique_ptr<Expr> factor();
	std::unique_ptr<Expr> unary();
	std::unique_ptr<Expr> primary();

	Token advance();
	bool match(const std::vector<TokenType>& types);
	Token consume(TokenType type, const std::string& message);

	bool check(TokenType type) const;
	bool isAtEnd() const;
	Token peek() const;
	Token previous() const;

	void synchronize();
	ParseError error(Token token, const std::string& message) const;

};