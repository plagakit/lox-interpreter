#pragma once

#include "expr.h"
#include "token.h"

class LogicalExpr : public Expr {

public:
	const std::unique_ptr<Expr> left;
	const Token op;
	const std::unique_ptr<Expr> right;

	LogicalExpr(std::unique_ptr<Expr>& left, Token& op, std::unique_ptr<Expr>& right);
	Object accept(ExprVisitor& visitor) override;

};