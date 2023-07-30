#include "expr/variable_expr.h"

VariableExpr::VariableExpr(Token& name) :
	name(std::move(name))
{}

Object VariableExpr::accept(ExprVisitor& visitor)
{
	return visitor.visitVariableExpr(*this);
}