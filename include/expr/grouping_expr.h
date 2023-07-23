#pragma once

#include "expr.h"

class GroupingExpr : public Expr {

	const Expr& expression;

	GroupingExpr(Expr& expression);
	std::any accept(ExprVisitor& visitor) override;

};