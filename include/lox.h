#pragma once

#include "runtime_error.h"
#include <string>

class Token;
class Interpreter;

class Lox {

public:
	static void runFile(const std::string& path);
	static void runPrompt();
	static void run(const std::string& source);

	static void error(int line, const std::string& message);
	static void error(Token token, const std::string& message);
	static void runtimeError(RuntimeError error);

private:
	static bool hadError;
	static bool hadRuntimeError;

	static Interpreter interpreter;

	static void report(int line, const std::string& where, const std::string& message);
};