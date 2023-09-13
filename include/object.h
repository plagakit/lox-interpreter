#pragma once

#include <string>
#include <variant>
#include <memory>
class Callable;

using Object = std::variant<double, bool, std::string, std::monostate, std::shared_ptr<Callable>>;