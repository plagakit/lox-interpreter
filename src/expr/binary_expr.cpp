#include "expr/binary_expr.h"

BinaryExpr::BinaryExpr(std::unique_ptr<Expr>& left, Token& op, std::unique_ptr<Expr>& right) :
	left(std::move(left)), 
	op(std::move(op)),
	right(std::move(right))
{}

Object BinaryExpr::accept(ExprVisitor& visitor) 
{
	return visitor.visitBinaryExpr(*this);
}