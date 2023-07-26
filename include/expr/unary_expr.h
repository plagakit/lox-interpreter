#pragma once

#include "expr.h"
#include "token.h"

class UnaryExpr : public Expr {

public:
	const Token op;
	const std::unique_ptr<Expr> value;

	UnaryExpr(Token& op, std::unique_ptr<Expr>& value);
	Object accept(ExprVisitor& visitor) override;

};