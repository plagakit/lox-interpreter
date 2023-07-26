#include <iostream>
#include "lox.h"

int main(int argc, char* argv[])
{
	/*LiteralExpr a = LiteralExpr(Object(3.0));
	GroupingExpr g = GroupingExpr(a);
	UnaryExpr u = UnaryExpr(Token(TokenType::MINUS, "-", "", 1), a);

	BinaryExpr b = BinaryExpr(
		g,
		Token(TokenType::PLUS, "+", "", 1),
		u
	);


	ASTPrinter printer;
	std::cout << printer.print(b) << std::endl;
	*/
	
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