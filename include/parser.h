#pragma once

#include "token.h"
#include "expr/expr.h"
#include "stmt/stmt.h"
#include <vector>
#include <memory>

struct ParseError {};

class Parser {

public:
	Parser(const std::vector<Token>& tokens);
	std::vector<std::unique_ptr<Stmt>> parse();
	std::unique_ptr<Expr> parseExpr();

private:
	const std::vector<Token>& tokens;
	int current = 0;

	std::unique_ptr<Expr> expression();
	std::unique_ptr<Expr> assignment();
	std::unique_ptr<Expr> orExpr();
	std::unique_ptr<Expr> andExpr();
	std::unique_ptr<Expr> equality();
	std::unique_ptr<Expr> comparison();
	std::unique_ptr<Expr> term();
	std::unique_ptr<Expr> factor();
	std::unique_ptr<Expr> unary();
	std::unique_ptr<Expr> primary();

	std::unique_ptr<Stmt> statement();
	std::unique_ptr<Stmt> declaration();
	std::unique_ptr<Stmt> varDeclaration();
	std::unique_ptr<Stmt> forStatement();
	std::unique_ptr<Stmt> ifStatement();
	std::unique_ptr<Stmt> printStatement();
	std::unique_ptr<Stmt> expressionStatement();
	std::unique_ptr<Stmt> whileStatement();

	std::unique_ptr<Stmt> blockStatement();
	std::vector<std::unique_ptr<Stmt>> block();

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