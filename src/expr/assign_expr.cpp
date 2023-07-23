#include "expr/assign_expr.h"

AssignExpr::AssignExpr(Token name, Expr& value) :
	name(name), value(value)
{}

std::any AssignExpr::accept(ExprVisitor& visitor) const
{
	return visitor.visitAssignExpr(*this);
}

