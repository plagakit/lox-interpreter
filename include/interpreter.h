#pragma once

#include "expr/expr_visitor.h"
#include "stmt/stmt_visitor.h"
#include "environment.h"
#include <memory>
#include <vector>

class Token;
class Expr;
class Stmt;

class Interpreter : public ExprVisitor, public StmtVisitor {

public:
	void interpret(const std::vector<std::unique_ptr<Stmt>>& statements);

	Object visitAssignExpr(AssignExpr& expr) override;
	Object visitBinaryExpr(BinaryExpr& expr) override;
	Object visitGroupingExpr(GroupingExpr& expr) override;
	Object visitLiteralExpr(LiteralExpr& expr) override;
	Object visitLogicalExpr(LogicalExpr& expr) override;
	Object visitUnaryExpr(UnaryExpr& expr) override;
	Object visitVariableExpr(VariableExpr& expr) override;

	void visitExpressionStmt(ExpressionStmt& stmt) override;
	void visitPrintStmt(PrintStmt& stmt) override;
	void visitVarStmt(VarStmt& stmt) override;
	void visitBlockStmt(BlockStmt& stmt) override;
	void visitIfStmt(IfStmt& stmt) override;

private:
	Environment environment;

	Object evaluate(const std::unique_ptr<Expr>& expr);
	void execute(const std::unique_ptr<Stmt>& stmt);
	void executeBlock(const std::vector<std::unique_ptr<Stmt>>& stmts, Environment& newEnv);
	bool isTruthy(const Object& object);
	bool isEqual(const Object& a, const Object& b);
	void checkNumberOperand(const Token& token, const Object& operand);
	void checkNumberOperands(const Token& token, const Object& operand1, const Object& operand2);

};