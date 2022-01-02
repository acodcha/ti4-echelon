#pragma once

#include "Game.hpp"

namespace TI4Echelon {

/// \brief Elo rating of a player or a faction at a given point in time.
/// \details A difference of 400 Elo rating points between two players implies that the higher-rated player is 10 times more likely to win.
class EloRating {

public:

  /// \brief Default constructor. Initializes the Elo rating to 1000.
  constexpr EloRating() noexcept {}

  /// \brief Constructor to a given value. For example, EloRating{1500} sets the value to 1500.
  constexpr EloRating(const double value) noexcept : value_(value) {}

  /// \brief Constructs an updated Elo rating for a player given a game and a set of previous Elo ratings.
  EloRating(
    const PlayerName& player_name,
    const Game& game,
    const std::unordered_map<PlayerName, EloRating>& previous_elo_ratings
  ) {
    // Player current place.
    const std::optional<Place> place{game.place(player_name)};
    if (!place.has_value()) {
      error("Player " + player_name.value() + " is not a participant in the game: " + game.print());
    }
    // Number of enemies.
    const std::size_t number_of_opponents{game.participants().size() - game.number_of_players_on_team(player_name).value()};
    // Maximum update factor.
    const double maximum_update_factor_{maximum_update_factor(number_of_opponents)};
    // Player previous Elo rating.
    EloRating elo_rating{previous_elo_rating(player_name, previous_elo_ratings)};
    // Update the Elo rating using the actual and expected outcomes.
    for (const PlayerName& other_player_name : game.player_names() ) {
      if (player_name != other_player_name) {
        if (game.mode() == GameMode::Teams && place.value() == game.place(other_player_name).value()) {
          // In this case, this is an ally. Players do not compete against their allies.
          continue;
        }
        const EloRating opponent_elo_rating{previous_elo_rating(other_player_name, previous_elo_ratings)};
        const double actual_outcome{place.value().outcome(game.place(other_player_name).value())};
        const double expected_outcome{elo_rating.expected_outcome(opponent_elo_rating)};
        elo_rating += maximum_update_factor_ * (actual_outcome - expected_outcome);
      }
    }
    value_ = elo_rating.value();
  }

  constexpr double value() const noexcept {
    return value_;
  }

  /// \brief Print the Elo rating as an integer.
  std::string print() const noexcept {
    return std::to_string(static_cast<int64_t>(std::round(value_)));
  }

  constexpr bool operator==(const EloRating& other) const noexcept {
    return value_ == other.value_;
  }

  constexpr bool operator!=(const EloRating& other) const noexcept {
    return value_ != other.value_;
  }

  constexpr bool operator<(const EloRating& other) const noexcept {
    return value_ < other.value_;
  }

  constexpr bool operator<=(const EloRating& other) const noexcept {
    return value_ <= other.value_;
  }

  constexpr bool operator>(const EloRating& other) const noexcept {
    return value_ > other.value_;
  }

  constexpr bool operator>=(const EloRating& other) const noexcept {
    return value_ >= other.value_;
  }

  constexpr EloRating operator+(const EloRating& other) const noexcept {
    return {value_ + other.value_};
  }

  constexpr EloRating operator+(const double number) const noexcept {
    return {value_ + number};
  }

  constexpr void operator+=(const EloRating& other) noexcept {
    value_ += other.value_;
  }

  constexpr void operator+=(const double number) noexcept {
    value_ += number;
  }

  constexpr EloRating operator-(const EloRating& other) const noexcept {
    return {value_ - other.value_};
  }

  constexpr EloRating operator-(const double number) const noexcept {
    return {value_ - number};
  }

  constexpr void operator-=(const EloRating& other) noexcept {
    value_ -= other.value_;
  }

  constexpr void operator-=(const double number) noexcept {
    value_ -= number;
  }

  constexpr EloRating operator*(const double number) const noexcept {
    return {value_ * number};
  }

  constexpr void operator*=(const double number) noexcept {
    value_ *= number;
  }

  constexpr EloRating operator/(const double number) const noexcept {
    return {value_ / number};
  }

  constexpr void operator/=(const double number) noexcept {
    value_ /= number;
  }

  /// \brief Sort descending, i.e. from the highest Elo rating downwards.
  struct sort {
    bool operator()(const EloRating& elo_rating_1, const EloRating& elo_rating_2) const noexcept {
      return elo_rating_1 > elo_rating_2;
    }
  };

private:

  /// \brief Elo ratings start with a value of 1000.
  double value_{1000.0};

  /// \brief The expected outcome depends on the difference in Elo rating between two opponents.
  constexpr double expected_outcome(const EloRating& opponent_elo_rating) const noexcept {
    return 1.0 / (1.0 + std::pow(10.0, (opponent_elo_rating.value() - value_) / 400.0));
  }

  static constexpr double maximum_update_factor(const std::size_t number_of_opponents) noexcept {
    if (number_of_opponents <= 1) {
      return 64.0;
    } else {
      // In a free-for-all game with N players, each player faces off against N-1 other players, and there are 0.5*N*(N-1) two-player pairs.
      return 64.0 / number_of_opponents;
    }
  }

  EloRating previous_elo_rating(const PlayerName& player_name, const std::unordered_map<PlayerName, EloRating>& previous_elo_ratings) const {
    const std::unordered_map<PlayerName, EloRating>::const_iterator found{previous_elo_ratings.find(player_name)};
    if (found != previous_elo_ratings.cend()) {
      return found->second;
    } else {
      error("Player " + player_name.value() + " is missing from the previous Elo ratings.");
    }
    return {};
  }

}; // class EloRating

} // namespace TI4Echelon

namespace std {

  template <> struct hash<TI4Echelon::EloRating> {

    size_t operator()(const TI4Echelon::EloRating& elo_rating) const {
      return hash<double>()(elo_rating.value());
    }

  };

} // namespace std
