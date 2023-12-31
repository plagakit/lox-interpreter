#include "parser.h"

#include "expr/assign_expr.h"
#include "expr/binary_expr.h"
#include "expr/unary_expr.h"
#include "expr/literal_expr.h"
#include "expr/logical_expr.h"
#include "expr/grouping_expr.h"
#include "expr/variable_expr.h"
#include "expr/call_expr.h"
#include "stmt/print_stmt.h"
#include "stmt/expression_stmt.h"
#include "stmt/var_stmt.h"
#include "stmt/block_stmt.h"
#include "stmt/if_stmt.h"
#include "stmt/while_stmt.h"
#include "stmt/function_stmt.h"
#include "stmt/return_stmt.h"
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

	return call();
}

// call ::= primary ( "(" arguments? ")" )* ;
std::unique_ptr<Expr> Parser::call()
{
	auto expr = primary();

	while (true)
	{
		if (match({ LEFT_PAREN }))
			expr = finishCall(expr);
		else
			break;
	}

	return expr;
}

std::unique_ptr<Expr> Parser::finishCall(std::unique_ptr<Expr>& callee)
{
	std::vector<std::unique_ptr<Expr>> arguments;

	if (!check(RIGHT_PAREN))
	{
		do {
			if (arguments.size() >= 255)
				error(peek(), "Can't have more than 255 arguments.");
			arguments.push_back(expression());
		} while (match({ COMMA }));
	}

	Token paren = consume(RIGHT_PAREN, "Expected ')' after arguments to function call.");

	return std::make_unique<CallExpr>(callee, paren, arguments);
}

// primary :: = NUMBER | STRING | "true" | "false" | "nil" | "(" expression ")" | IDENTIFIER;
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
	if (match({ FOR }))		return forStatement();
	if (match({ IF }))		return ifStatement();
	if (match({ PRINT }))	return printStatement();
	if (match({ RETURN }))	return returnStatement();
	if (match({ WHILE }))	return whileStatement();

	if (match({ LEFT_BRACE }))	return blockStatement();

	return expressionStatement();
}

std::unique_ptr<Stmt> Parser::declaration()
{
	try
	{
		if (match({ FUN }))
			return function("function");
		
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

std::unique_ptr<Stmt> Parser::function(std::string kind)
{
	Token name = consume(IDENTIFIER, "Expect " + kind + " name.");
	
	consume(LEFT_PAREN, "Expect '(' after " + kind + " name.");

	std::vector<Token> parameters;
	if (!check(RIGHT_PAREN))
	{
		do 
		{
			if (parameters.size() >= 255)
				error(peek(), "Cannot have more than 255 parameters.");

			parameters.push_back(consume(IDENTIFIER, "Expect parameter name."));
		} 
		while (match({ COMMA }));
	}
	consume(RIGHT_PAREN, "Expect ')' after " + kind + " name.");

	consume(LEFT_BRACE, "Expect '{' before " + kind + " body.");
	auto body = block();
	
	return std::make_unique<FunctionStmt>(name, parameters, body);
}

std::unique_ptr<Stmt> Parser::forStatement()
{
	consume(LEFT_PAREN, "Expect '(' after 'for'.");

	// Initializer
	std::unique_ptr<Stmt> initializer;
	if (match({ SEMICOLON }))
		initializer = nullptr;
	else if (match({ VAR }))
		initializer = varDeclaration();
	else
		initializer = expressionStatement();

	// Condition
	std::unique_ptr<Expr> condition;
	if (!check(SEMICOLON))
		condition = expression();
	consume(SEMICOLON, "Expect ';' after loop condition.");

	// Increment
	std::unique_ptr<Expr> increment;
	if (!check(RIGHT_PAREN))
		increment = expression();
	
	// Body
	consume(RIGHT_PAREN, "Expect ')' after for clauses");
	std::unique_ptr<Stmt> body = statement();
	
	
	if (increment)
	{
		auto newBody = std::vector<std::unique_ptr<Stmt>>();
		newBody.push_back(std::move(body));
		newBody.push_back(std::make_unique<ExpressionStmt>(increment));
		body = std::make_unique<BlockStmt>(std::move(newBody));
	}
	
	if (condition == nullptr) condition = std::make_unique<LiteralExpr>(true);
	body = std::make_unique<WhileStmt>(condition, body);

	if (initializer)
	{
		auto newBody = std::vector<std::unique_ptr<Stmt>>();
		newBody.push_back(std::move(initializer));
		newBody.push_back(std::move(body));
		body = std::make_unique<BlockStmt>(std::move(newBody));
	}
	
	return body;
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

std::unique_ptr<Stmt> Parser::returnStatement()
{
	Token keyword = previous();
	std::unique_ptr<Expr> value = nullptr;
	if (!check(SEMICOLON))
		value = expression();

	consume(SEMICOLON, "Expect ';' after return value.");
	return std::make_unique<ReturnStmt>(keyword, value);
}

std::unique_ptr<Stmt> Parser::whileStatement()
{
	consume(LEFT_PAREN, "Expect '(' after 'while'.");
	auto condition = expression();
	consume(RIGHT_PAREN, "Expect ')' after condition.");
	auto body = statement();

	return std::make_unique<WhileStmt>(condition, body);
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