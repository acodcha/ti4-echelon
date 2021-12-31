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
    // Maximum update factor.
    const double maximum_update_factor_{maximum_update_factor(game.number_of_players())};
    // Player current place.
    const std::optional<Place> player_place{game.player_names().place(player_name)};
    if (!player_place.has_value()) {
      error("Player " + player_name.value() + " is not a participant in the game: " + game.print());
    }
    // Player previous Elo rating.
    EloRating player_elo_rating;
    const std::unordered_map<PlayerName, EloRating>::const_iterator found{previous_elo_ratings.find(player_name)};
    if (found != previous_elo_ratings.cend()) {
      player_elo_rating = found->second;
    } else {
      error("Player " + player_name.value() + " is missing from the previous Elo ratings map.");
    }
    // Update the Elo rating using the actual and expected outcomes.
    for (const PlayerName& game_player_name : game.player_names() ) {
      if (player_name != game_player_name) {
        const Place game_player_place{game.player_names().place(game_player_name).value()};
        const double actual_outcome{player_place.value().outcome(game_player_place)};
        EloRating game_player_previous_elo_rating;
        const std::unordered_map<PlayerName, EloRating>::const_iterator found{previous_elo_ratings.find(game_player_name)};
        if (found != previous_elo_ratings.cend()) {
          game_player_previous_elo_rating = found->second;
        } else {
          error("Player " + game_player_name.value() + " is missing from the previous Elo ratings map.");
        }
        const double expected_outcome{player_elo_rating.expected_outcome(game_player_previous_elo_rating)};
        player_elo_rating += maximum_update_factor_ * (actual_outcome - expected_outcome);
      }
    }
    value_ = player_elo_rating.value();
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

  struct sort_ascending {
    bool operator()(const EloRating& elo_rating_1, const EloRating& elo_rating_2) const noexcept {
      return elo_rating_1 < elo_rating_2;
    }
  };

  struct sort_descending {
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

  static constexpr double maximum_update_factor(const std::size_t number_of_players) noexcept {
    if (number_of_players <= 2) {
      return 64.0;
    } else {
      // In a game with N players, each player faces off against N-1 other players, and there are 0.5*N*(N-1) two-player pairs.
      return 64.0 / (number_of_players - 1);
    }
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
