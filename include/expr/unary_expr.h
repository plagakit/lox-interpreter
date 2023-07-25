#pragma once

#include "expr.h"
#include "token.h"

class UnaryExpr : public Expr {

public:
	const Token op;
	const Expr& value;

	UnaryExpr(Token op, Expr& value);
	Object accept(ExprVisitor& visitor) const override;

};