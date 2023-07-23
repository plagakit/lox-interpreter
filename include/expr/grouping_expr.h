#pragma once

#include "expr.h"

class GroupingExpr : public Expr {

public:
	const Expr& expression;

	GroupingExpr(Expr& expression);
	std::any accept(ExprVisitor& visitor) const override;

};