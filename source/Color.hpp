#pragma once

#include "Include.hpp"

namespace TI4Echelon {

/// \brief Namespace containing colors for plots.
namespace Color {

const std::string Red{"E6194B"};

const std::string Blue{"0082C8"};

const std::string Green{"3CB44B"};

const std::string Yellow{"FFE119"};

const std::string Orange{"F58231"};

const std::string Purple{"911EB4"};

const std::string Cyan{"46F0F0"};

const std::string Magenta{"F032E6"};

const std::string Teal{"008080"};

const std::string Brown{"AA6E28"};

const std::string Pink{"FABEBE"};

const std::string Olive{"808000"};

} // namespace Color

const std::vector<std::string> ColorSequence{
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

std::string color(const std::size_t counter) noexcept {
  const std::size_t color_index{counter % ColorSequence.size()};
  return ColorSequence[color_index];
}

} // namespace TI4Echelon
