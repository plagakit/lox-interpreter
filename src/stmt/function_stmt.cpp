#include "stmt/function_stmt.h"

FunctionStmt::FunctionStmt(Token& name, std::vector<Token>& parameters, std::vector<std::unique_ptr<Stmt>>& body) :
	name(std::move(name)),
	parameters(std::move(parameters)),
	body(std::move(body))
{}

void FunctionStmt::accept(StmtVisitor& visitor)
{
	visitor.visitFunctionStmt(*this);
}