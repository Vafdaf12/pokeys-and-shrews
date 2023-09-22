#pragma once

#include <string>

namespace out {
    
namespace {
const std::string ESC = "\x1b";
}

const std::string save_screen = ESC + "[?47h";
const std::string restore_screen=  ESC + "[?47l";
const std::string clear_screen=  ESC + "[2J";
const std::string home = ESC + "[H";

std::string error(const std::string &str);
std::string success(const std::string &str);
std::string warn(const std::string &str);

const std::string dim = ESC + "[90m";
const std::string reset_style = ESC + "[0m";

} // namespace out
