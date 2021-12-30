#pragma once

#include "Color.hpp"
#include "CurrentDateAndTime.hpp"
#include "Message.hpp"
#include "String.hpp"

namespace TI4Echelon {

/// \brief Namespace containing information about the program and its compilation.
namespace Program {

const std::string Title{"TI4 Echelon"};

const std::string CompilationDateAndTime{std::string{__DATE__} + ", " + std::string{__TIME__}};

const std::string Description{"Leaderboard generator for the Twilight Imperium 4th Edition board game by Fantasy Flight Games."};

} // namespace Program

constexpr const int16_t PlotWidthPixels{1000};

constexpr const int16_t PlotHeightPixels{750};

void create(const std::filesystem::path& directory) {
  std::filesystem::create_directory(directory);
  if (!std::filesystem::exists(directory) || !std::filesystem::is_directory(directory)) {
    error("Could not create the directory: " + directory.string());
  }
}

template <typename Type> const std::map<Type, std::string> labels;

template <typename Type> std::string label(const Type type) noexcept {
  const typename std::map<Type, std::string>::const_iterator found{labels<Type>.find(type)};
  if (found != labels<Type>.cend()) {
    return found->second;
  } else {
    return {};
  }
}

} // namespace TI4Echelon
