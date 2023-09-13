#pragma once

#include "object.h"
#include <vector>
#include <string>

class Interpreter;

class Callable {

public:
	virtual ~Callable() = default;
	virtual int arity() const = 0;
	virtual std::string toString() const = 0;
	virtual Object call(Interpreter& interpreter, std::vector<Object>& arguments) = 0;

};