#include "out.h"

namespace out {

std::string error(const std::string &str) {
    return ESC + "[1;31m" + str + ESC + "[0m";
}
std::string success(const std::string &str) {
    return ESC + "[32m" + str + ESC + "[0m";
}
std::string warn(const std::string &str) {
    return ESC + "[1;33m" + str + ESC + "[0m";
}

} // namespace out
