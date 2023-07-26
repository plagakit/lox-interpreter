#include "expr/grouping_expr.h"

GroupingExpr::GroupingExpr(std::unique_ptr<Expr>& expression) :
	expression(std::move(expression))
{}

Object GroupingExpr::accept(ExprVisitor& visitor)
{
	return visitor.visitGroupingExpr(*this);
}