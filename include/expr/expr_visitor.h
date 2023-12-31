#pragma once

#include "object.h"

class AssignExpr;
class BinaryExpr;
class CallExpr;
class GroupingExpr;
class LiteralExpr;
class LogicalExpr;
class UnaryExpr;
class VariableExpr;

class ExprVisitor {

public:
	virtual ~ExprVisitor() = default;
	virtual Object visitAssignExpr(AssignExpr& expr) = 0;
	virtual Object visitBinaryExpr(BinaryExpr& expr) = 0;
	virtual Object visitCallExpr(CallExpr& expr) = 0;
	virtual Object visitGroupingExpr(GroupingExpr& expr) = 0;
	virtual Object visitLiteralExpr(LiteralExpr& expr) = 0;
	virtual Object visitLogicalExpr(LogicalExpr& expr) = 0;
	virtual Object visitUnaryExpr(UnaryExpr& expr) = 0;
	virtual Object visitVariableExpr(VariableExpr& expr) = 0;

};