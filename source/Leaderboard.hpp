#pragma once

#include "DataFileWriter.hpp"
#include "DurationPlotConfigurationFileWriter.hpp"
#include "LeaderboardFileWriter.hpp"
#include "PointsPlotConfigurationFileWriter.hpp"
#include "RatingsPlotConfigurationFileWriter.hpp"
#include "WinRatesPlotConfigurationFileWriter.hpp"

namespace TI4Echelon {

/// \brief Class that writes all leaderboard files given games, players, and factions data.
class Leaderboard {

public:

  Leaderboard(const std::filesystem::path& directory, const Games& games, const Players& players, const Factions& factions) {
    if (!directory.empty()) {
      create_directories(directory, players, factions);
      write_player_data_files(directory, players);
      write_faction_data_files(directory, factions);
      write_duration_data_files(directory, games);
      write_leaderboard_file(directory, games, players, factions);
      write_player_plot_configuration_files(directory, players);
      write_faction_plot_configuration_files(directory, factions);
      write_duration_plot_configuration_file(directory, games);
      generate_player_plots(directory);
      generate_faction_plots(directory);
      generate_duration_plot(directory);
      message("Wrote the leaderboard to '" + directory.string() + "'.");
    }
  }

private:

  void create_directories(const std::filesystem::path& directory, const Players& players, const Factions& factions) const {
    create(directory);
    create(directory / Path::PlayersDirectoryName);
    create(directory / Path::FactionsDirectoryName);
    for (const Player& player : players) {
      create(directory / Path::PlayersDirectoryName / player.name().path());
    }
    for (const Faction& faction : factions) {
      create(directory / Path::FactionsDirectoryName / path(faction.name()));
    }
    message("Created the directories.");
  }

  void write_player_data_files(const std::filesystem::path& directory, const Players& players) const {
    for (const Player& player : players) {
      Table table;
      table.insert_column("GlobalGameNumber"); // Column index 0
      table.insert_column("PlayerGameNumber"); // Column index 1
      table.insert_column("Date"); // Column index 2
      table.insert_column("CurrentRating"); // Column index 3
      table.insert_column("AverageRating"); // Column index 4
      table.insert_column("AveragePointsPerGame"); // Column index 5
      table.insert_column("EffectiveWinRate"); // Column index 6
      table.insert_column("1stPlacePercentage"); // Column index 7
      table.insert_column("2ndPlacePercentage"); // Column index 8
      table.insert_column("3rdPlacePercentage"); // Column index 9
      for (Player::const_reverse_iterator snapshot = player.crbegin(); snapshot != player.crend(); ++snapshot) {
        table.column(0).insert_row(snapshot->global_game_number());
        table.column(1).insert_row(snapshot->local_game_number());
        table.column(2).insert_row(snapshot->date());
        table.column(3).insert_row(snapshot->current_elo_rating());
        table.column(4).insert_row(snapshot->average_elo_rating());
        table.column(5).insert_row(snapshot->average_victory_points_per_game());
        table.column(6).insert_row(snapshot->effective_win_rate());
        table.column(7).insert_row(snapshot->place_percentage({1}));
        table.column(8).insert_row(snapshot->place_percentage({2}));
        table.column(9).insert_row(snapshot->place_percentage({3}));
      }
      DataFileWriter{directory / Path::PlayersDirectoryName / player.name().path() / Path::PlayerDataFileName, table};
    }
    message("Wrote the player data files.");
  }

  void write_faction_data_files(const std::filesystem::path& directory, const Factions& factions) const {
    for (const Faction& faction : factions) {
      Table table;
      table.insert_column("GlobalGameNumber"); // Column index 0
      table.insert_column("PlayerGameNumber"); // Column index 1
      table.insert_column("Date"); // Column index 2
      table.insert_column("CurrentRating"); // Column index 3
      table.insert_column("AverageRating"); // Column index 4
      table.insert_column("AveragePointsPerGame"); // Column index 5
      table.insert_column("EffectiveWinRate"); // Column index 6
      table.insert_column("1stPlacePercentage"); // Column index 7
      table.insert_column("2ndPlacePercentage"); // Column index 8
      table.insert_column("3rdPlacePercentage"); // Column index 9
      for (Player::const_reverse_iterator snapshot = faction.crbegin(); snapshot != faction.crend(); ++snapshot) {
        table.column(0).insert_row(snapshot->global_game_number());
        table.column(1).insert_row(snapshot->local_game_number());
        table.column(2).insert_row(snapshot->date());
        table.column(3).insert_row(snapshot->current_elo_rating());
        table.column(4).insert_row(snapshot->average_elo_rating());
        table.column(5).insert_row(snapshot->average_victory_points_per_game());
        table.column(6).insert_row(snapshot->effective_win_rate());
        table.column(7).insert_row(snapshot->place_percentage({1}));
        table.column(8).insert_row(snapshot->place_percentage({2}));
        table.column(9).insert_row(snapshot->place_percentage({3}));
      }
      DataFileWriter{directory / Path::FactionsDirectoryName / path(faction.name()) / Path::FactionDataFileName, table};
    }
    message("Wrote the faction data files.");
  }

