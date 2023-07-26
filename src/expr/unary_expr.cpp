#include "expr/unary_expr.h"

UnaryExpr::UnaryExpr(Token& op, std::unique_ptr<Expr>& value) :
	op(std::move(op)), 
	value(std::move(value))
{}

Object UnaryExpr::accept(ExprVisitor& visitor)
{
	return visitor.visitUnaryExpr(*this);
}