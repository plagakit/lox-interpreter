#include "expr/literal_expr.h"

LiteralExpr::LiteralExpr(Object value) :
	value(value) // copying faster than moving b/c std::variant is a union?
{}

Object LiteralExpr::accept(ExprVisitor& visitor)
{
	return visitor.visitLiteralExpr(*this);
}