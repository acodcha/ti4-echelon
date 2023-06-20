#pragma once

#include "CurrentDateAndTime.hpp"
#include "Enumerations.hpp"
#include "Message.hpp"

namespace TI4Echelon {

/// \brief Namespace containing information about the program and its
/// compilation.
namespace Program {

const std::string Title{"TI4 Echelon"};

const std::string CompilationDateAndTime{
    std::string{__DATE__} + ", " + std::string{__TIME__}};

const std::string Description{
    "Leaderboard generator for the Twilight Imperium 4th Edition board game by "
    "Fantasy Flight Games."};

}  // namespace Program

constexpr const std::size_t PlotMinimumNumberOfPlayers{1};

constexpr const std::size_t PlotMaximumNumberOfPlayers{9};

constexpr const int16_t PlotWidthPixels{640};

constexpr const int16_t PlotHeightPixels{640};

void create(const std::filesystem::path& directory) {
  std::filesystem::create_directory(directory);
  if (!std::filesystem::exists(directory)
      || !std::filesystem::is_directory(directory)) {
    error("Could not create the directory: " + directory.string());
  }
}

}  // namespace TI4Echelon
