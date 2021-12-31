#pragma once

#include "Game.hpp"
#include "TextFileReader.hpp"

namespace TI4Echelon {

/// \brief List of games read from the games file.
class Games {

public:

  Games(const std::filesystem::path& games_file_path) {
    message("Reading the games file...");
    const TextFileReader games_file_reader{games_file_path};
    std::vector<std::string> game_lines;
    for (const std::string& line : games_file_reader) {
      if (line.empty()) {
        if (!game_lines.empty()) {
          data_.emplace(game_lines);
        }
        game_lines.clear();
      } else {
        game_lines.push_back(line);
      }
    }
    if (!game_lines.empty()) {
      data_.emplace(game_lines);
    }
    message("Read " + std::to_string(data_.size()) + " games from the games file:");
    for (const Game& game : data_) {
      message("- " + game.print());
    }
  }

  struct const_iterator : public std::multiset<Game, Game::sort_by_most_recent_date>::const_iterator {
    const_iterator(const std::multiset<Game, Game::sort_by_most_recent_date>::const_iterator i) noexcept : std::multiset<Game, Game::sort_by_most_recent_date>::const_iterator(i) {}
  };

  std::size_t size() const noexcept {
    return data_.size();
  }

  const_iterator cbegin() const noexcept {
   return const_iterator(data_.cbegin());
  }

  const_iterator begin() const noexcept {
   return cbegin();
  }

  const_iterator cend() const noexcept {
   return const_iterator(data_.cend());
  }

  const_iterator end() const noexcept {
   return cend();
  }

private:

  /// \brief A multiset is used in case two or more games are played on the same date.
  std::multiset<Game, Game::sort_by_most_recent_date> data_;

}; // class Games

} // namespace TI4Echelon
