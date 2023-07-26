#pragma once

#include "expr.h"

class LiteralExpr : public Expr {

public:
	const Object value;

	LiteralExpr(Object value);
	Object accept(ExprVisitor& visitor) override;

};