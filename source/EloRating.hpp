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
    const std::optional<Place> place{game.place(player_name)};
    if (!place.has_value()) {
      error("Player " + player_name.value() + " is not a participant in the game: " + game.print());
    }
    EloRating elo_rating{previous_elo_rating(player_name, previous_elo_ratings)};
    // Update the Elo rating using the actual and expected outcomes.
    for (const Participant& participant : game.participants() ) {
      // Do not compete against yourself or your allies. The place handles both of these checks.
      if (place.value() != participant.place()) {
        const EloRating opponent_elo_rating{previous_elo_rating(participant.player_name(), previous_elo_ratings)};
        const double actual_outcome{place.value().outcome(participant.place())};
        const double expected_outcome{elo_rating.expected_outcome(opponent_elo_rating)};
        elo_rating += update_factor_ * (actual_outcome - expected_outcome);
      }
    }
    value_ = elo_rating.value();
  }

  /// \brief Constructs an updated Elo rating for a faction given a game and a set of previous Elo ratings.
  EloRating(
    const FactionName& faction_name,
    const Game& game,
    const std::unordered_map<FactionName, EloRating>& previous_elo_ratings
  ) {
    const std::set<Place, Place::sort> places{game.places(faction_name)};
    if (!places.empty()) {
      EloRating elo_rating{previous_elo_rating(faction_name, previous_elo_ratings)};
      for (const Place& place : places) {
        // Update the Elo rating using the actual and expected outcomes.
        for (const Participant& participant : game.participants() ) {
          // Do not compete against yourself or your allies. The place handles both of these checks.
          if (place != participant.place()) {
            const EloRating opponent_elo_rating{previous_elo_rating(participant.faction_name(), previous_elo_ratings)};
            const double actual_outcome{place.outcome(participant.place())};
            const double expected_outcome{elo_rating.expected_outcome(opponent_elo_rating)};
            elo_rating += update_factor_ * (actual_outcome - expected_outcome);
          }
        }
      }
      value_ = elo_rating.value();
    } else {
      error("Faction " + label(faction_name) + " is not a participant in the game: " + game.print());
    }
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

  /// \brief When an Elo rating is updated, it changes by at most its update factor.
  static constexpr const double update_factor_{64.0};

  /// \brief The expected outcome depends on the difference in Elo rating between two opponents.
  constexpr double expected_outcome(const EloRating& opponent_elo_rating) const noexcept {
    return 1.0 / (1.0 + std::pow(10.0, (opponent_elo_rating.value() - value_) / 400.0));
  }

  static EloRating previous_elo_rating(const PlayerName& player_name, const std::unordered_map<PlayerName, EloRating>& previous_elo_ratings) {
    const std::unordered_map<PlayerName, EloRating>::const_iterator found{previous_elo_ratings.find(player_name)};
    if (found != previous_elo_ratings.cend()) {
      return found->second;
    } else {
      error("Player " + player_name.value() + " is missing from the previous Elo ratings.");
      return {};
    }
  }

  static EloRating previous_elo_rating(const FactionName& faction_name, const std::unordered_map<FactionName, EloRating>& previous_elo_ratings) {
    const std::unordered_map<FactionName, EloRating>::const_iterator found{previous_elo_ratings.find(faction_name)};
    if (found != previous_elo_ratings.cend()) {
      return found->second;
    } else {
      error("Faction " + label(faction_name) + " is missing from the previous Elo ratings.");
      return {};
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
