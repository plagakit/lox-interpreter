#include "parser.h"

#include "expr/assign_expr.h"
#include "expr/binary_expr.h"
#include "expr/unary_expr.h"
#include "expr/literal_expr.h"
#include "expr/logical_expr.h"
#include "expr/grouping_expr.h"
#include "expr/variable_expr.h"
#include "stmt/print_stmt.h"
#include "stmt/expression_stmt.h"
#include "stmt/var_stmt.h"
#include "stmt/block_stmt.h"
#include "stmt/if_stmt.h"
#include "lox.h"

Parser::Parser(const std::vector<Token>& tokens) :
	tokens(tokens)
{}

std::vector<std::unique_ptr<Stmt>> Parser::parse()
{
	auto statements = std::vector<std::unique_ptr<Stmt>>();
	while (!isAtEnd())
		statements.push_back(declaration());

	return statements;
}

std::unique_ptr<Expr> Parser::parseExpr()
{
	try {
		return expression();
	} catch (ParseError) {
		return nullptr;
	}
}

// EXPRESSIONS

// expression ::= assignment
std::unique_ptr<Expr> Parser::expression()
{
	return assignment();
}

// assignment ::= IDENTIFIER "=" assignment | equality ;
std::unique_ptr<Expr> Parser::assignment()
{
	auto expr = orExpr();

	if (match({ EQUAL }))
	{
		Token equals = previous();
		auto value = assignment();

		try
		{
			auto& varExpr = dynamic_cast<VariableExpr&>(*expr);
			Token name = varExpr.name;
			return std::make_unique<AssignExpr>(name, value);
		}
		catch (...)
		{
			error(equals, "Invalid assignment target.");
		}
	}

	return expr;

}

std::unique_ptr<Expr> Parser::orExpr()
{
	auto expr = andExpr();

	while (match({ OR }))
	{
		auto op = previous();
		auto right = equality();
		expr = std::make_unique<LogicalExpr>(expr, op, right);
	}

	return expr;
}

std::unique_ptr<Expr> Parser::andExpr()
{
	auto expr = equality();

	while (match({ AND }))
	{
		auto op = previous();
		auto right = equality();
		expr = std::make_unique<LogicalExpr>(expr, op, right);
	}

	return expr;
}

// equality ::= comparison ( ( "!=" | "==" ) comparison )* ;
std::unique_ptr<Expr> Parser::equality()
{
	std::unique_ptr<Expr> expr = comparison();

	while (match({ BANG_EQUAL, EQUAL_EQUAL }))
	{
		Token op = previous();
		std::unique_ptr<Expr> right = comparison();
		expr = std::make_unique<BinaryExpr>(expr, op, right);
	}

	return expr;
}

// comparison ::= term ( ( ">" | ">=" | "<" | "<=" ) term )* ;
std::unique_ptr<Expr> Parser::comparison()
{
	std::unique_ptr<Expr> expr = term();

	while (match({ GREATER, GREATER_EQUAL, LESS, LESS_EQUAL }))
	{
		Token op = previous();
		std::unique_ptr<Expr> right = term();
		expr = std::make_unique<BinaryExpr>(expr, op, right);
	}

	return expr;
}

// term	::= factor ( ( "+" | "-" ) factor )* ;
std::unique_ptr<Expr> Parser::term()
{
	std::unique_ptr<Expr> expr = factor();

	while (match({ PLUS, MINUS }))
	{
		Token op = previous();
		std::unique_ptr<Expr> right = factor();
		expr = std::make_unique<BinaryExpr>(expr, op, right);
	}

	return expr;
}

// factor ::= unary ( ( "*" | "/" ) unary )* ;
std::unique_ptr<Expr> Parser::factor()
{
	std::unique_ptr<Expr> expr = unary();

	while (match({ SLASH, STAR }))
	{
		Token op = previous();
		std::unique_ptr<Expr> right = unary();
		expr = std::make_unique<BinaryExpr>(expr, op, right);
	}

	return expr;
}

// unary ::= ( "!" | "-" ) unary | primary;
std::unique_ptr<Expr> Parser::unary()
{
	if (match({ BANG, MINUS }))
	{
		Token op = previous();
		std::unique_ptr<Expr> right = unary();
		return std::make_unique<UnaryExpr>(op, right);
	}

	return primary();
}

