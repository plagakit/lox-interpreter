#include "lox.h"

#include "scanner.h"
#include "token.h"
#include <iostream>
#include <vector>

bool Lox::hadError = false;

void Lox::runFile(const std::string& path)
{
	std::cout << "Running files is not implemented yet.\n";
}

void Lox::runPrompt()
{
	for (;;) {
		std::cout << "> ";
		
		std::string line;
		std::getline(std::cin, line);
		std::cout << line << std::endl;
		
		if (line == "") 
			break;

		run(line);
		hadError = false;
	}
}

void Lox::error(int line, const std::string& message)
{
	report(line, "", message);
}

void Lox::run(const std::string& source)
{
	Scanner scanner = Scanner(source);
	std::vector<Token> tokens = scanner.scanTokens();

	for (Token token : tokens)
	{
		std::cout << token.toString() << std::endl;
	}
}

void Lox::report(int line, const std::string& where, const std::string& message)
{
	std::cerr << "[line " << std::to_string(line) << "] Error" << where << ": " << message << std::endl;
	hadError = true;
}


