#pragma once

#include "Base.hpp"

namespace TI4Echelon {

enum class Alignment : int8_t {
  Left,
  Center,
  Right,
};

template <>
const std::unordered_map<Alignment, std::string> labels<Alignment>{
    {Alignment::Left,   "Left"  },
    {Alignment::Center, "Center"},
    {Alignment::Right,  "Right" },
};

template <>
const std::unordered_map<std::string, Alignment> spellings<Alignment>{
    {"Left",   Alignment::Left  },
    {"Center", Alignment::Center},
    {"Right",  Alignment::Right },
};

const std::map<Alignment, std::string> markdown_alignments{
    {Alignment::Left,   ":---" },
    {Alignment::Center, ":---:"},
    {Alignment::Right,  "---:" },
};

std::string markdown(const Alignment alignment) noexcept {
  return markdown_alignments.find(alignment)->second;
}

}  // namespace TI4Echelon
