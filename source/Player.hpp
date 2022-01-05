#pragma once

#include "Color.hpp"
#include "Snapshot.hpp"

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

  std::optional<Snapshot> latest_snapshot() const {
    if (!snapshots_.empty()) {
      return {snapshots_.back()};
    } else {
      const std::optional<Snapshot> no_data;
      return no_data;
    }
  }

  void update(const Game& game, const std::unordered_map<PlayerName, EloRating>& elo_ratings) noexcept {
    if (game.exists(name_)) {
      snapshots_.emplace_back(name_, game, elo_ratings, latest_snapshot());
      update_lowest_and_highest_elo_ratings();
    }
  }

  /// \brief Prints this player's latest statistics.
  std::string print() const noexcept {
    std::string text{name_.value() + ": "};
    const std::optional<Snapshot> latest_snapshot_{latest_snapshot()};
    if (latest_snapshot_.has_value()) {
      text += latest_snapshot_.value().print();
    } else {
      text += Snapshot{}.print();
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

  struct const_iterator : public std::vector<Snapshot>::const_iterator {
    const_iterator(const std::vector<Snapshot>::const_iterator i) noexcept : std::vector<Snapshot>::const_iterator(i) {}
  };

  struct const_reverse_iterator : public std::vector<Snapshot>::const_reverse_iterator {
    const_reverse_iterator(const std::vector<Snapshot>::const_reverse_iterator i) noexcept : std::vector<Snapshot>::const_reverse_iterator(i) {}
  };

  std::size_t number_of_snapshots() const noexcept {
    return snapshots_.size();
  }

  const_iterator begin() const noexcept {
    return const_iterator(snapshots_.begin());
  }

  const_iterator cbegin() const noexcept {
    return const_iterator(snapshots_.cbegin());
  }

  const_reverse_iterator rbegin() const noexcept {
    return const_reverse_iterator(snapshots_.rbegin());
  }

  const_reverse_iterator crbegin() const noexcept {
    return const_reverse_iterator(snapshots_.crbegin());
  }

  const_iterator end() const noexcept {
    return const_iterator(snapshots_.end());
  }

  const_iterator cend() const noexcept {
    return const_iterator(snapshots_.cend());
  }

  const_reverse_iterator rend() const noexcept {
    return const_reverse_iterator(snapshots_.rend());
  }

  const_reverse_iterator crend() const noexcept {
    return const_reverse_iterator(snapshots_.crend());
  }

private:

  PlayerName name_;

  std::optional<Color> color_;

  EloRating lowest_elo_rating_;

  EloRating highest_elo_rating_;

  std::vector<Snapshot> snapshots_;

  void update_lowest_and_highest_elo_ratings() noexcept {
    const std::optional<Snapshot> latest_snapshot_{latest_snapshot()};
    if (latest_snapshot_.value().current_elo_rating() < lowest_elo_rating_) {
      lowest_elo_rating_ = latest_snapshot_.value().current_elo_rating();
    }
    if (latest_snapshot_.value().current_elo_rating() > highest_elo_rating_) {
      highest_elo_rating_ = latest_snapshot_.value().current_elo_rating();
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
