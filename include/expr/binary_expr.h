#pragma once

#include "expr.h"
#include "token.h"

class BinaryExpr : public Expr {

public:
	const Expr& left;
	const Token op;
	const Expr& right;

	BinaryExpr(Expr& left, Token op, Expr& right);
	Object accept(ExprVisitor& visitor) const override;

};