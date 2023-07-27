#include "runtime_error.h"

RuntimeError::RuntimeError(const Token& token, const std::string& message) :
	token(token), message(message)
{}