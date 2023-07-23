#pragma once

#include "expr.h"

class LiteralExpr : public Expr {

	const std::any value;

	LiteralExpr(std::any value);
	std::any accept(ExprVisitor& visitor) override;

};