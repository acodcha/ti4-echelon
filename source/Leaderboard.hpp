#pragma once

#include "DataFileWriter.hpp"
#include "GlobalLeaderboardFileWriter.hpp"
#include "GlobalPointsPlotConfigurationFileWriter.hpp"
#include "GlobalRatingsPlotConfigurationFileWriter.hpp"
#include "GlobalWinRatesPlotConfigurationFileWriter.hpp"

namespace TI4Echelon {

/// \brief Class that writes all leaderboard files given games, players, and factions data.
class Leaderboard {

public:

  Leaderboard(const std::filesystem::path& directory, const Games& games, const Players& players) {
    if (!directory.empty()) {
      create_directories(directory, players);
      write_player_data_files(directory, players);
      write_global_leaderboard_file(directory, games, players);
      write_global_plot_configuration_files(directory, players);
      generate_global_plots(directory);
      message("Wrote the leaderboard to '" + directory.string() + "'.");
    }
  }

private:

  void create_directories(const std::filesystem::path& directory, const Players& players) const {
    create(directory);
    create(directory / Path::PlayersDirectoryName);
    for (const Player& player : players) {
      create(directory / Path::PlayersDirectoryName / std::filesystem::path{player.name().value()});
    }
    message("Created the directories.");
  }

  void write_player_data_files(const std::filesystem::path& directory, const Players& players) const {
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

  void write_global_leaderboard_file(const std::filesystem::path& directory, const Games& games, const Players& players) const {
    GlobalLeaderboardFileWriter{directory, games, players};
    message("Wrote the global leaderboard Markdown file.");
  }

  void write_global_plot_configuration_files(const std::filesystem::path& directory, const Players& players) const {
    GlobalRatingsPlotConfigurationFileWriter{directory, players};
    GlobalPointsPlotConfigurationFileWriter{directory, players};
    GlobalWinRatesPlotConfigurationFileWriter{directory, players};
    message("Wrote the global plot configuration Gnuplot files.");
  }

  void generate_global_plots(const std::filesystem::path& directory) const {
    message("Generating the global plots...");
    generate_plot(directory / Path::PlayersDirectoryName / file_name(Path::RatingsPlotFileStem, Path::PlotConfigurationFileExtension));
    generate_plot(directory / Path::PlayersDirectoryName / file_name(Path::PointsPlotFileStem, Path::PlotConfigurationFileExtension));
    generate_plot(directory / Path::PlayersDirectoryName / file_name(Path::WinRatesPlotFileStem, Path::PlotConfigurationFileExtension));
    message("Generated the global plots.");
  }

  /// \brief Generate a plot using Gnuplot. If the path points to a file that does not exist, no plot is generated.
  void generate_plot(const std::filesystem::path& path) const {
    if (std::filesystem::exists(path)) {
      const std::string command{"gnuplot " + path.string()};
      const int outcome{std::system(command.c_str())};
      if (outcome != 0) {
        error("Could not run the command: " + command);
      }
    }
  }

}; // class Leaderboard

} // namespace TI4Echelon
