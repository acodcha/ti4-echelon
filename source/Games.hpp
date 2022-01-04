#pragma once

#include "GamesDurationVersusNumberOfPlayers.hpp"
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
          data_.emplace_back(game_lines);
          duration_versus_number_of_players_.insert(data_.back());
        }
        game_lines.clear();
      } else {
        game_lines.push_back(line);
      }
    }
    if (!game_lines.empty()) {
      data_.emplace_back(game_lines);
      duration_versus_number_of_players_.insert(data_.back());
    }
    std::sort(data_.begin(), data_.end(), Game::sort());
    for (std::size_t index = 0; index < data_.size(); ++index) {
      data_[index].set_index(data_.size() - 1 - index);
    }
    duration_versus_number_of_players_.initialize_linear_regression();
    message("Read " + std::to_string(data_.size()) + " games from the games file:");
    for (const Game& game : data_) {
      message("- " + game.print() + ".");
    }
  }

  const GamesDurationVersusNumberOfPlayers& duration_versus_number_of_players() const noexcept {
    return duration_versus_number_of_players_;
  }

  struct const_iterator : public std::vector<Game>::const_iterator {
    const_iterator(const std::vector<Game>::const_iterator i) noexcept : std::vector<Game>::const_iterator(i) {}
  };

  struct const_reverse_iterator : public std::vector<Game>::const_reverse_iterator {
    const_reverse_iterator(const std::vector<Game>::const_reverse_iterator i) noexcept : std::vector<Game>::const_reverse_iterator(i) {}
  };

  bool empty() const noexcept {
    return data_.empty();
  }

  std::size_t size() const noexcept {
    return data_.size();
  }

  const_iterator begin() const noexcept {
    return const_iterator(data_.begin());
  }

  const_iterator cbegin() const noexcept {
    return const_iterator(data_.cbegin());
  }

  const_reverse_iterator rbegin() const noexcept {
    return const_reverse_iterator(data_.rbegin());
  }

  const_reverse_iterator crbegin() const noexcept {
    return const_reverse_iterator(data_.crbegin());
  }

  const_iterator end() const noexcept {
    return const_iterator(data_.end());
  }

  const_iterator cend() const noexcept {
    return const_iterator(data_.cend());
  }

  const_reverse_iterator rend() const noexcept {
    return const_reverse_iterator(data_.rend());
  }

  const_reverse_iterator crend() const noexcept {
    return const_reverse_iterator(data_.crend());
  }

private:

  GamesDurationVersusNumberOfPlayers duration_versus_number_of_players_;

  /// \brief Sorted in reverse-chronological order, i.e. from most recent to oldest.
  std::vector<Game> data_;

}; // class Games

} // namespace TI4Echelon
