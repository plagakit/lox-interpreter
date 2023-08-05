#pragma once

#include "stmt.h"
#include "expr/expr.h"

class WhileStmt : public Stmt {

public:
	const std::unique_ptr<Expr> condition;
	const std::unique_ptr<Stmt> statement;

	WhileStmt(std::unique_ptr<Expr>& condition, std::unique_ptr<Stmt>& statement);
	void accept(StmtVisitor& visitor) override;

};