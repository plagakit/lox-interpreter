#include "expr/grouping_expr.h"

GroupingExpr::GroupingExpr(Expr& expression) :
	expression(expression)
{}

std::any GroupingExpr::accept(ExprVisitor& visitor)
{
	return visitor.visitGroupingExpr(*this);
}