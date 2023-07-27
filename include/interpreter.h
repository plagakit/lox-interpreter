#pragma once


#include "expr/expr_visitor.h"
#include <memory>

class Token;
class Expr;

class Interpreter : public ExprVisitor {

public:
	void interpret(const std::unique_ptr<Expr>& expression);

	Object visitAssignExpr(AssignExpr& expr);
	Object visitBinaryExpr(BinaryExpr& expr);
	Object visitGroupingExpr(GroupingExpr& expr);
	Object visitLiteralExpr(LiteralExpr& expr);
	Object visitUnaryExpr(UnaryExpr& expr);

private:
	Object evaluate(const std::unique_ptr<Expr>& expr);
	bool isTruthy(const Object& object);
	bool isEqual(const Object& a, const Object& b);
	void checkNumberOperand(const Token& token, const Object& operand);
	void checkNumberOperands(const Token& token, const Object& operand1, const Object& operand2);

};