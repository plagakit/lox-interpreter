#pragma once

#include "token.h"
#include <string>

class RuntimeError {

	const Token token;
	const std::string message;

public:
	RuntimeError(const Token& token, const std::string& message);

};

