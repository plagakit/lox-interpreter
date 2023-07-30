#pragma once

#include "object.h"
#include "token.h"
#include <unordered_map>
#include <string>

class Environment {

public:
	void define(const std::string& name, const Object& value);
	Object get(const Token& name);

private:
	std::unordered_map<std::string, Object> values;

};