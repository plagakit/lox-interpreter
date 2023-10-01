#include "environment.h"

#include "runtime_error.h"

auto Environment::environments = std::vector<std::shared_ptr<Environment>>();

Environment::Environment() :
	enclosing(nullptr)
{}

Environment::Environment(std::shared_ptr<Environment> parent) :
	enclosing(parent)
{}

void Environment::define(const std::string& name, const Object& value)
{
	values[name] = value;
}

void Environment::assign(const Token& name, const Object& value)
{
	auto find = values.find(name.getLexeme());
	if (find != values.end())
	{
		values[name.getLexeme()] = value;
		return;
	}

	if (enclosing)
	{
		enclosing->assign(name, value);
		return;
	}

	throw RuntimeError(name, "Undefined variable '" + name.getLexeme() + "'.");
}

Object Environment::get(const Token& name)
{
	auto find = values.find(name.getLexeme());
	if (find != values.end())
		return find->second;

	if (enclosing)
		return enclosing->get(name);

	throw RuntimeError(name, "Undefined variable '" + name.getLexeme() + "'.");
}