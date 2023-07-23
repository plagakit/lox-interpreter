#pragma once

#include "expr/expr_visitor.h"
#include <string>

class Expr;

class ASTPrinter : public ExprVisitor {

public:
	std::string print(Expr expr);

private:
	std::any visitAssignExpr(AssignExpr expr) override;
	std::any visitBinaryExpr(BinaryExpr expr) override;
	std::any visitGroupingExpr(GroupingExpr expr) override;
	std::any visitLiteralExpr(LiteralExpr expr) override;

	template<std::same_as<Expr>... U>
	std::any parenthesize(std::any name, U... exprs);

};