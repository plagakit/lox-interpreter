#pragma once

#include "expr/expr_visitor.h"
#include <string>

class Expr;

class ASTPrinter : public ExprVisitor {

public:
	std::string print(Expr& expr);

	Object visitAssignExpr(AssignExpr expr) override;
	Object visitBinaryExpr(BinaryExpr expr) override;
	Object visitGroupingExpr(GroupingExpr expr) override;
	Object visitLiteralExpr(LiteralExpr expr) override;
	Object visitUnaryExpr(UnaryExpr expr) override;

	template<std::same_as<Expr>... U>
	Object parenthesize(std::string name, const U&... exprs);

	template <std::same_as<Expr>... U>
	std::string parenthesizeHelper(U const&... expr);

};