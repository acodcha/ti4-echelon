#pragma once

#include "EloRating.hpp"
#include "Percentage.hpp"

namespace TI4Echelon {

/// \brief Cell in a table.
class TableCell {

public:

  TableCell() noexcept {}

  TableCell(const std::size_t number) noexcept : value_(std::to_string(number)) {}

  TableCell(const double number, const int8_t decimals = 2) noexcept : value_(real_number_to_string(number, decimals)) {}

  TableCell(const std::string& text) noexcept : value_(text) {}

  TableCell(const Date& date) noexcept : value_(date.print()) {}

  TableCell(const EloRating& elo_rating) noexcept : value_(elo_rating.print()) {}

  TableCell(const FactionName& faction_name) noexcept : value_(label(faction_name)) {}

  TableCell(const GameMode& game_mode) noexcept : value_(label(game_mode)) {}

  TableCell(const Percentage& percentage) noexcept : value_(percentage.print()) {}

  TableCell(const Place& place) noexcept : value_(place.print()) {}

  TableCell(const PlayerName& player_name) noexcept : value_(player_name.value()) {}

  TableCell(const VictoryPoints& victory_points) noexcept : value_(victory_points.print()) {}

  const std::string& print() const noexcept {
    return value_;
  }

protected:

  std::string value_;

}; // class TableRow

} // namespace TI4Echelon
