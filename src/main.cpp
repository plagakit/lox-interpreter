#include <iostream>
#include "lox.h"

#include "expr/binary_expr.h"
#include "expr/unary_expr.h"
#include "expr/literal_expr.h"
#include "expr/grouping_expr.h"
#include "ast_printer.h"

int main(int argc, char* argv[])
{
	LiteralExpr a = LiteralExpr(std::make_any<std::string>("hello"));
	GroupingExpr g = GroupingExpr(a);
	UnaryExpr u = UnaryExpr(Token(TokenType::MINUS, "-", "", 1), a);

	BinaryExpr b = BinaryExpr(
		g,
		Token(TokenType::PLUS, "+", "", 1),
		u
	);

	ASTPrinter printer;
	std::cout << printer.print(b) << std::endl;
	
	if (argc > 2)
	{
		std::cout << "Usage: cpp-lox [script]\n";
		exit(64);
	}
	else if (argc == 2)
	{
		Lox::runFile(argv[1]);
	}
	else
	{
		Lox::runPrompt();
	}
}