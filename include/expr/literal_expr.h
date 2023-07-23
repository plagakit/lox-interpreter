#pragma once

#include "expr.h"

class LiteralExpr : public Expr {

public:
	const std::any value;

	LiteralExpr(std::any value);
	std::any accept(ExprVisitor& visitor) const override;

};