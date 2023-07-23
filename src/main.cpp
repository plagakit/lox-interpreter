#include <iostream>
#include "lox.h"

#include "expr/binary_expr.h"
#include "expr/assign_expr.h"
#include "expr/literal_expr.h"
#include "expr/grouping_expr.h"

int main(int argc, char* argv[])
{
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