#include "expr/binary_expr.h"

BinaryExpr::BinaryExpr(Expr& left, Token op, Expr& right) :
	left(left), op(op), right(right)
{}

std::any BinaryExpr::accept(ExprVisitor& visitor)
{
	return visitor.visitBinaryExpr(*this);
}