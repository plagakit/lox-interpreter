#include "stmt/var_stmt.h"

VarStmt::VarStmt(Token& name, std::unique_ptr<Expr>& initializer) :
	name(std::move(name)), 
	initializer(std::move(initializer))
{}

void VarStmt::accept(StmtVisitor& visitor)
{
	visitor.visitVarStmt(*this);
}