#pragma once

#include <any>

class AssignExpr;
class BinaryExpr;
class GroupingExpr;
class LiteralExpr;
class UnaryExpr;

class ExprVisitor {

public:
	virtual std::any visitAssignExpr(AssignExpr expr) = 0;
	virtual std::any visitBinaryExpr(BinaryExpr expr) = 0;
	virtual std::any visitGroupingExpr(GroupingExpr expr) = 0;
	virtual std::any visitLiteralExpr(LiteralExpr expr) = 0;
	virtual std::any visitUnaryExpr(UnaryExpr expr) = 0;

};