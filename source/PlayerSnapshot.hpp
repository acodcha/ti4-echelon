#pragma once

#include "EloRating.hpp"
#include "Percentage.hpp"

namespace TI4Echelon {

/// \brief Snapshot of a player's statistics at a point in time.
class PlayerSnapshot {

public:

  /// \brief Default constructor. Does not initialize anything.
  PlayerSnapshot() noexcept {}

  PlayerSnapshot(
    const PlayerName& name,
    const Game& game,
    const std::unordered_map<PlayerName, EloRating>& elo_ratings,
    const std::optional<PlayerSnapshot>& previous = std::optional<PlayerSnapshot>{}
  ) noexcept :
    global_game_index_(game.index()),
    date_(game.date())
  {
    initialize_player_game_index(previous);
    initialize_average_victory_points_per_game(name, game, previous);
    initialize_place_counts(name, game, previous);
    initialize_place_percentages();
    initialize_current_elo_rating(name, game, elo_ratings);
    initialize_average_elo_rating(previous);
  }

  /// \brief Global number of games played, including this one, at this time.
  constexpr std::size_t global_game_number() const noexcept {
    return global_game_index_ + 1;
  }

  /// \brief Number of games played by this player, including this one, at this time.
  constexpr std::size_t player_game_number() const noexcept {
    return player_game_index_ + 1;
  }

  constexpr const Date& date() const noexcept {
    return date_;
  }

  constexpr double average_victory_points_per_game() const noexcept {
    return average_victory_points_per_game_;
  }

  /// \brief Number of Nth place finishes.
  std::size_t place_count(const Place place) const noexcept {
    const std::map<Place, std::size_t, Place::sort>::const_iterator found{place_counts_.find(place)};
    if (found != place_counts_.cend()) {
      return found->second;
    } else {
      return 0;
    }
  }

  /// \brief Percentage ratio of Nth place finishes.
  Percentage place_percentage(const Place place) const noexcept {
    const std::map<Place, Percentage, Place::sort>::const_iterator found{place_percentages_.find(place)};
    if (found != place_percentages_.cend()) {
      return found->second;
    } else {
      return {0.0};
    }
  }

  std::string print_place_percentage_and_count(const Place place) const noexcept {
    return place_percentage(place).print() + " (" + std::to_string(place_count(place)) + ")";
  }

  constexpr const EloRating& current_elo_rating() const noexcept {
    return current_elo_rating_;
  }

  constexpr const EloRating& average_elo_rating() const noexcept {
    return average_elo_rating_;
  }

  std::string print() const noexcept {
    return std::to_string(player_game_number()) + " games, " + current_elo_rating_.print() + " current rating, " + average_elo_rating_.print() + " average rating, " + real_number_to_string(average_victory_points_per_game_, 2) + " average victory points, " + place_percentage({1}).print() + " (" + std::to_string(place_count({1})) + ") 1st place, " + place_percentage({2}).print() + " (" + std::to_string(place_count({2})) + ") 2nd place, " + place_percentage({3}).print() + " (" + std::to_string(place_count({3})) + ") 3rd place";
  }

  /// \brief Sort from most recent to oldest.
  struct sort {
    bool operator()(const PlayerSnapshot& player_snapshot_1, const PlayerSnapshot& player_snapshot_2) const noexcept {
      return player_snapshot_1.player_game_index_ > player_snapshot_2.player_game_index_;
    }
  };

private:

  std::size_t global_game_index_{0};

  std::size_t player_game_index_{0};

  Date date_;

  /// \brief This is relative to a 10-point game. Victory point counts are adjusted to a 10-point game.
  double average_victory_points_per_game_{0.0};

  std::map<Place, std::size_t, Place::sort> place_counts_;

  std::map<Place, Percentage, Place::sort> place_percentages_;

  EloRating current_elo_rating_;

  EloRating average_elo_rating_;

  void initialize_player_game_index(const std::optional<PlayerSnapshot>& previous) noexcept {
    if (previous.has_value()) {
      player_game_index_ = previous.value().player_game_index_ + 1;
    }
  }

  void initialize_average_victory_points_per_game(const PlayerName& name, const Game& game, const std::optional<PlayerSnapshot>& previous) noexcept {
    const std::optional<double> found{game.adjusted_victory_points(name)};
    if (found.has_value()) {
      if (previous.has_value()) {
        average_victory_points_per_game_ = (previous.value().average_victory_points_per_game_ * previous.value().player_game_number() + found.value()) / player_game_number();
      } else {
        average_victory_points_per_game_ = found.value();
      }
    } else {
      error("Player '" + name.value() + "' is not a participant in the game '" + game.print() + "'.");
    }
  }

  void initialize_place_counts(const PlayerName& name, const Game& game, const std::optional<PlayerSnapshot>& previous) noexcept {
    if (previous.has_value()) {
      place_counts_ = previous.value().place_counts_;
    }
    const std::optional<Place> found{game.place(name)};
    if (found.has_value()) {
      const std::map<Place, std::size_t, Place::sort>::iterator place_count{place_counts_.find(found.value())};
      if (place_count != place_counts_.end()) {
        ++(place_count->second);
      } else {
        place_counts_.emplace(found.value(), 1);
      }
    } else {
      error("Player '" + name.value() + "' is not a participant in the game '" + game.print() + "'.");
    }
  }

  void initialize_place_percentages() noexcept {
    for (const std::pair<Place, int64_t>& place_count : place_counts_) {
      place_percentages_.insert({place_count.first, {static_cast<double>(place_count.second) / player_game_number()}});
    }
  }

  void initialize_current_elo_rating(
    const PlayerName& player_name,
    const Game& game,
    const std::unordered_map<PlayerName, EloRating>& elo_ratings
  ) noexcept {
    current_elo_rating_ = {player_name, game, elo_ratings};
  }

  void initialize_average_elo_rating(const std::optional<PlayerSnapshot>& previous) noexcept {
    if (previous.has_value()) {
      average_elo_rating_ = (previous.value().average_elo_rating_ * previous.value().player_game_number() + current_elo_rating_) / (player_game_number());
    } else {
      average_elo_rating_ = current_elo_rating_;
    }
  }

}; // class PlayerSnapshot

} // namespace TI4Echelon
