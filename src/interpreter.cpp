#include "interpreter.h"

#include "runtime_error.h"
#include "expr/assign_expr.h"
#include "expr/binary_expr.h"
#include "expr/grouping_expr.h"
#include "expr/literal_expr.h"
#include "expr/unary_expr.h"

Object Interpreter::visitAssignExpr(AssignExpr& expr)
{
	return std::monostate();
}

Object Interpreter::visitBinaryExpr(BinaryExpr& expr)
{
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
	}

	return std::monostate();
}


Object Interpreter::evaluate(const std::unique_ptr<Expr>& expr)
{
	return expr->accept(*this);
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
	throw RuntimeError(token, "Operand(s) must be a number.");
}