#include "stmt/if_stmt.h"

IfStmt::IfStmt(std::unique_ptr<Expr>& condition, std::unique_ptr<Stmt>& thenBranch, std::unique_ptr<Stmt>& elseBranch) :
	condition(std::move(condition)),
	thenBranch(std::move(thenBranch)),
	elseBranch(std::move(elseBranch))
{}

void IfStmt::accept(StmtVisitor& visitor)
{
	visitor.visitIfStmt(*this);
}