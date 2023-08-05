#include "stmt/while_stmt.h"

WhileStmt::WhileStmt(std::unique_ptr<Expr>& condition, std::unique_ptr<Stmt>& statement) :
	condition(std::move(condition)),
	statement(std::move(statement))
{}

void WhileStmt::accept(StmtVisitor& visitor)
{
	visitor.visitWhileStmt(*this);
}