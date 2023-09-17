#include "stmt/return_stmt.h"

ReturnStmt::ReturnStmt(Token& keyword, std::unique_ptr<Expr>& value) :
	keyword(std::move(keyword)),
	value(std::move(value))
{}

void ReturnStmt::accept(StmtVisitor& visitor)
{
	visitor.visitReturnStmt(*this);
}
