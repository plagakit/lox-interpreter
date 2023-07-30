#pragma once

#include "stmt.h"
#include "expr/expr.h"
#include "token.h"

class VarStmt : public Stmt {

public:
	const Token name;
	const std::unique_ptr<Expr> initializer;

	VarStmt(Token& name, std::unique_ptr<Expr>& initializer);
	void accept(StmtVisitor& visitor) override;

};