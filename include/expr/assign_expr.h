#pragma once

#include "expr.h"
#include "token.h"

class AssignExpr : public Expr {

	const Token name;
	const Expr value;

	AssignExpr(Token name, Expr value);
	std::any accept(ExprVisitor visitor) override;

};