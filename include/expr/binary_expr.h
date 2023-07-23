#pragma once

#include "expr.h"
#include "token.h"

class BinaryExpr : public Expr {

	const Expr& left;
	const Token op;
	const Expr& right;

	BinaryExpr(Expr& left, Token op, Expr& right);
	std::any accept(ExprVisitor& visitor) override;

};