#pragma once

#include "expr_visitor.h"
#include <any>

class Expr {

public:
	virtual std::any accept(ExprVisitor& visitor) const = 0;

};