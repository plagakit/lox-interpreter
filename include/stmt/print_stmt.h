#pragma once

#include "stmt.h"
#include "expr/expr.h"

class PrintStmt : public Stmt {

public:
	const std::unique_ptr<Expr> expression;

	PrintStmt(std::unique_ptr<Expr>& expression);
	void accept(StmtVisitor& visitor) override;

};