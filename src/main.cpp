#include <iostream>
#include "lox.h"

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