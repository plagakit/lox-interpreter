#pragma once

#include "object.h"

class AssignExpr;
class BinaryExpr;
class GroupingExpr;
class LiteralExpr;
class UnaryExpr;

class ExprVisitor {

public:
	virtual ~ExprVisitor() = default;
	virtual Object visitAssignExpr(AssignExpr& expr) = 0;
	virtual Object visitBinaryExpr(BinaryExpr& expr) = 0;
	virtual Object visitGroupingExpr(GroupingExpr& expr) = 0;
	virtual Object visitLiteralExpr(LiteralExpr& expr) = 0;
	virtual Object visitUnaryExpr(UnaryExpr& expr) = 0;

};