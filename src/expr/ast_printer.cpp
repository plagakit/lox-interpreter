#include "expr/ast_printer.h"

#include "expr/assign_expr.h"
#include "expr/binary_expr.h"
#include "expr/call_expr.h"
#include "expr/grouping_expr.h"
#include "expr/literal_expr.h"
#include "expr/logical_expr.h"
#include "expr/unary_expr.h"
#include "expr/variable_expr.h"

#include "stmt/expression_stmt.h"
#include "stmt/print_stmt.h"
#include "stmt/var_stmt.h"
#include "stmt/block_stmt.h"
#include "stmt/if_stmt.h"
#include "stmt/while_stmt.h"
#include "stmt/function_stmt.h"
#include "stmt/return_stmt.h"

#include "utils.h"

std::string ASTPrinter::print(const std::unique_ptr<Expr>& expr)
{
	Object str = expr->accept(*this);
	return Utils::objectToString(str);
}

std::string ASTPrinter::print(const std::vector<std::unique_ptr<Stmt>>& stmts)
{
	stmtStream = {};
	for (auto& s : stmts)
		print(s);

	return stmtStream.str();
}

std::string ASTPrinter::print(const std::unique_ptr<Stmt>& stmt)
{
	stmt->accept(*this);
	return stmtStream.str();
}


// Expressions

Object ASTPrinter::visitAssignExpr(AssignExpr& expr)
{
	auto s = "assign " + expr.name.getLexeme() + " to: ";
	return wrapExpr(s, expr.value);
}

Object ASTPrinter::visitBinaryExpr(BinaryExpr& expr)
{
	return wrapExpr(expr.op.getLexeme(), expr.left, expr.right);
}

Object ASTPrinter::visitCallExpr(CallExpr& expr)
{
	auto args = std::string();
	if (expr.arguments.size() > 0)
		args = " with args ";

	for (auto& arg : expr.arguments)
		args += print(arg) + " ";

	return "(call " + wrapExprHelper(expr.callee) + args + ")";
}

Object ASTPrinter::visitGroupingExpr(GroupingExpr& expr)
{
	return wrapExpr("group", expr.expression);
}

Object ASTPrinter::visitLiteralExpr(LiteralExpr& expr)
{
	return wrapExpr(Utils::objectToString(expr.value));
}

Object ASTPrinter::visitLogicalExpr(LogicalExpr& expr)
{
	return wrapExpr(expr.op.getLexeme(), expr.left, expr.right);
}

Object ASTPrinter::visitUnaryExpr(UnaryExpr& expr)
{
	return wrapExpr(expr.op.getLexeme(), expr.value);
}

Object ASTPrinter::visitVariableExpr(VariableExpr& expr)
{
	return wrapExpr("var " + expr.name.getLexeme());
}


// Statements

void ASTPrinter::visitExpressionStmt(ExpressionStmt& stmt)
{
	stmtStream << "expr {" << print(stmt.expression) << "}; ";
}

void ASTPrinter::visitIfStmt(IfStmt& stmt)
{
	stmtStream << "if { ";
	print(stmt.thenBranch);
	stmtStream << "}"; 

	if (stmt.elseBranch)
	{
		stmtStream << " else { ";
		print(stmt.elseBranch);
		stmtStream << "}";
	}
	stmtStream << "; ";
}

void ASTPrinter::visitPrintStmt(PrintStmt& stmt)
{
	stmtStream << "printStmt; ";
}

void ASTPrinter::visitVarStmt(VarStmt& stmt)
{
	stmtStream << "varStmt; ";
}
void ASTPrinter::visitWhileStmt(WhileStmt& stmt)
{
	stmtStream << "while { ";
	print(stmt.statement);
	stmtStream << "}; ";
}

void ASTPrinter::visitBlockStmt(BlockStmt& stmt)
{
	stmtStream << "block { ";
	for (auto& s : stmt.statements)
		print(s);
	stmtStream << "}; ";
}

void ASTPrinter::visitFunctionStmt(FunctionStmt& stmt)
{
	stmtStream << "functionStmt { ";
	for (auto& s : stmt.body)
		print(s);
	stmtStream << "}; ";
}

void ASTPrinter::visitReturnStmt(ReturnStmt& stmt)
{
	stmtStream << "returnStmt; ";
}

// Helpers

template <std::same_as<std::unique_ptr<Expr>>... U>
Object ASTPrinter::wrapExpr(std::string name, U const&... exprsPack)
{
	std::ostringstream str;
	str << "(" << name;
	str << wrapExprHelper(exprsPack...);
	str << ")";
	return Object(str.str());
}

template <std::same_as<std::unique_ptr<Expr>>... U>
std::string ASTPrinter::wrapExprHelper(U const&... expr)
{
	if (sizeof...(expr) < 1) return "";
	return (Utils::objectToString(expr->accept(*this)) + ... + "");
}