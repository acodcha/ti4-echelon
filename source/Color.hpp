#pragma once

#include "Base.hpp"

namespace TI4Echelon {

enum class Color : int8_t {
  Maroon2,
  Blue,
  ForestGreen,
  Yellow,
  DarkOrange,
  Indigo,
  Fuchsia,
  Aqua,
  Lime,
  Cornflower,
  HotPink,
  DarkSlateGray,
  LightGray
};

/*
maroon2 #7f0000
blue #0000ff
forestgreen #228b22
yellow #ffff00
darkorange #ff8c00
indigo #4b0082
fuchsia #ff00ff
aqua #00ffff
lime #00ff00
cornflower #6495ed
hotpink #ff69b4
darkslategray #2f4f4f
*/

namespace {

const std::unordered_map<Color, std::string> color_codes{
  {Color::Maroon2, "7f0000"},
  {Color::Blue, "0000ff"},
  {Color::ForestGreen, "228b22"},
  {Color::Yellow, "ffff00"},
  {Color::DarkOrange, "ff8c00"},
  {Color::Indigo, "4b0082"},
  {Color::Fuchsia, "ff00ff"},
  {Color::Aqua, "00ffff"},
  {Color::Lime, "00ff00"},
  {Color::Cornflower, "6495ed"},
  {Color::HotPink, "ff69b4"},
  {Color::DarkSlateGray, "2f4f4f"},
  {Color::LightGray, "d3d3d3"}
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

/// \brief Ordered sequence of colors for plot series.
const std::vector<Color> PlotDataColors{
  Color::Maroon2,
  Color::Blue,
  Color::ForestGreen,
  Color::Yellow,
  Color::DarkOrange,
  Color::Indigo,
  Color::Fuchsia,
  Color::Aqua,
  Color::Lime,
  Color::Cornflower,
  Color::HotPink,
  Color::DarkSlateGray
};

Color plot_data_color(const std::size_t counter) noexcept {
  const std::size_t color_index{counter % PlotDataColors.size()};
  return PlotDataColors[color_index];
}

} // namespace TI4Echelon
