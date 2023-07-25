#pragma once

#include "expr_visitor.h"

class Expr {

public:
	virtual Object accept(ExprVisitor& visitor) const = 0;

};