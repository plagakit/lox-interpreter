#pragma once

#include "expr/expr_visitor.h"
#include "stmt/stmt_visitor.h"
#include "stmt/stmt.h"
#include <sstream>
#include <string>
#include <memory>
#include <vector>

class Expr;

class ASTPrinter : public ExprVisitor, public StmtVisitor {

public:
	std::string print(const std::unique_ptr<Expr>& expr);
	std::string print(const std::vector<std::unique_ptr<Stmt>>& stmt);
	std::string print(const std::unique_ptr<Stmt>& stmt);

private:
	std::stringstream stmtStream;

	Object visitAssignExpr(AssignExpr& expr) override;
	Object visitBinaryExpr(BinaryExpr& expr) override;
	Object visitCallExpr(CallExpr& expr) override;
	Object visitGroupingExpr(GroupingExpr& expr) override;
	Object visitLiteralExpr(LiteralExpr& expr) override;
	Object visitLogicalExpr(LogicalExpr& expr) override;
	Object visitUnaryExpr(UnaryExpr& expr) override;
	Object visitVariableExpr(VariableExpr& expr) override;

	void visitExpressionStmt(ExpressionStmt& stmt) override;
	void visitIfStmt(IfStmt& stmt) override;
	void visitPrintStmt(PrintStmt& stmt) override;
	void visitVarStmt(VarStmt& stmt) override;
	void visitWhileStmt(WhileStmt& stmt) override;
	void visitBlockStmt(BlockStmt& stmt) override;
	void visitFunctionStmt(FunctionStmt& stmt) override;
	void visitReturnStmt(ReturnStmt& stmt) override;

	template<std::same_as<std::unique_ptr<Expr>>... U>
	Object wrapExpr(std::string name, const U&... exprs);

	template <std::same_as<std::unique_ptr<Expr>>... U>
	std::string wrapExprHelper(U const&... expr);

};