#pragma once

#include "expr.h"
#include "token.h"

class AssignExpr : public Expr {

public:
	const Token name;
	const Expr& value;

	AssignExpr(Token name, Expr& value);
	Object accept(ExprVisitor& visitor) const override;

};