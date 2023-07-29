#include "stmt/expression_stmt.h"

ExpressionStmt::ExpressionStmt(std::unique_ptr<Expr>& expression) :
	expression(std::move(expression))
{}

void ExpressionStmt::accept(StmtVisitor& visitor)
{
	visitor.visitExpressionStmt(*this);
}