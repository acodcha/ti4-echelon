#pragma once

#include "Base.hpp"

namespace TI4Echelon {

enum class Color : int8_t {
  Red,
  Blue,
  Green,
  Yellow,
  Orange,
  Purple,
  Cyan,
  Magenta,
  Teal,
  Brown,
  Pink,
  Olive
};

template <> const std::unordered_map<Color, std::string> labels<Color>{
  {Color::Red, "Red"},
  {Color::Blue, "Blue"},
  {Color::Green, "Green"},
  {Color::Yellow, "Yellow"},
  {Color::Orange, "Orange"},
  {Color::Purple, "Purple"},
  {Color::Cyan, "Cyan"},
  {Color::Magenta, "Magenta"},
  {Color::Teal, "Teal"},
  {Color::Brown, "Brown"},
  {Color::Pink, "Pink"},
  {Color::Olive, "Olive"}
};

template <> const std::unordered_map<std::string, Color> spellings<Color>{
  {"Red", Color::Red},
  {"Blue", Color::Blue},
  {"Green", Color::Green},
  {"Yellow", Color::Yellow},
  {"Orange", Color::Orange},
  {"Purple", Color::Purple},
  {"Cyan", Color::Cyan},
  {"Magenta", Color::Magenta},
  {"Teal", Color::Teal},
  {"Brown", Color::Brown},
  {"Pink", Color::Pink},
  {"Olive", Color::Olive}
};

namespace {

const std::unordered_map<Color, std::string> color_codes{
  {Color::Red, "E6194B"},
  {Color::Blue, "0082C8"},
  {Color::Green, "3CB44B"},
  {Color::Yellow, "FFE119"},
  {Color::Orange, "F58231"},
  {Color::Purple, "911EB4"},
  {Color::Cyan, "46F0F0"},
  {Color::Magenta, "F032E6"},
  {Color::Teal, "008080"},
  {Color::Brown, "AA6E28"},
  {Color::Pink, "FABEBE"},
  {Color::Olive, "808000"}
};

} // namespace

std::string color_code(const Color color) noexcept {
  const std::unordered_map<Color, std::string>::const_iterator found{color_codes.find(color)};
  if (found != color_codes.cend()) {
    return found->second;
  } else {
    return {};
  }
}

/// \brief Ordered sequence of colors.
const std::vector<Color> Colors{
  Color::Red,
  Color::Blue,
  Color::Green,
  Color::Yellow,
  Color::Orange,
  Color::Purple,
  Color::Cyan,
  Color::Magenta,
  Color::Teal,
  Color::Brown,
  Color::Pink,
  Color::Olive
};

Color color(const std::size_t counter) noexcept {
  const std::size_t color_index{counter % Colors.size()};
  return Colors[color_index];
}

} // namespace TI4Echelon
