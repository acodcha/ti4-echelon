#pragma once

#include "MarkdownFileWriter.hpp"
#include "Path.hpp"
#include "Players.hpp"

namespace TI4Echelon {

/// \brief File writer for the global leaderboard file.
class LeaderboardFileWriter : public MarkdownFileWriter {

public:

  LeaderboardFileWriter(
    const std::filesystem::path& directory,
    const Games& games,
    const Players& players
  ) noexcept :
    MarkdownFileWriter(directory / Path::LeaderboardFileName)
  {
    introduction();
    players_section(players);
    factions_section();
    duration_section();
    games_section(games);
    license_section();
    blank_line();
  }

private:

  const std::string section_title_players_{"Players"};

  const std::string section_title_factions_{"Factions"};

  const std::string section_title_duration_{"Time Duration"};

  const std::string section_title_games_{"Games"};

  const std::string section_title_license_{"License"};

  const std::string subsection_title_summary_{"Summary"};

  const std::string subsection_title_ratings_{"Ratings"};

  const std::string subsection_title_points_{"Average Victory Points per Game"};

  const std::string subsection_title_win_rates_{"Win Rates"};

  void introduction() noexcept {
    list_link(section_title_players_);
    nested_list_link(section_title_players_ + ": " + subsection_title_summary_);
    nested_list_link(section_title_players_ + ": " + subsection_title_ratings_);
    nested_list_link(section_title_players_ + ": " + subsection_title_points_);
    nested_list_link(section_title_players_ + ": " + subsection_title_win_rates_);
    list_link(section_title_factions_);
    nested_list_link(section_title_factions_ + ": " + subsection_title_summary_);
    nested_list_link(section_title_factions_ + ": " + subsection_title_ratings_);
    nested_list_link(section_title_factions_ + ": " + subsection_title_points_);
    nested_list_link(section_title_factions_ + ": " + subsection_title_win_rates_);
    list_link(section_title_duration_);
    list_link(section_title_games_);
    list_link(section_title_license_);
    blank_line();
    line("Last updated " + current_utc_date_and_time() + ".");
  }

  void players_section(const Players& players) noexcept {
    section(section_title_players_);
    list_link(section_title_players_ + ": " + subsection_title_summary_);
    list_link(section_title_players_ + ": " + subsection_title_ratings_);
    list_link(section_title_players_ + ": " + subsection_title_points_);
    list_link(section_title_players_ + ": " + subsection_title_win_rates_);
    link_back_to_top();
    subsection(section_title_players_ + ": " + subsection_title_summary_);
    players_summary_table(players);
    link_back_to_section(section_title_players_);
    subsection(section_title_players_ + ": " + subsection_title_ratings_);
    players_ratings_plot();
    link_back_to_section(section_title_players_);
    subsection(section_title_players_ + ": " + subsection_title_points_);
    players_points_plot();
    link_back_to_section(section_title_players_);
    subsection(section_title_players_ + ": " + subsection_title_win_rates_);
    players_win_rates_plot();
    link_back_to_section(section_title_players_);
  }

  void players_summary_table(const Players& players) noexcept {
    Table table_;
    table_.insert_column("Player", Alignment::Left); // Column index 0
    table_.insert_column("Games", Alignment::Center); // Column index 1
    table_.insert_column("Current Rating", Alignment::Center); // Column index 2
    table_.insert_column("Avg Rating", Alignment::Center); // Column index 3
    table_.insert_column("Avg Points", Alignment::Center); // Column index 4
    table_.insert_column("1st Place", Alignment::Center); // Column index 5
    table_.insert_column("2nd Place", Alignment::Center); // Column index 6
    table_.insert_column("3rd Place", Alignment::Center); // Column index 7
    for (const Player& player : players) {
      table_.column(0).insert_row(player.name());
      table_.column(1).insert_row(player.number_of_snapshots());
      table_.column(2).insert_row(player.latest_snapshot().value().current_elo_rating());
      table_.column(3).insert_row(player.latest_snapshot().value().average_elo_rating());
      table_.column(4).insert_row(player.latest_snapshot().value().average_victory_points_per_game());
      table_.column(5).insert_row(player.latest_snapshot().value().print_place_percentage_and_count({1}));
      table_.column(6).insert_row(player.latest_snapshot().value().print_place_percentage_and_count({2}));
      table_.column(7).insert_row(player.latest_snapshot().value().print_place_percentage_and_count({3}));
    }
    table(table_);
  }

