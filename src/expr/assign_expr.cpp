#include "expr/assign_expr.h"

AssignExpr::AssignExpr(Token name, Expr& value) :
	name(name), value(value)
{}

Object AssignExpr::accept(ExprVisitor& visitor) const
{
	return visitor.visitAssignExpr(*this);
}

