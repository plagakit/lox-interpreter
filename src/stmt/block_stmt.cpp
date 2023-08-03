#include "stmt/block_stmt.h"

BlockStmt::BlockStmt(std::vector<std::unique_ptr<Stmt>> statements) :
	statements(std::move(statements))
{}

void BlockStmt::accept(StmtVisitor& visitor) 
{
	visitor.visitBlockStmt(*this);
}
