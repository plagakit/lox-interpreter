#pragma once

#include <any>

class AssignExpr;
class BinaryExpr;
class GroupingExpr;
class LiteralExpr;

class ExprVisitor {

public:
	virtual std::any visitAssignExpr(AssignExpr expr);
	virtual std::any visitBinaryExpr(BinaryExpr expr);
	virtual std::any visitGroupingExpr(GroupingExpr expr);
	virtual std::any visitLiteralExpr(LiteralExpr expr);

};