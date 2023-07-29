#include "stmt/print_stmt.h"

PrintStmt::PrintStmt(std::unique_ptr<Expr>& expression) :
	expression(std::move(expression))
{}

void PrintStmt::accept(StmtVisitor& visitor)
{
	visitor.visitPrintStmt(*this);
}