//primary :: = NUMBER | STRING | "true" | "false" | "nil" | "(" expression ")" | IDENTIFIER;
std::unique_ptr<Expr> Parser::primary()
{
	std::unique_ptr<Expr> expr = nullptr;
	
	if (match({ FALSE }))
		return std::make_unique<LiteralExpr>(false);
	
	if (match({ TRUE }))
		return std::make_unique<LiteralExpr>(true);
	
	if (match({ NIL }))
		return std::make_unique<LiteralExpr>(std::monostate());

	if (match({ NUMBER, STRING }))
		return std::make_unique<LiteralExpr>(previous().getLiteral());

	if (match({ LEFT_PAREN }))
	{
		std::unique_ptr<Expr> expr = expression();
		consume(RIGHT_PAREN, "Expect ')' after expression.");
		return std::make_unique<GroupingExpr>(expr);
	}

	if (match({ IDENTIFIER }))
	{
		auto name = previous(); // passing in previous() means passing in an rvalue to a lvalue-expecting method...
		return std::make_unique<VariableExpr>(name);
	}

	throw error(peek(), "Expect expression.");
}

// STATEMENTS

std::unique_ptr<Stmt> Parser::statement()
{
	if (match({ IF }))
		return ifStatement();
	
	if (match({ PRINT }))
		return printStatement();

	if (match({ LEFT_BRACE }))
		return blockStatement();

	return expressionStatement();
}

std::unique_ptr<Stmt> Parser::declaration()
{
	try
	{
		if (match({ VAR }))
			return varDeclaration();

		return statement();
	}
	catch (ParseError error)
	{
		synchronize();
		return nullptr;
	}
}

std::unique_ptr<Stmt> Parser::varDeclaration()
{
	Token name = consume(IDENTIFIER, "Expect variable name.");
	
	std::unique_ptr<Expr> initializer = nullptr;
	if (match({ EQUAL }))
		initializer = expression();

	consume(SEMICOLON, "Expect ';' after variable declaration.");
	return std::make_unique<VarStmt>(name, initializer);
}

std::unique_ptr<Stmt> Parser::printStatement()
{
	auto value = expression();
	consume(SEMICOLON, "Expect ';' after value.");
	return std::make_unique<PrintStmt>(value);
}

std::unique_ptr<Stmt> Parser::expressionStatement()
{
	auto value = expression();
	consume(SEMICOLON, "Expect ';' after value.");
	return std::make_unique<ExpressionStmt>(value);
}

std::unique_ptr<Stmt> Parser::blockStatement()
{
	return std::make_unique<BlockStmt>(block());
}


std::vector<std::unique_ptr<Stmt>> Parser::block()
{
	auto statements = std::vector<std::unique_ptr<Stmt>>();

	while (!check(RIGHT_BRACE) && !isAtEnd())
		statements.push_back(declaration());

	consume(RIGHT_BRACE, "Expect '}' after block.");
	return statements;
}

std::unique_ptr<Stmt> Parser::ifStatement()
{
	consume(LEFT_PAREN, "Expect '(' after 'if'.");
	auto condition = expression();
	consume(RIGHT_PAREN, "Expect ')' after if condition.");

	auto thenBranch = statement();
	auto elseBranch = std::unique_ptr<Stmt>(nullptr);
	if (match({ ELSE }))
		elseBranch = statement();

	return std::make_unique<IfStmt>(condition, thenBranch, elseBranch);
}


// HELPERS

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

Token Parser::consume(TokenType type, const std::string& message)
{
	if (check(type))
		return advance();

	throw error(peek(), message);
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


void Parser::synchronize()
{
	advance();

	while (!isAtEnd())
	{
		if (previous().getType() == SEMICOLON)
			return;

		switch (peek().getType())
		{
		case CLASS:
		case FUN:
		case VAR:
		case FOR:
		case IF:
		case WHILE:
		case PRINT:
		case RETURN:
			return;
		default:
			break;
		}

		advance();
	}
}

ParseError Parser::error(Token token, const std::string& message) const
{
	Lox::error(token, message);
	return ParseError();
}