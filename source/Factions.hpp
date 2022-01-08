#pragma once

#include "Games.hpp"
#include "Faction.hpp"

namespace TI4Echelon {

/// \brief A set of factions.
class Factions {

public:

  /// \brief Constructs all faction data given the games.
  Factions(const Games& games) noexcept {
    initialize_data(games);
    initialize_indices();
    update(games);
    message(print());
  }

  const EloRating& lowest_elo_rating() const noexcept {
    return lowest_elo_rating_;
  }

  const EloRating& highest_elo_rating() const noexcept {
    return highest_elo_rating_;
  }

  std::string print() const noexcept {
    std::stringstream stream;
    stream << "Calculated statistics for " << data_.size() << " factions:";
    for (const Faction& faction : data_) {
      stream << std::endl << "- " << faction.print() << ".";
    }
    return stream.str();
  }

  struct const_iterator : public std::vector<Faction>::const_iterator {
    const_iterator(const std::vector<Faction>::const_iterator i) noexcept : std::vector<Faction>::const_iterator(i) {}
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

  const_iterator end() const noexcept {
   return const_iterator(data_.end());
  }

  const_iterator cend() const noexcept {
   return const_iterator(data_.cend());
  }

  bool exists(const FactionName name) const noexcept {
    return indices_.find(name) != indices_.cend();
  }

  const_iterator find(const FactionName name) const noexcept {
    const std::unordered_map<FactionName, std::size_t>::const_iterator found{indices_.find(name)};
    if (found != indices_.cend()) {
      return data_.cbegin() + found->second;
    } else {
      return data_.cend();
    }
  }

private:

  EloRating lowest_elo_rating_;

  EloRating highest_elo_rating_;

  std::vector<Faction> data_;

  std::unordered_map<FactionName, std::size_t> indices_;

  /// \brief Initialize the factions with their names and colors.
  /// \details Only a limited number of factions with the most games played are assigned a color.
  void initialize_data(const Games& games) noexcept {
    for (const FactionName faction_name : FactionNames) {
      data_.emplace_back(faction_name, color(faction_name));
    }
    std::sort(data_.begin(), data_.end(), Faction::sort());
  }

  void initialize_indices() noexcept {
    for (std::size_t index = 0; index < data_.size(); ++index) {
      indices_.emplace(data_[index].name(), index);
    }
  }

  /// \brief Update all the factions with all the games.
  void update(const Games& games) noexcept {
    // Iterate through the games in chronological order.
    // The games are listed in reverse-chronological order, so use a reverse iterator.
    for (Games::const_reverse_iterator game = games.crbegin(); game != games.crend(); ++game) {
      const std::unordered_map<FactionName, EloRating> current_elo_ratings_{current_elo_ratings()};
      for (Faction& faction : data_) {
        faction.update(*game, current_elo_ratings_);
        if (faction.lowest_elo_rating() < lowest_elo_rating_) {
          lowest_elo_rating_ = faction.lowest_elo_rating();
        }
        if (faction.highest_elo_rating() > highest_elo_rating_) {
          highest_elo_rating_ = faction.highest_elo_rating();
        }
      }
    }
  }

  std::unordered_map<FactionName, EloRating> current_elo_ratings() const noexcept {
    std::unordered_map<FactionName, EloRating> elo_ratings_;
    for (const Faction& faction : data_) {
      const std::optional<Snapshot> latest_snapshot{faction.latest_snapshot()};
      if (latest_snapshot.has_value()) {
        elo_ratings_.emplace(faction.name(), latest_snapshot.value().current_elo_rating());
      } else {
        elo_ratings_.emplace(faction.name(), EloRating{});
      }
    }
    return elo_ratings_;
  }

}; // class Factions

} // namespace TI4Echelon
