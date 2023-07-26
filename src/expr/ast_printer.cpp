#include "expr/ast_printer.h"

#include "expr/expr.h"
#include "expr/assign_expr.h"
#include "expr/binary_expr.h"
#include "expr/grouping_expr.h"
#include "expr/literal_expr.h"
#include "expr/unary_expr.h"
#include "utils.h"
#include <sstream>

std::string ASTPrinter::print(const std::unique_ptr<Expr>& expr)
{
	Object str = expr->accept(*this);
	return Utils::objectToString(str);
}

Object ASTPrinter::visitAssignExpr(AssignExpr& expr)
{
	return parenthesize(std::string("assign " + expr.name.getLexeme() + " to: "), expr.value);
}

Object ASTPrinter::visitBinaryExpr(BinaryExpr& expr)
{
	return parenthesize(expr.op.getLexeme(), expr.left, expr.right);
}

Object ASTPrinter::visitGroupingExpr(GroupingExpr& expr)
{
	return parenthesize("group", expr.expression);
}

Object ASTPrinter::visitLiteralExpr(LiteralExpr& expr)
{
	return parenthesize(Utils::objectToString(expr.value));
}

Object ASTPrinter::visitUnaryExpr(UnaryExpr& expr)
{
	return parenthesize(expr.op.getLexeme(), expr.value);
}

template <std::same_as<std::unique_ptr<Expr>>... U>
Object ASTPrinter::parenthesize(std::string name, U const&... exprsPack)
{
	std::ostringstream str;
	str << "(" << name;
	str << parenthesizeHelper(exprsPack...);
	str << ")";
	return Object(str.str());
}

template <std::same_as<std::unique_ptr<Expr>>... U>
std::string ASTPrinter::parenthesizeHelper(U const&... expr)
{
	if (sizeof...(expr) < 1) return "";
	return (Utils::objectToString(expr->accept(*this)) + ... + "");
}