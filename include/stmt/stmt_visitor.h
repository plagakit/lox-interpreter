#pragma once

class ExpressionStmt;
class IfStmt;
class PrintStmt;
class VarStmt;
class WhileStmt;
class BlockStmt;
class FunctionStmt;

class StmtVisitor {

public:
	virtual ~StmtVisitor() = default;
	virtual void visitExpressionStmt(ExpressionStmt& stmt) = 0;
	virtual void visitIfStmt(IfStmt& stmt) = 0;
	virtual void visitPrintStmt(PrintStmt& stmt) = 0;
	virtual void visitVarStmt(VarStmt& stmt) = 0;
	virtual void visitWhileStmt(WhileStmt& stmt) = 0;
	virtual void visitBlockStmt(BlockStmt& stmt) = 0;
	virtual void visitFunctionStmt(FunctionStmt& stmt) = 0;

};