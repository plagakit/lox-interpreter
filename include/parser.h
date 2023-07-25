#pragma once

#include "token.h"
#include "expr/expr.h"
#include <vector>
#include <memory>

class Parser {

public:
	Parser(const std::vector<Token>& tokens);

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

	bool check(TokenType type) const;
	bool isAtEnd() const;
	Token peek() const;
	Token previous() const;

};