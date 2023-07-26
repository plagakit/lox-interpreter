#include "expr/assign_expr.h"

AssignExpr::AssignExpr(Token& name, std::unique_ptr<Expr>& value) :
	name(std::move(name)), 
	value(std::move(value))
{}

Object AssignExpr::accept(ExprVisitor& visitor) 
{
	return visitor.visitAssignExpr(*this);
}

