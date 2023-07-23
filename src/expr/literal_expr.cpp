#include "expr/literal_expr.h"

LiteralExpr::LiteralExpr(std::any value) :
	value(std::move(value))
{}

std::any LiteralExpr::accept(ExprVisitor& visitor) const
{
	return visitor.visitLiteralExpr(*this);
}