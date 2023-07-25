#include "expr/literal_expr.h"

LiteralExpr::LiteralExpr(Object value) :
	value(std::move(value))
{}

Object LiteralExpr::accept(ExprVisitor& visitor) const
{
	return visitor.visitLiteralExpr(*this);
}