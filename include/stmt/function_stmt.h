#pragma once

#include "stmt.h"
#include "token.h"
#include <vector>

class FunctionStmt : public Stmt {

public:
	const Token name;
	const std::vector<Token> parameters;
	std::vector<std::unique_ptr<Stmt>> body; // drop const to allow moving

	FunctionStmt(Token& name, std::vector<Token>& parameters, std::vector<std::unique_ptr<Stmt>>& body);
	void accept(StmtVisitor& visitor) override;

};