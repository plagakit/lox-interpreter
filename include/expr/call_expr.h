#pragma once

#include "expr.h"
#include "token.h"

class CallExpr : public Expr {

public:
	const std::unique_ptr<Expr> callee;
	const Token paren;
	const std::vector<std::unique_ptr<Expr>> arguments;

	CallExpr(std::unique_ptr<Expr>& callee, Token& paren, std::vector<std::unique_ptr<Expr>>& arguments);
	Object accept(ExprVisitor& visitor) override;

};