#pragma once

#include "object.h"
#include "token.h"
#include <unordered_map>
#include <string>
#include <memory>
#include <vector>

class Environment {

public:
	Environment();
	Environment(std::shared_ptr<Environment> parent);
	static std::vector<std::shared_ptr<Environment>> environments;

	void define(const std::string& name, const Object& value);
	void assign(const Token& name, const Object& value);
	Object get(const Token& name);

private:
	std::shared_ptr<Environment> enclosing;
	std::unordered_map<std::string, Object> values;

};