#include "environment.hpp"

Environment::Environment(const std::string &display_value,
                         const Position &position)
    : Object(display_value, position) {}