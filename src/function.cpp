#include "function.h"

#include "interpreter.h"

#include "utils.h"
#include <iostream>

Function::Function(std::unique_ptr<FunctionStmt> declaration) :
	declaration(std::move(declaration))
{}

int Function::arity() const
{
	return declaration->parameters.size();
}

std::string Function::toString() const
{
	return "<fn " + declaration->name.getLexeme() + ">";
}

Object Function::call(Interpreter& interpreter, std::vector<Object>& arguments)
{
	auto env = std::make_shared<Environment>(interpreter.globals);
	Environment::environments.push_back(env);

	for (int i = 0; i < declaration->parameters.size(); i++)
		env->define(declaration->parameters[i].getLexeme(), arguments[i]);

	try { interpreter.executeBlock(declaration->body, env); }
	catch (Object value) { return value; } // catch a return value

	return std::monostate();
}