  void write_duration_data_files(const std::filesystem::path& directory, const Games& games) const noexcept {
    write_duration_values_data_files(directory, games);
    write_duration_regression_fit_data_files(directory, games);
  }

  void write_duration_values_data_files(const std::filesystem::path& directory, const Games& games) const noexcept {
    Table table;
    table.insert_column("NumberOfPlayers"); // Column index 0
    table.insert_column("GameDurationInHours"); // Column index 1
    for (const std::pair<double, double>& number_of_players_and_game_duration_in_hours : games.duration_versus_number_of_players()) {
      table.column(0).insert_row(number_of_players_and_game_duration_in_hours.first);
      table.column(1).insert_row(number_of_players_and_game_duration_in_hours.second);
    }
    DataFileWriter{directory / Path::DurationValuesDataFileName, table};
  }

  void write_duration_regression_fit_data_files(const std::filesystem::path& directory, const Games& games) const noexcept {
    Table table;
    table.insert_column("NumberOfPlayers"); // Column index 0
    table.insert_column("GameDurationInHours"); // Column index 1
    const std::set<std::size_t> numbers_of_players{PlotMinimumNumberOfPlayers, PlotMaximumNumberOfPlayers};
    for (const std::size_t number_of_players : numbers_of_players) {
      table.column(0).insert_row(number_of_players);
      table.column(1).insert_row({games.duration_versus_number_of_players().linear_regression()(number_of_players), 2});
    }
    DataFileWriter{directory / Path::DurationRegressionFitDataFileName, table};
  }

  void write_leaderboard_file(const std::filesystem::path& directory, const Games& games, const Players& players, const Factions& factions) const {
    LeaderboardFileWriter{directory, games, players, factions};
    message("Wrote the leaderboard Markdown file.");
  }

  void write_player_plot_configuration_files(const std::filesystem::path& directory, const Players& players) const {
    RatingsPlotConfigurationFileWriter{directory, players};
    PointsPlotConfigurationFileWriter{directory, players};
    WinRatesPlotConfigurationFileWriter{directory, players};
    message("Wrote the player plot configuration Gnuplot files.");
  }

  void write_faction_plot_configuration_files(const std::filesystem::path& directory, const Factions& factions) const {
    RatingsPlotConfigurationFileWriter{directory, factions, Half::First};
    PointsPlotConfigurationFileWriter{directory, factions, Half::First};
    WinRatesPlotConfigurationFileWriter{directory, factions, Half::First};
    RatingsPlotConfigurationFileWriter{directory, factions, Half::Second};
    PointsPlotConfigurationFileWriter{directory, factions, Half::Second};
    WinRatesPlotConfigurationFileWriter{directory, factions, Half::Second};
    message("Wrote the faction plot configuration Gnuplot files.");
  }

  void write_duration_plot_configuration_file(const std::filesystem::path& directory, const Games& games) const noexcept {
    DurationPlotConfigurationFileWriter{directory, games};
    message("Wrote the duration plot configuration Gnuplot file.");
  }

  void generate_player_plots(const std::filesystem::path& directory) const {
    message("Generating the player plots...");
    generate_plot(directory / Path::PlayersDirectoryName / file_name(Path::RatingsPlotFileStem, Path::PlotConfigurationFileExtension));
    generate_plot(directory / Path::PlayersDirectoryName / file_name(Path::PointsPlotFileStem, Path::PlotConfigurationFileExtension));
    generate_plot(directory / Path::PlayersDirectoryName / file_name(Path::WinRatesPlotFileStem, Path::PlotConfigurationFileExtension));
    message("Generated the player plots.");
  }

  void generate_faction_plots(const std::filesystem::path& directory) const {
    message("Generating the faction plots...");
    generate_plot(directory / Path::FactionsDirectoryName / file_name(Path::RatingsPlotFileStem, Half::First, Path::PlotConfigurationFileExtension));
    generate_plot(directory / Path::FactionsDirectoryName / file_name(Path::RatingsPlotFileStem, Half::Second, Path::PlotConfigurationFileExtension));
    generate_plot(directory / Path::FactionsDirectoryName / file_name(Path::PointsPlotFileStem, Half::First, Path::PlotConfigurationFileExtension));
    generate_plot(directory / Path::FactionsDirectoryName / file_name(Path::PointsPlotFileStem, Half::Second, Path::PlotConfigurationFileExtension));
    generate_plot(directory / Path::FactionsDirectoryName / file_name(Path::WinRatesPlotFileStem, Half::First, Path::PlotConfigurationFileExtension));
    generate_plot(directory / Path::FactionsDirectoryName / file_name(Path::WinRatesPlotFileStem, Half::Second, Path::PlotConfigurationFileExtension));
    message("Generated the faction plots.");
  }

  void generate_duration_plot(const std::filesystem::path& directory) const {
    message("Generating the duration plot...");
    generate_plot(directory / file_name(Path::DurationPlotFileStem, Path::PlotConfigurationFileExtension));
    message("Generated the duration plot.");
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
