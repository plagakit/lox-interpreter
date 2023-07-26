#pragma once

#include "expr_visitor.h"
#include <memory>

class Expr {

public:
	virtual ~Expr() = default;
	virtual Object accept(ExprVisitor& visitor) = 0;

};