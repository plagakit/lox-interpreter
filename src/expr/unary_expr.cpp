#include "expr/unary_expr.h"

UnaryExpr::UnaryExpr(Token op, Expr& value) :
	op(op), value(value)
{}

Object UnaryExpr::accept(ExprVisitor& visitor) const
{
	return visitor.visitUnaryExpr(*this);
}