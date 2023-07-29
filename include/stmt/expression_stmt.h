#pragma once

#include "stmt.h"
#include "expr/expr.h"

class ExpressionStmt : public Stmt {

public:
	const std::unique_ptr<Expr> expression;

	ExpressionStmt(std::unique_ptr<Expr>& expression);
	void accept(StmtVisitor& visitor) override;

};