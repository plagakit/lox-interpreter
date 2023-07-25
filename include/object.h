#pragma once

#include <string>
#include <variant>

using Object = std::variant<double, bool, std::string, std::monostate>;