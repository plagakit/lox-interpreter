#include "utils.h"

#include <iostream>

std::string Utils::objectToString(Object object)
{
	if (std::holds_alternative<std::string>(object))
		return std::get<std::string>(object);

	else if (std::holds_alternative<double>(object))
		return std::to_string(std::get<double>(object));

	else if (std::holds_alternative<bool>(object))
		return std::get<bool>(object) ? "true" : "false";
	
	else
		return "nil";
}