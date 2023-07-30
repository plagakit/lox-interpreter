#pragma once

class ExpressionStmt;
class PrintStmt;
class VarStmt;

class StmtVisitor {

public:
	virtual ~StmtVisitor() = default;
	virtual void visitExpressionStmt(ExpressionStmt& stmt) = 0;
	virtual void visitPrintStmt(PrintStmt& stmt) = 0;
	virtual void visitVarStmt(VarStmt& stmt) = 0;

};