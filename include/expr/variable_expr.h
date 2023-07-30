#pragma once

#include "expr.h"
#include "token.h"

class VariableExpr : public Expr {

public:
	const Token name;

	VariableExpr(Token& name);
	Object accept(ExprVisitor& visitor) override;

};