#include "interpreter.h"

#include "lox.h"
#include "runtime_error.h"
#include "utils.h"
#include "expr/assign_expr.h"
#include "expr/binary_expr.h"
#include "expr/grouping_expr.h"
#include "expr/literal_expr.h"
#include "expr/unary_expr.h"
#include "expr/variable_expr.h"
#include "stmt/expression_stmt.h"
#include "stmt/print_stmt.h"
#include "stmt/var_stmt.h"
#include <iostream>

void Interpreter::interpret(const std::vector<std::unique_ptr<Stmt>>& statements)
{
	try 
	{
		for (auto& statement : statements)
			execute(statement);
	}
	catch (RuntimeError error)
	{
		Lox::runtimeError(error);
	}
}

// EXPRESSIONS

Object Interpreter::visitAssignExpr(AssignExpr& expr)
{
	return std::monostate();
}

Object Interpreter::visitBinaryExpr(BinaryExpr& expr)
{
	Object left = evaluate(expr.left);
	Object right = evaluate(expr.right);

	switch (expr.op.getType())
	{
	case SLASH:
		checkNumberOperands(expr.op, left, right);
		return std::get<double>(left) / std::get<double>(right);
	
	case STAR:
		checkNumberOperands(expr.op, left, right);
		return std::get<double>(left) * std::get<double>(right);

	case MINUS:
		checkNumberOperands(expr.op, left, right);
		return std::get<double>(left) - std::get<double>(right);

	case PLUS:
		if (std::holds_alternative<double>(left)
			&& std::holds_alternative<double>(right))
			return std::get<double>(left) + std::get<double>(right);

		if (std::holds_alternative<std::string>(left)
			&& std::holds_alternative<std::string>(right))
			return std::get<std::string>(left) + std::get<std::string>(right);

		throw RuntimeError(expr.op, "Operands must be two numbers or two strings.");

	case GREATER:
		checkNumberOperands(expr.op, left, right);
		return std::get<double>(left) > std::get<double>(right);

	case GREATER_EQUAL:
		checkNumberOperands(expr.op, left, right);
		return std::get<double>(left) >= std::get<double>(right);

	case LESS:
		checkNumberOperands(expr.op, left, right);
		return std::get<double>(left) < std::get<double>(right);

	case LESS_EQUAL:
		checkNumberOperands(expr.op, left, right);
		return std::get<double>(left) <= std::get<double>(right);

	case BANG_EQUAL: return left != right;
	case EQUAL_EQUAL: return left == right;
	
	default: break;
	}

	return std::monostate();
}

Object Interpreter::visitGroupingExpr(GroupingExpr& expr)
{
	return evaluate(expr.expression);
}

Object Interpreter::visitLiteralExpr(LiteralExpr& expr)
{
	return expr.value;
}

Object Interpreter::visitUnaryExpr(UnaryExpr& expr)
{
	Object right = evaluate(expr.value);

	switch (expr.op.getType())
	{
	case MINUS:
		checkNumberOperand(expr.op, right);
		return -std::get<double>(right);
	
	case BANG:
		return !isTruthy(right);

	default: break;
	}

	return std::monostate();
}

Object Interpreter::visitVariableExpr(VariableExpr& expr)
{
	return environment.get(expr.name);
}

// STATEMENTS

void Interpreter::visitExpressionStmt(ExpressionStmt& stmt)
{
	evaluate(stmt.expression);
}

void Interpreter::visitPrintStmt(PrintStmt& stmt)
{
	Object value = evaluate(stmt.expression);
	std::cout << Utils::objectToString(value) << std::endl;
}

void Interpreter::visitVarStmt(VarStmt& stmt)
{
	Object value = std::monostate();
	if (stmt.initializer)
		value = evaluate(stmt.initializer);

	environment.define(stmt.name.getLexeme(), value);
}

// HELPERS

Object Interpreter::evaluate(const std::unique_ptr<Expr>& expr)
{
	return expr->accept(*this);
}

void Interpreter::execute(const std::unique_ptr<Stmt>& stmt)
{
	stmt->accept(*this);
}

bool Interpreter::isTruthy(const Object& object)
{
	if (std::holds_alternative<std::monostate>(object))
		return false;
	if (std::holds_alternative<bool>(object))
		return std::get<bool>(object);
	return true;
}

void Interpreter::checkNumberOperand(const Token& token, const Object& operand)
{
	if (std::holds_alternative<double>(operand))
		return;
	throw RuntimeError(token, "Operand must be a number.");
}

void Interpreter::checkNumberOperands(const Token& token, const Object& operand1, const Object& operand2)
{
	if (!std::holds_alternative<double>(operand1))
		throw RuntimeError(token, "Left operand must be a number.");
	if (!std::holds_alternative<double>(operand2))
		throw RuntimeError(token, "Right operand must be a number.");
}