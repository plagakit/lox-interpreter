#pragma once

#include "expr.h"

class GroupingExpr : public Expr {

public:
	const Expr& expression;

	GroupingExpr(Expr& expression);
	Object accept(ExprVisitor& visitor) const override;

};