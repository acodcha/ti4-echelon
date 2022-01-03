#pragma once

#include "Color.hpp"
#include "PlayerSnapshots.hpp"

namespace TI4Echelon {

/// \brief A player along with a history of snapshots.
class Player {

public:

  /// \brief Default constructor.
  Player() noexcept {}

  /// \brief Constructs a player, initially without any snapshots. Snapshots can be added from games later.
  /// \details If a player does not have a color defined, that player does not appear in plots.
  Player(const PlayerName& name, const std::optional<Color>& color = std::optional<Color>{}) noexcept : name_(name), color_(color) {}

  const PlayerName& name() const noexcept {
    return name_;
  }

  const std::optional<Color>& color() const noexcept {
    return color_;
  }

  const EloRating& lowest_elo_rating() const noexcept {
    return lowest_elo_rating_;
  }

  const EloRating& highest_elo_rating() const noexcept {
    return highest_elo_rating_;
  }

  const PlayerSnapshots& snapshots() const noexcept {
    return snapshots_;
  }

  void update(const Game& game, const std::unordered_map<PlayerName, EloRating>& elo_ratings) noexcept {
    if (game.player_names().exists(name_)) {
      snapshots_.emplace_back(name_, game, elo_ratings);
      update_lowest_and_highest_elo_ratings();
    }
  }

  /// \brief Prints this player's latest statistics.
  std::string print() const noexcept {
    std::string text{name_.value() + ": "};
    const std::optional<PlayerSnapshot> latest_snapshot{snapshots_.latest()};
    if (latest_snapshot.has_value()) {
      text += latest_snapshot.value().print();
    } else {
      text += PlayerSnapshot{}.print();
    }
    return text;
  }

  bool operator==(const Player& other) const noexcept {
    return name_ == other.name_;
  }

  bool operator!=(const Player& other) const noexcept {
    return name_ != other.name_;
  }

  bool operator<(const Player& other) const noexcept {
    return name_ < other.name_;
  }

  bool operator<=(const Player& other) const noexcept {
    return name_ <= other.name_;
  }

  bool operator>(const Player& other) const noexcept {
    return name_ > other.name_;
  }

  bool operator>=(const Player& other) const noexcept {
    return name_ >= other.name_;
  }

  struct sort {
    bool operator()(const Player& player_1, const Player& player_2) const noexcept {
      return player_1 < player_2;
    }
  };

private:

  PlayerName name_;

  std::optional<Color> color_;

  EloRating lowest_elo_rating_;

  EloRating highest_elo_rating_;

  PlayerSnapshots snapshots_;

  void update_lowest_and_highest_elo_ratings() noexcept {
    const std::optional<PlayerSnapshot> latest_snapshot{snapshots_.latest()};
    if (latest_snapshot.value().current_elo_rating() < lowest_elo_rating_) {
      lowest_elo_rating_ = latest_snapshot.value().current_elo_rating();
    }
    if (latest_snapshot.value().current_elo_rating() > highest_elo_rating_) {
      highest_elo_rating_ = latest_snapshot.value().current_elo_rating();
    }
  }

}; // class Player

} // namespace TI4Echelon

namespace std {

  template <> struct hash<TI4Echelon::Player> {

    size_t operator()(const TI4Echelon::Player& player) const {
      return hash<TI4Echelon::PlayerName>()(player.name());
    }

  };

} // namespace std
