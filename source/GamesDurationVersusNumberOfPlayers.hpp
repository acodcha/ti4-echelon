#pragma once

#include "Duration.hpp"
#include "Game.hpp"
#include "LinearRegression.hpp"

namespace TI4Echelon {

/// \brief Plot and linear regression of game duration versus number of players.
class GamesDurationVersusNumberOfPlayers {

public:

  GamesDurationVersusNumberOfPlayers() noexcept {}

  double minimum_duration_in_hours() const noexcept {
    return minimum_duration_in_hours_;
  }

  double maximum_duration_in_hours() const noexcept {
    return maximum_duration_in_hours_;
  }

  const LinearRegression& linear_regression() const noexcept {
    return linear_regression_;
  }

  std::string print() const noexcept {
    return "hours = " + real_number_to_string(linear_regression_.intercept(), 2) + " + " + real_number_to_string(linear_regression_.slope(), 2) + " * players";
  }

  void insert(const Game& game) noexcept {
    if (game.duration().has_value()) {
      number_of_players_and_duration_in_hours_.emplace_back(game.participants().size(), game.duration().value().hours());
      if (game.duration().value().hours() < minimum_duration_in_hours_) {
        minimum_duration_in_hours_ = game.duration().value().hours();
      }
      if (game.duration().value().hours() > maximum_duration_in_hours_) {
        maximum_duration_in_hours_ = game.duration().value().hours();
      }
    }
  }

  void initialize_linear_regression() noexcept {
    linear_regression_ = {number_of_players_and_duration_in_hours_};
  }

  struct const_iterator : public std::vector<std::pair<double, double>>::const_iterator {
    const_iterator(const std::vector<std::pair<double, double>>::const_iterator i) noexcept : std::vector<std::pair<double, double>>::const_iterator(i) {}
  };

  struct const_reverse_iterator : public std::vector<std::pair<double, double>>::const_reverse_iterator {
    const_reverse_iterator(const std::vector<std::pair<double, double>>::const_reverse_iterator i) noexcept : std::vector<std::pair<double, double>>::const_reverse_iterator(i) {}
  };

  bool empty() const noexcept {
    return number_of_players_and_duration_in_hours_.empty();
  }

  std::size_t size() const noexcept {
    return number_of_players_and_duration_in_hours_.size();
  }

  const_iterator begin() const noexcept {
    return const_iterator(number_of_players_and_duration_in_hours_.begin());
  }

  const_iterator cbegin() const noexcept {
    return const_iterator(number_of_players_and_duration_in_hours_.cbegin());
  }

  const_reverse_iterator rbegin() const noexcept {
    return const_reverse_iterator(number_of_players_and_duration_in_hours_.rbegin());
  }

  const_reverse_iterator crbegin() const noexcept {
    return const_reverse_iterator(number_of_players_and_duration_in_hours_.crbegin());
  }

  const_iterator end() const noexcept {
    return const_iterator(number_of_players_and_duration_in_hours_.end());
  }

  const_iterator cend() const noexcept {
    return const_iterator(number_of_players_and_duration_in_hours_.cend());
  }

  const_reverse_iterator rend() const noexcept {
    return const_reverse_iterator(number_of_players_and_duration_in_hours_.rend());
  }

  const_reverse_iterator crend() const noexcept {
    return const_reverse_iterator(number_of_players_and_duration_in_hours_.crend());
  }

private:

  double minimum_duration_in_hours_{10.0};

  double maximum_duration_in_hours_{0.0};

  std::vector<std::pair<double, double>> number_of_players_and_duration_in_hours_;

  LinearRegression linear_regression_;

}; // class GamesDurationVersusNumberOfPlayers

} // namespace TI4Echelon
