#include "expr/logical_expr.h"

LogicalExpr::LogicalExpr(std::unique_ptr<Expr>& left, Token& op, std::unique_ptr<Expr>& right) :
	left(std::move(left)), 
	op(std::move(op)),
	right(std::move(right))
{}

Object LogicalExpr::accept(ExprVisitor& visitor)
{
	return visitor.visitLogicalExpr(*this);
}