  void players_ratings_plot() noexcept {
    line("![Ratings Plot](" + std::filesystem::path{Path::PlayersDirectoryName / file_name(Path::RatingsPlotFileStem, Path::PlotImageFileExtension)}.string() + ")");
  }

  void players_points_plot() noexcept {
    line("![Points Plot](" + std::filesystem::path{Path::PlayersDirectoryName / file_name(Path::PointsPlotFileStem, Path::PlotImageFileExtension)}.string() + ")");
    blank_line();
    line("Victory points are adjusted relative to a 10-point game.");
  }

  void players_win_rates_plot() noexcept {
    line("![Win Rates Plot](" + std::filesystem::path{Path::PlayersDirectoryName / file_name(Path::WinRatesPlotFileStem, Path::PlotImageFileExtension)}.string() + ")");
  }

  void factions_section() noexcept {
    section(section_title_factions_);
    list_link(section_title_factions_ + ": " + subsection_title_summary_);
    list_link(section_title_factions_ + ": " + subsection_title_ratings_);
    list_link(section_title_factions_ + ": " + subsection_title_points_);
    list_link(section_title_factions_ + ": " + subsection_title_win_rates_);
    link_back_to_top();
    subsection(section_title_factions_ + ": " + subsection_title_summary_);
    line("Coming soon!");
    link_back_to_section(section_title_factions_);
    subsection(section_title_factions_ + ": " + subsection_title_ratings_);
    line("Coming soon!");
    link_back_to_section(section_title_factions_);
    subsection(section_title_factions_ + ": " + subsection_title_points_);
    line("Coming soon!");
    link_back_to_section(section_title_factions_);
    subsection(section_title_factions_ + ": " + subsection_title_win_rates_);
    line("Coming soon!");
    link_back_to_section(section_title_factions_);
  }

  void duration_section() noexcept {
    section(section_title_duration_);
    line("![Duration Plot](" + std::filesystem::path{file_name(Path::DurationPlotFileStem, Path::PlotImageFileExtension)}.string() + ")");
    link_back_to_top();
  }

  void games_section(const Games& games) noexcept {
    section(section_title_games_);
    games_table(games);
    link_back_to_top();
  }

  void games_table(const Games& games) noexcept {
    Table table_;
    table_.insert_column("Game", Alignment::Center); // Column index 0
    table_.insert_column("Date", Alignment::Center); // Column index 1
    table_.insert_column("Mode", Alignment::Center); // Column index 2
    table_.insert_column("Points", Alignment::Center); // Column index 3
    table_.insert_column("Players", Alignment::Center); // Column index 4
    table_.insert_column("Results", Alignment::Left); // Column index 5
    for (const Game& game : games) {
      table_.column(0).insert_row(game.index() + 1);
      table_.column(1).insert_row(game.date());
      table_.column(2).insert_row(game.mode());
      table_.column(3).insert_row(game.victory_point_goal());
      table_.column(4).insert_row(game.participants().size());
      table_.column(5).insert_row((game.duration().has_value() ? game.duration().value().print() + ", " : "") + game.participants().print());
    }
    table(table_);
  }

  void license_section() noexcept {
    section(section_title_license_);
    line("This work is maintained by Alexandre Coderre-Chabot (https://github.com/acodcha) and licensed under the MIT License. For more details, see the `LICENSE` file or https://mit-license.org/. This work is based on the Twilight Imperium 4th Edition board game by Fantasy Flight Games. The contents, copyrights, and trademarks of everything involving Twilight Imperium 4th Edition are exclusively held by Fantasy Flight Games; I make no claim to any of these in any way.");
    link_back_to_top();
  }

}; // class LeaderboardFileWriter

} // namespace TI4Echelon
