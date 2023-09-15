#include "interpreter.h"

#include "lox.h"
#include "runtime_error.h"
#include "utils.h"
#include "object.h"
#include "callable.h"
#include "function.h"
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
#include <iostream>
#include <chrono>

Interpreter::Interpreter() :
	globals(std::make_shared<Environment>()),
	environment(globals)
{
	class ClockGlobal : public Callable {
	public:
		int arity() const override { return 0; }
		std::string toString() const override { return "<native fn>"; }
		Object call(Interpreter& interpreter, std::vector<Object>& arguments) override
		{
			return (double)(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
		}
	};

	class PingGlobal : public Callable {
	public:
		int arity() const override { return 0; }
		std::string toString() const override { return "<native fn>"; }
		Object call(Interpreter& interpreter, std::vector<Object>& arguments) override
		{
			std::cout << "Pong!\n";
			return std::monostate();
		}
	};

	class ClearGlobal : public Callable {
	public:
		int arity() const override { return 0; }
		std::string toString() const override { return "<native fn>"; }
		Object call(Interpreter& interpreter, std::vector<Object>& arguments) override
		{
			system("cls");
			return std::monostate();
		}
	};
	
	globals->define("clock", std::make_shared<ClockGlobal>());
	globals->define("ping", std::make_shared<PingGlobal>());
	globals->define("clear", std::make_shared<ClearGlobal>());
}

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
	Object value = evaluate(expr.value);
	environment->assign(expr.name, value);
	return value;
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

Object Interpreter::visitCallExpr(CallExpr& expr)
{
	Object callee = evaluate(expr.callee);

	std::vector<Object> arguments;
	for (auto& expr : expr.arguments)
		arguments.push_back(evaluate(expr));

	if (!std::holds_alternative<std::shared_ptr<Callable>>(callee))
		throw RuntimeError(expr.paren, "Can only call functions and classes.");

	auto function = std::get<std::shared_ptr<Callable>>(callee);
	return function->call(*this, arguments);
}

Object Interpreter::visitGroupingExpr(GroupingExpr& expr)
{
	return evaluate(expr.expression);
}

Object Interpreter::visitLiteralExpr(LiteralExpr& expr)
{
	return expr.value;
}

Object Interpreter::visitLogicalExpr(LogicalExpr& expr)
{
	Object left = evaluate(expr.left);

	if (expr.op.getType() == TokenType::OR)
	{
		if (isTruthy(left))
			return left;
	}
	else { // and
		if (!isTruthy(left))
			return left;
	}

	return evaluate(expr.right);
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
	return environment->get(expr.name);
}

// STATEMENTS

void Interpreter::visitExpressionStmt(ExpressionStmt& stmt)
{
	evaluate(stmt.expression);
}

void Interpreter::visitIfStmt(IfStmt& stmt)
{
	if (isTruthy(evaluate(stmt.condition)))
		execute(stmt.thenBranch);

	else if (stmt.elseBranch)
		execute(stmt.elseBranch);
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

	environment->define(stmt.name.getLexeme(), value);
}

void Interpreter::visitWhileStmt(WhileStmt& stmt)
{
	while (isTruthy(evaluate(stmt.condition)))
		execute(stmt.statement);
}

void Interpreter::visitBlockStmt(BlockStmt& stmt)
{
	auto newEnv = Environment(environment);
	executeBlock(stmt.statements, std::make_shared<Environment>(newEnv));
}

void Interpreter::visitFunctionStmt(FunctionStmt& stmt)
{
	auto fnStmt = std::make_unique<FunctionStmt>(std::move(stmt));
	auto function = std::make_shared<Function>(std::move(fnStmt));
	environment->define(stmt.name.getLexeme(), function);
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

void Interpreter::executeBlock(const std::vector<std::unique_ptr<Stmt>>& stmts, std::shared_ptr<Environment> newEnv)
{
	std::shared_ptr<Environment> temp = environment;
	try
	{
		environment = newEnv;

		for (auto& stmt : stmts)
			execute(stmt);

	}
	catch (RuntimeError e) 
	{ 
		environment = temp;
		throw e;
	}
	environment = temp;
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