#include "ast_printer.h"

#include "expr/expr.h"
#include "expr/assign_expr.h"
#include "expr/binary_expr.h"
#include "expr/grouping_expr.h"
#include "expr/literal_expr.h"
#include <sstream>

std::string ASTPrinter::print(Expr expr)
{
	std::any str = expr.accept(*this);
	return std::any_cast<std::string>(str);
}

std::any ASTPrinter::visitAssignExpr(AssignExpr expr)
{
	return std::make_any<std::string>("");
}

std::any ASTPrinter::visitBinaryExpr(BinaryExpr expr)
{
	return std::make_any<std::string>("");
}

std::any ASTPrinter::visitGroupingExpr(GroupingExpr expr)
{
	return std::make_any<std::string>("");
}

std::any ASTPrinter::visitLiteralExpr(LiteralExpr expr)
{
	return std::make_any<std::string>("");
}

template<std::same_as<Expr>... U>
std::any ASTPrinter::parenthesize(std::any name, U... exprsPack)
{
	const int exprsCount = sizeof...(exprsPack);
	Expr exprs[exprsCount] = { exprsPack... };
	
	std::ostringstream str;
	str << "(" << std::any_cast<std::string>(name);


	

}