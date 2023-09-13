#pragma once

#include "Base.hpp"

namespace TI4Echelon {

// First half as opposed to second half. Used to split the various faction plots
// into two, since there are too many factions for a single plot.
enum class Half : int8_t {
  First = 1,
  Second = 2,
};

template <>
const std::unordered_map<Half, std::string> labels<Half>{
    {Half::First,  "1"},
    {Half::Second, "2"},
};

template <>
const std::unordered_map<std::string, Half> spellings<Half>{
    {"1", Half::First },
    {"2", Half::Second},
};

}  // namespace TI4Echelon
