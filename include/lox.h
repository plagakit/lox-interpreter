#pragma once

#include <string>

class Token;

class Lox {
	
public:
	static void runFile(const std::string& path);
	static void runPrompt();

	static void error(int line, const std::string& message);
	static void error(Token token, const std::string& message);

private:
	static bool hadError;

	static void run(const std::string& source);
	static void report(int line, const std::string& where, const std::string& message);
};