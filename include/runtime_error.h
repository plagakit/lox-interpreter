#pragma once

#include "token.h"
#include <string>

class RuntimeError {

public:
	const Token token;
	const std::string message;

	RuntimeError(const Token& token, const std::string& message);

};

