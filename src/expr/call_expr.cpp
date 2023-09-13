#include "expr/call_expr.h"

CallExpr::CallExpr(std::unique_ptr<Expr>& callee, Token& paren, std::vector<std::unique_ptr<Expr>>& arguments) :
	callee(std::move(callee)), 
	paren(std::move(paren)), 
	arguments(std::move(arguments))
{}

Object CallExpr::accept(ExprVisitor& visitor)
{
	return visitor.visitCallExpr(*this);
}