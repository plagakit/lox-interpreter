#include "parser.h"

#include "expr/binary_expr.h"
#include "expr/unary_expr.h"
#include "expr/literal_expr.h"

Parser::Parser(const std::vector<Token>& tokens) :
	tokens(tokens)
{}

// expression ::= equality
std::shared_ptr<Expr> Parser::expression()
{
	return equality();
}

// equality ::= comparison ( ( "!=" | "==" ) comparison )* ;
std::shared_ptr<Expr> Parser::equality()
{
	std::shared_ptr<Expr> expr = comparison();

	while (match({ BANG_EQUAL, EQUAL_EQUAL }))
	{
		Token op = previous();
		std::shared_ptr<Expr> right = comparison();
		expr = BinaryExpr(expr, op, right);
	}

	return expr;
}

// comparison ::= term ( ( ">" | ">=" | "<" | "<=" ) term )* ;
Expr& Parser::comparison()
{
	Expr& expr = term();

	while (match({ GREATER, GREATER_EQUAL, LESS, LESS_EQUAL }))
	{
		Token op = previous();
		Expr& right = term();
		expr = BinaryExpr(expr, op, right);
	}

	return expr;
}

// term	::= factor ( ( "+" | "-" ) factor )* ;
Expr& Parser::term()
{
	Expr& expr = factor();

	while (match({ PLUS, MINUS }))
	{
		Token op = previous();
		Expr& right = factor();
		expr = BinaryExpr(expr, op, right);
	}

	return expr;
}

// factor ::= unary ( ( "*" | "/" ) unary )* ;
Expr& Parser::factor()
{
	Expr& expr = unary();

	while (match({ SLASH, STAR }))
	{
		Token op = previous();
		Expr& right = unary();
		expr = BinaryExpr(expr, op, right);
	}

	return expr;
}

// unary ::= ( "!" | "-" ) unary | primary;
Expr& Parser::unary()
{
	if (match({ BANG, MINUS }))
	{
		Token op = previous();
		Expr& right = unary();
		UnaryExpr newExpr = UnaryExpr(op, right);
		return newExpr;
	}

	return primary();
}

//primary :: = NUMBER | STRING | "true" | "false" | "nil" | "(" expression ")";
Expr& Parser::primary()
{
	Expr& expr = nullptr;
	if (match({ TRUE })) return std::make_shared<Expr>(LiteralExpr(false));
}


Token Parser::advance()
{
	if (!isAtEnd())
		current++;
	return previous();
}

bool Parser::match(const std::vector<TokenType>& types)
{
	for (TokenType type : types)
	{
		if (check(type))
		{
			advance();
			return true;
		}
	}
	return false;
}

bool Parser::check(TokenType type) const
{
	return peek().getType() == type;
}

bool Parser::isAtEnd() const
{
	return check(TokenType::END_OF_FILE);
}

Token Parser::peek() const
{
	return tokens[current];
}

Token Parser::previous() const
{
	return tokens[current - 1];
}