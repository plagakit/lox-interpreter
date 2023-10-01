#include "lox.h"

#include "scanner.h"
#include "parser.h"
#include "token.h"
#include "expr/expr.h"
#include "expr/ast_printer.h"
#include "interpreter.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

bool Lox::hadError = false;
bool Lox::hadRuntimeError = false;

Interpreter Lox::interpreter = Interpreter();

void Lox::runFile(const std::string& path)
{
	std::stringstream buffer;
	std::ifstream rfile;

	rfile.open(path);
	if (rfile.is_open())
	{
		buffer << rfile.rdbuf();
		run(buffer.str());
	}
	else
	{
		std::cout << "Error reading file.\n";
		exit(65);
	}
}

void Lox::runPrompt()
{
	for (;;) {
		std::cout << "> ";
		
		std::string line;
		std::getline(std::cin, line);
		//std::cout << line << std::endl;
		
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

void Lox::error(Token token, const std::string& message)
{
	if (token.getType() == TokenType::END_OF_FILE)
		report(token.getLine(), " at end", message);
	else
		report(token.getLine(), " at '" + token.getLexeme() + "'", message);
}

void Lox::runtimeError(RuntimeError error)
{
	std::cerr << error.message << "[line " << std::to_string(error.token.getLine()) << "]" << std::endl;
	hadRuntimeError = true;
}


void Lox::run(const std::string& source)
{
	Scanner scanner = Scanner(source);
	std::vector<Token> tokens = scanner.scanTokens();
	
	Parser parser = Parser(tokens);
	auto statements = parser.parse();

	if (hadError)
		return;

	//ASTPrinter astPrinter;
	//std::cout << astPrinter.print(statements) << "\n";

	interpreter.interpret(statements);
}

void Lox::report(int line, const std::string& where, const std::string& message)
{
	std::cerr << "[line " << std::to_string(line) << "] Error" << where << ": " << message << std::endl;
	hadError = true;
}


