#pragma once

#include "EloRating.hpp"
#include "Percentage.hpp"

namespace TI4Echelon {

/// \brief Snapshot of an entity's statistics at a point in time. An entity is either a player or a faction.
class Snapshot {

public:

  /// \brief Default constructor. Does not initialize anything.
  Snapshot() noexcept {}

  Snapshot(
    const PlayerName& player_name,
    const Game& game,
    const std::unordered_map<PlayerName, EloRating>& elo_ratings,
    const std::optional<Snapshot>& previous
  ) noexcept :
    global_game_index_(game.index()),
    date_(game.date())
  {
    initialize_local_game_index(previous);
    initialize_average_victory_points_per_game(player_name, game, previous);
    initialize_place_counts(player_name, game, previous);
    initialize_place_percentages();
    initialize_current_elo_rating(player_name, game, elo_ratings);
    initialize_average_elo_rating(previous);
  }

  Snapshot(
    const FactionName faction_name,
    const Game& game,
    const std::unordered_map<FactionName, EloRating>& elo_ratings,
    const std::optional<Snapshot>& previous
  ) noexcept :
    global_game_index_(game.index()),
    date_(game.date())
  {
    initialize_local_game_index(previous);
    initialize_average_victory_points_per_game(faction_name, game, previous);
    initialize_place_counts(faction_name, game, previous);
    initialize_place_percentages();
    initialize_current_elo_rating(faction_name, game, elo_ratings);
    initialize_average_elo_rating(previous);
  }

  /// \brief Global number of games played, including this one, at this time.
  constexpr std::size_t global_game_number() const noexcept {
    return global_game_index_ + 1;
  }

  /// \brief Number of games played by this entity, including this one, at this time.
  constexpr std::size_t local_game_number() const noexcept {
    return local_game_index_ + 1;
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
    return std::to_string(local_game_number()) + " games, " + current_elo_rating_.print() + " current rating, " + average_elo_rating_.print() + " average rating, " + real_number_to_string(average_victory_points_per_game_, 2) + " average victory points, " + place_percentage({1}).print() + " (" + std::to_string(place_count({1})) + ") 1st place, " + place_percentage({2}).print() + " (" + std::to_string(place_count({2})) + ") 2nd place, " + place_percentage({3}).print() + " (" + std::to_string(place_count({3})) + ") 3rd place";
  }

  /// \brief Sort from most recent to oldest.
  struct sort {
    bool operator()(const Snapshot& snapshot_1, const Snapshot& snapshot_2) const noexcept {
      return snapshot_1.local_game_index_ > snapshot_2.local_game_index_;
    }
  };

private:

  std::size_t global_game_index_{0};

  std::size_t local_game_index_{0};

  Date date_;

  /// \brief This is relative to a 10-point game. Victory point counts are adjusted to a 10-point game.
  double average_victory_points_per_game_{0.0};

  std::map<Place, std::size_t, Place::sort> place_counts_;

  std::map<Place, Percentage, Place::sort> place_percentages_;

  EloRating current_elo_rating_;

  EloRating average_elo_rating_;

  void initialize_local_game_index(const std::optional<Snapshot>& previous) noexcept {
    if (previous.has_value()) {
      local_game_index_ = previous.value().local_game_index_ + 1;
    }
  }

  void initialize_average_victory_points_per_game(const PlayerName& player_name, const Game& game, const std::optional<Snapshot>& previous) noexcept {
    const std::optional<double> adjusted_victory_points{game.adjusted_victory_points(player_name)};
    if (adjusted_victory_points.has_value()) {
      if (previous.has_value()) {
        average_victory_points_per_game_ = (previous.value().average_victory_points_per_game_ * previous.value().local_game_number() + adjusted_victory_points.value()) / local_game_number();
      } else {
        average_victory_points_per_game_ = adjusted_victory_points.value();
      }
    } else {
      error("Player '" + player_name.value() + "' is not a participant in the game '" + game.print() + "'.");
    }
  }

  void initialize_average_victory_points_per_game(const FactionName faction_name, const Game& game, const std::optional<Snapshot>& previous) noexcept {
    const std::multiset<double, std::greater<double>> adjusted_victory_points{game.adjusted_victory_points(faction_name)};
    if (!adjusted_victory_points.empty()) {
      double average_adjusted_victory_points{0.0};
      for (const double value : adjusted_victory_points) {
        average_adjusted_victory_points += value;
      }
      average_adjusted_victory_points /= adjusted_victory_points.size();
      if (previous.has_value()) {
        average_victory_points_per_game_ = (previous.value().average_victory_points_per_game_ * previous.value().local_game_number() + average_adjusted_victory_points) / local_game_number();
      } else {
        average_victory_points_per_game_ = average_adjusted_victory_points;
      }
    } else {
      error("Faction '" + label(faction_name) + "' is not a participant in the game '" + game.print() + "'.");
    }
  }

  void initialize_place_counts(const PlayerName& player_name, const Game& game, const std::optional<Snapshot>& previous) noexcept {
    if (previous.has_value()) {
      place_counts_ = previous.value().place_counts_;
    }
    const std::optional<Place> place{game.place(player_name)};
    if (place.has_value()) {
      const std::map<Place, std::size_t, Place::sort>::iterator place_count{place_counts_.find(place.value())};
      if (place_count != place_counts_.end()) {
        ++(place_count->second);
      } else {
        place_counts_.emplace(place.value(), 1);
      }
    } else {
      error("Player '" + player_name.value() + "' is not a participant in the game '" + game.print() + "'.");
    }
  }

  void initialize_place_counts(const FactionName faction_name, const Game& game, const std::optional<Snapshot>& previous) noexcept {
    if (previous.has_value()) {
      place_counts_ = previous.value().place_counts_;
    }
    const std::set<Place, Place::sort> places{game.places(faction_name)};
    if (!places.empty()) {
      for (const Place& place : places) {
        const std::map<Place, std::size_t, Place::sort>::iterator place_count{place_counts_.find(place)};
        if (place_count != place_counts_.end()) {
          ++(place_count->second);
        } else {
          place_counts_.emplace(place, 1);
        }
      }
    } else {
      error("Faction '" + label(faction_name) + "' is not a participant in the game '" + game.print() + "'.");
    }
  }

  void initialize_place_percentages() noexcept {
    for (const std::pair<Place, int64_t>& place_count : place_counts_) {
      place_percentages_.insert({place_count.first, {static_cast<double>(place_count.second) / local_game_number()}});
    }
  }

  void initialize_current_elo_rating(
    const PlayerName& player_name,
    const Game& game,
    const std::unordered_map<PlayerName, EloRating>& elo_ratings
  ) noexcept {
    current_elo_rating_ = {player_name, game, elo_ratings};
  }

  void initialize_current_elo_rating(
    const FactionName faction_name,
    const Game& game,
    const std::unordered_map<FactionName, EloRating>& elo_ratings
  ) noexcept {
    current_elo_rating_ = {faction_name, game, elo_ratings};
  }

  void initialize_average_elo_rating(const std::optional<Snapshot>& previous) noexcept {
    if (previous.has_value()) {
      average_elo_rating_ = (previous.value().average_elo_rating_ * previous.value().local_game_number() + current_elo_rating_) / (local_game_number());
    } else {
      average_elo_rating_ = current_elo_rating_;
    }
  }

}; // class Snapshot

} // namespace TI4Echelon
