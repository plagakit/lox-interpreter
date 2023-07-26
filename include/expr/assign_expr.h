#pragma once

#include "expr.h"
#include "token.h"

class AssignExpr : public Expr {

public:
	const Token name;
	const std::unique_ptr<Expr> value;

	AssignExpr(Token& name, std::unique_ptr<Expr>& value);
	Object accept(ExprVisitor& visitor) override;

};