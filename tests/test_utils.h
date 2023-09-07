#pragma once

#include "lox.h"
#include <sstream>
#include <iostream>

// Runs a string and returns the terminal output, without the \n at the end
static std::string process(const std::string& str)
{
	// Redirect std::cout
	std::stringstream buffer;
	std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

	// Process str
	Lox::run(str);

	// Get output, redirect back, return
	std::string text = buffer.str();
	if (text.size() > 0)
		text.pop_back();
	std::cout.rdbuf(old);
	return text;
}