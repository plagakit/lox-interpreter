#include "expr/ast_printer.h"

#include "expr/expr.h"
#include "expr/assign_expr.h"
#include "expr/binary_expr.h"
#include "expr/grouping_expr.h"
#include "expr/literal_expr.h"
#include "expr/unary_expr.h"
#include <sstream>

std::string ASTPrinter::print(Expr& expr)
{
	std::any str = expr.accept(*this);
	return std::any_cast<std::string>(str);
}

std::any ASTPrinter::visitAssignExpr(AssignExpr expr)
{
	return parenthesize(std::string("assign " + expr.name.getLexeme() + " to: "), expr.value);
}

std::any ASTPrinter::visitBinaryExpr(BinaryExpr expr)
{
	return parenthesize(expr.op.getLexeme(), expr.left, expr.right);
}

std::any ASTPrinter::visitGroupingExpr(GroupingExpr expr)
{
	return parenthesize("group", expr.expression);
}

std::any ASTPrinter::visitLiteralExpr(LiteralExpr expr)
{
	return parenthesize(std::any_cast<std::string>(expr.value));
}

std::any ASTPrinter::visitUnaryExpr(UnaryExpr expr)
{
	return parenthesize(expr.op.getLexeme(), expr.value);
}

template <std::same_as<Expr>... U>
std::any ASTPrinter::parenthesize(std::string name, U const&... exprsPack)
{
	std::ostringstream str;
	str << "(" << name;
	str << parenthesizeHelper(exprsPack...);
	str << ")";
	return std::make_any<std::string>(str.str());
}

template <std::same_as<Expr>... U>
std::string ASTPrinter::parenthesizeHelper(U const&... expr)
{
	return (std::any_cast<std::string>(expr.accept(*this)) + ... + "");
}