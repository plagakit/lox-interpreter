#pragma once

#include "expr.h"

class GroupingExpr : public Expr {

public:
	const std::unique_ptr<Expr> expression;

	GroupingExpr(std::unique_ptr<Expr>& expression);
	Object accept(ExprVisitor& visitor) override;

};