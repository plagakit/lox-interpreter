#include "environment.h"

#include "runtime_error.h"

void Environment::define(const std::string& name, const Object& value)
{
	values[name] = value;
}

Object Environment::get(const Token& name)
{
	auto find = values.find(name.getLexeme());
	if (find != values.end())
		return find->second;

	throw RuntimeError(name, "Undefined variable '" + name.getLexeme() + "'.");
}