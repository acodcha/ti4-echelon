#pragma once

#include "Games.hpp"
#include "Player.hpp"

namespace TI4Echelon {

/// \brief A set of players.
class Players {

public:

  /// \brief Constructs all player data given the games.
  Players(const Games& games) noexcept {
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
    stream << "The statistics of the " << data_.size() << " players are:";
    for (const Player& player : data_) {
      stream << std::endl << "- " << player.print() << ".";
    }
    return stream.str();
  }

  struct const_iterator : public std::vector<Player>::const_iterator {
    const_iterator(const std::vector<Player>::const_iterator i) noexcept : std::vector<Player>::const_iterator(i) {}
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

  bool exists(const PlayerName& name) const noexcept {
    return indices_.find(name) != indices_.cend();
  }

  const_iterator find(const PlayerName& name) const noexcept {
    const std::unordered_map<PlayerName, std::size_t>::const_iterator found{indices_.find(name)};
    if (found != indices_.cend()) {
      return data_.cbegin() + found->second;
    } else {
      return data_.cend();
    }
  }

private:

  EloRating lowest_elo_rating_;

  EloRating highest_elo_rating_;

  std::vector<Player> data_;

  std::unordered_map<PlayerName, std::size_t> indices_;

  /// \brief Initialize the players with their names and colors.
  /// \details Only a limited number of players with the most games played are assigned a color.
  void initialize_data(const Games& games) noexcept {
    const std::multimap<std::size_t, PlayerName, std::greater<std::size_t>> player_names_by_number_of_games_(player_names_by_number_of_games(games));
    std::set<PlayerName, PlayerName::sort> player_names_with_colors;
    std::set<PlayerName, PlayerName::sort> player_names_without_colors;
    for (const std::pair<std::size_t, PlayerName>& number_of_games_and_player_name : player_names_by_number_of_games_) {
      if (player_names_with_colors.size() < Colors.size()) {
        player_names_with_colors.insert(number_of_games_and_player_name.second);
      } else {
        player_names_without_colors.insert(number_of_games_and_player_name.second);
      }
    }
    for (const PlayerName& player_name : player_names_with_colors) {
      const std::size_t color_index{data_.size()};
      data_.emplace_back(player_name, color(color_index));
    }
    for (const PlayerName& player_name : player_names_without_colors) {
      data_.emplace_back(player_name);
    }
    std::sort(data_.begin(), data_.end(), Player::sort());
  }

  std::multimap<std::size_t, PlayerName, std::greater<std::size_t>> player_names_by_number_of_games(const Games& games) const noexcept {
    const std::unordered_map<PlayerName, std::size_t> number_of_games_(number_of_games(games));
    std::multimap<std::size_t, PlayerName, std::greater<std::size_t>> player_names_by_number_of_games_;
    for (const std::pair<PlayerName, std::size_t>& player_name_and_number_of_games : number_of_games_) {
      player_names_by_number_of_games_.emplace(player_name_and_number_of_games.second, player_name_and_number_of_games.first);
    }
    return player_names_by_number_of_games_;
  }

  std::unordered_map<PlayerName, std::size_t> number_of_games(const Games& games) const noexcept {
    std::unordered_map<PlayerName, std::size_t> number_of_games_;
    for (const Game& game : games) {
      for (const PlayerName& player_name : game.player_names()) {
        const std::unordered_map<PlayerName, std::size_t>::iterator found{number_of_games_.find(player_name)};
        if (found != number_of_games_.cend()) {
          ++(found->second);
        } else {
          number_of_games_.emplace(player_name, 1);
        }
      }
    }
    return number_of_games_;
  }

  void initialize_indices() noexcept {
    for (std::size_t index = 0; index < data_.size(); ++index) {
      indices_.emplace(data_[index].name(), index);
    }
  }

  /// \brief Update all the players with all the games.
  void update(const Games& games) noexcept {
    // Iterate through the games in chronological order.
    // The games are listed in reverse-chronological order, so use a reverse iterator.
    for (Games::const_reverse_iterator game = games.crbegin(); game != games.crend(); ++game) {
      const std::unordered_map<PlayerName, EloRating> current_elo_ratings_{current_elo_ratings()};
      for (Player& player : data_) {
        player.update(*game, current_elo_ratings_);
        if (player.lowest_elo_rating() < lowest_elo_rating_) {
          lowest_elo_rating_ = player.lowest_elo_rating();
        }
        if (player.highest_elo_rating() > highest_elo_rating_) {
          highest_elo_rating_ = player.highest_elo_rating();
        }
      }
    }
  }

  std::unordered_map<PlayerName, EloRating> current_elo_ratings() const noexcept {
    std::unordered_map<PlayerName, EloRating> elo_ratings_;
    for (const Player& player : data_) {
      const std::optional<PlayerSnapshot> latest_snapshot{player.snapshots().latest()};
      if (latest_snapshot.has_value()) {
        elo_ratings_.emplace(player.name(), latest_snapshot.value().current_elo_rating());
      } else {
        elo_ratings_.emplace(player.name(), EloRating{});
      }
    }
    return elo_ratings_;
  }

}; // class Players

} // namespace TI4Echelon
