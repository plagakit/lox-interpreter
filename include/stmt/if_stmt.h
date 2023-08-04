#pragma once

#include "stmt.h"
#include "expr/expr.h"
#include <vector>

class IfStmt : public Stmt {

public:
	const std::unique_ptr<Expr> condition;
	const std::unique_ptr<Stmt> thenBranch;
	const std::unique_ptr<Stmt> elseBranch;

	IfStmt(std::unique_ptr<Expr>& condition, std::unique_ptr<Stmt>& thenBranch, std::unique_ptr<Stmt>& elseBranch);
	void accept(StmtVisitor& visitor) override;

};