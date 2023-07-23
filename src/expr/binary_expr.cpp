#include "expr/binary_expr.h"

BinaryExpr::BinaryExpr(Expr& left, Token op, Expr& right) :
	left(left), op(op), right(right)
{}

std::any BinaryExpr::accept(ExprVisitor& visitor) const
{
	return visitor.visitBinaryExpr(*this);
}