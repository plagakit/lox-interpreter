#include "utils.h"

std::string Utils::objectToString(Object object)
{
	if (std::holds_alternative<std::string>(object))
		return std::get<std::string>(object);

	else if (std::holds_alternative<double>(object))
		return std::to_string(std::get<double>(object));

	else if (std::holds_alternative<bool>(object))
		return std::to_string(std::get<bool>(object));

	else
		return "nil";
}