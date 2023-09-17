#pragma once

#include "stmt.h"
#include "token.h"
#include "expr/expr.h"

class ReturnStmt : public Stmt {

public:
	const Token keyword;
	const std::unique_ptr<Expr> value;

	ReturnStmt(Token& keyword, std::unique_ptr<Expr>& value);
	void accept(StmtVisitor& visitor) override;

};