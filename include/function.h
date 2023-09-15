#pragma once

#include "callable.h"
#include "stmt/function_stmt.h"

class Function : public Callable {

public:
	Function(std::unique_ptr<FunctionStmt> declaration);
	int arity() const override;
	std::string toString() const override;
	Object call(Interpreter& interpreter, std::vector<Object>& arguments) override;

private:
	std::unique_ptr<FunctionStmt> declaration;

};