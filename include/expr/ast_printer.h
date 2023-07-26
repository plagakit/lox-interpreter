#pragma once

#include "expr/expr_visitor.h"
#include <string>
#include <memory>

class Expr;

class ASTPrinter : public ExprVisitor {

public:
	std::string print(const std::unique_ptr<Expr>& expr);

	Object visitAssignExpr(AssignExpr& expr) override;
	Object visitBinaryExpr(BinaryExpr& expr) override;
	Object visitGroupingExpr(GroupingExpr& expr) override;
	Object visitLiteralExpr(LiteralExpr& expr) override;
	Object visitUnaryExpr(UnaryExpr& expr) override;

	template<std::same_as<std::unique_ptr<Expr>>... U>
	Object parenthesize(std::string name, const U&... exprs);

	template <std::same_as<std::unique_ptr<Expr>>... U>
	std::string parenthesizeHelper(U const&... expr);

};