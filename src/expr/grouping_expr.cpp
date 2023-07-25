#include "expr/grouping_expr.h"

GroupingExpr::GroupingExpr(Expr& expression) :
	expression(expression)
{}

Object GroupingExpr::accept(ExprVisitor& visitor) const
{
	return visitor.visitGroupingExpr(*this);
}