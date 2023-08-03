#pragma once

#include "stmt.h"
#include "expr/expr.h"
#include <vector>

class BlockStmt : public Stmt {

public:
	const std::vector<std::unique_ptr<Stmt>> statements;

	BlockStmt(std::vector<std::unique_ptr<Stmt>> statements);
	void accept(StmtVisitor& visitor) override;

};