#pragma once


#include "expr/expr_visitor.h"
#include <memory>

class Token;
class Expr;

class Interpreter : public ExprVisitor {

public:
	Object visitAssignExpr(AssignExpr& expr);
	Object visitBinaryExpr(BinaryExpr& expr);
	Object visitGroupingExpr(GroupingExpr& expr);
	Object visitLiteralExpr(LiteralExpr& expr);
	Object visitUnaryExpr(UnaryExpr& expr);

private:
	Object evaluate(const std::unique_ptr<Expr>& expr);
	bool isTruthy(const Object& object);
	void checkNumberOperand(const Token& token, const Object& operand);

};