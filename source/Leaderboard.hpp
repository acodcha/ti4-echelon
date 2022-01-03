#pragma once

#include "DataFileWriter.hpp"
#include "GlobalLeaderboardFileWriter.hpp"

namespace TI4Echelon {

/// \brief Class that writes all leaderboard files given games, players, and factions data.
class Leaderboard {

public:

  Leaderboard(const std::filesystem::path& directory, const Games& games, const Players& players) {
    if (!directory.empty()) {
      create_directories(directory, players);
      write_player_data_files(directory, players);
      write_global_leaderboard_file(directory, games, players);
    }
  }

private:

  void create_directories(const std::filesystem::path& directory, const Players& players) {
    message("Creating the directories...");
    create(directory);
    create(directory / Path::PlayersDirectoryName);
    for (const Player& player : players) {
      create(directory / Path::PlayersDirectoryName / std::filesystem::path{player.name().value()});
    }
    message("Created the directories.");
  }

  void write_player_data_files(const std::filesystem::path& directory, const Players& players) {
    message("Writing the player data files...");
    for (const Player& player : players) {
      Table table;
      table.insert_column("GlobalGame#"); // Column index 0
      table.insert_column("PlayerGame#"); // Column index 1
      table.insert_column("Date"); // Column index 2
      table.insert_column("CurrentRating"); // Column index 3
      table.insert_column("AverageRating"); // Column index 4
      table.insert_column("AveragePoints/Game"); // Column index 5
      table.insert_column("1stPlace%"); // Column index 6
      table.insert_column("2ndPlace%"); // Column index 7
      table.insert_column("3rdPlace%"); // Column index 8
      for (PlayerSnapshots::const_reverse_iterator snapshot = player.snapshots().crbegin(); snapshot != player.snapshots().crend(); ++snapshot) {
        table.column(0).insert_row(snapshot->global_game_number());
        table.column(1).insert_row(snapshot->player_game_number());
        table.column(2).insert_row(snapshot->date());
        table.column(3).insert_row(snapshot->current_elo_rating());
        table.column(4).insert_row(snapshot->average_elo_rating());
        table.column(5).insert_row(snapshot->average_victory_points_per_game());
        table.column(6).insert_row(snapshot->place_percentage({1}));
        table.column(7).insert_row(snapshot->place_percentage({2}));
        table.column(8).insert_row(snapshot->place_percentage({3}));
      }
      DataFileWriter{directory / Path::PlayersDirectoryName / std::filesystem::path{player.name().value()} / Path::DataFileName, table};
    }
    message("Wrote the player data files.");
  }

  void write_global_leaderboard_file(const std::filesystem::path& directory, const Games& games, const Players& players) noexcept {
    GlobalLeaderboardFileWriter{directory, games, players};
    message("Wrote the global leaderboard Markdown file.");
  }

}; // class Leaderboard

} // namespace TI4Echelon
