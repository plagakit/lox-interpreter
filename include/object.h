#pragma once

#include <string>
#include <variant>

using Object = std::variant<double, std::string, std::monostate>;