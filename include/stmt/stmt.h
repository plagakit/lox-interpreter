#pragma once

#include "stmt_visitor.h"
#include <memory>

class Stmt {

public:
	virtual ~Stmt() = default;
	virtual void accept(StmtVisitor& visitor) = 0;

};