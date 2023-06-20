#pragma once

#include "Base.hpp"

namespace TI4Echelon {

enum class Color : int8_t {
  Red,
  Blue,
  Green,
  Yellow,
  Orange,
  Magenta,
  Cyan,
  Brown,
  Mint,
  Pink,
  White,
  Black,
  DarkGray,
  LightGray,
};

namespace {

const std::unordered_map<Color, std::string> color_codes{
    {Color::Red,       "e6194b"},
    {Color::Blue,      "4363d8"},
    {Color::Green,     "3cb44b"},
    {Color::Yellow,    "ffe119"},
    {Color::Orange,    "f58231"},
    {Color::Magenta,   "f032e6"},
    {Color::Cyan,      "42d4f4"},
    {Color::Brown,     "9a6324"},
    {Color::Mint,      "aaffc3"},
    {Color::Pink,      "fabed4"},
    {Color::White,     "ffffff"},
    {Color::Black,     "000000"},
    {Color::DarkGray,  "808080"},
    {Color::LightGray, "d3d3d3"},
};

}  // namespace

std::string color_code(const Color color) noexcept {
  const std::unordered_map<Color, std::string>::const_iterator found{
      color_codes.find(color)};
  if (found != color_codes.cend()) {
    return found->second;
  } else {
    return {};
  }
}

/// \brief Ordered sequence of colors for plot series.
const std::vector<Color> PlotDataColors{
    Color::Red,     Color::Blue,  Color::Green,   Color::Yellow, Color::Orange,
    Color::Magenta, Color::Cyan,  Color::Brown,   Color::Mint,   Color::Pink,
    Color::White,   Color::Black, Color::DarkGray};

Color plot_data_color(const std::size_t counter) noexcept {
  const std::size_t color_index{counter % PlotDataColors.size()};
  return PlotDataColors[color_index];
}

}  // namespace TI4Echelon
