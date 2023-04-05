#include <fmt/core.h>
#include <string>

std::string bracketStr(const std::string str) {
    return fmt::format("[{}]", str);
}
