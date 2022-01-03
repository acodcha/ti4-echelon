#pragma once

#include "MarkdownFileWriter.hpp"
#include "Path.hpp"
#include "Players.hpp"

namespace TI4Echelon {

/// \brief File writer for the global leaderboard file.
class GlobalLeaderboardFileWriter : public MarkdownFileWriter {

public:

  GlobalLeaderboardFileWriter(
    const std::filesystem::path& directory,
    const Games& games,
    const Players& players
  ) noexcept :
    MarkdownFileWriter(directory / Path::LeaderboardFileName)
  {
    introduction();
    players_section(directory, players);
    factions_section();
    games_section(games);
    license_section();
    blank_line();
  }

private:

  const std::string section_title_players_{"Players"};

  const std::string section_title_factions_{"Factions"};

  const std::string section_title_games_{"Games"};

  const std::string section_title_license_{"License"};

  const std::string subsection_title_summary_{"Summary"};

  const std::string subsection_title_ratings_{"Ratings"};

  const std::string subsection_title_points_{"Average Victory Points per Game"};

  const std::string subsection_title_win_rates_{"Win Rates"};

  void introduction() noexcept {
    line("Last updated " + current_utc_date_and_time() + ".");
    blank_line();
    list_link(section_title_players_);
    nested_list_link(section_title_players_ + " " + subsection_title_summary_);
    nested_list_link(section_title_players_ + " " + subsection_title_ratings_);
    nested_list_link(section_title_players_ + " " + subsection_title_points_);
    nested_list_link(section_title_players_ + " " + subsection_title_win_rates_);
    list_link(section_title_factions_);
    nested_list_link(section_title_factions_ + " " + subsection_title_summary_);
    nested_list_link(section_title_factions_ + " " + subsection_title_ratings_);
    nested_list_link(section_title_factions_ + " " + subsection_title_points_);
    nested_list_link(section_title_factions_ + " " + subsection_title_win_rates_);
    list_link(section_title_games_);
    list_link(section_title_license_);
  }

  void players_section(const std::filesystem::path& directory, const Players& players) noexcept {
    section(section_title_players_);
    list_link(section_title_players_ + " " + subsection_title_summary_);
    list_link(section_title_players_ + " " + subsection_title_ratings_);
    list_link(section_title_players_ + " " + subsection_title_points_);
    list_link(section_title_players_ + " " + subsection_title_win_rates_);
    link_back_to_top();
    subsection(section_title_players_ + " " + subsection_title_summary_);
    players_summary_table(players);
    link_back_to_section(section_title_players_);
    subsection(section_title_players_ + " " + subsection_title_ratings_);
    players_ratings_plot(directory);
    link_back_to_section(section_title_players_);
    subsection(section_title_players_ + " " + subsection_title_points_);
    players_points_plot(directory);
    link_back_to_section(section_title_players_);
    subsection(section_title_players_ + " " + subsection_title_win_rates_);
    players_win_rates_plot(directory);
    link_back_to_section(section_title_players_);
  }

  void players_summary_table(const Players& players) noexcept {
    Table table;
    table.insert_column("Player", Alignment::Left); // Column index 0
    table.insert_column("Games", Alignment::Center); // Column index 1
    table.insert_column("Current Rating", Alignment::Center); // Column index 2
    table.insert_column("Avg Rating", Alignment::Center); // Column index 3
    table.insert_column("Avg Points", Alignment::Center); // Column index 4
    table.insert_column("1st Place", Alignment::Center); // Column index 5
    table.insert_column("2nd Place", Alignment::Center); // Column index 6
    table.insert_column("3rd Place", Alignment::Center); // Column index 7
    for (const Player& player : players) {
      table.column(0).insert_row(player.name());
      table.column(1).insert_row(player.snapshots().size());
      table.column(2).insert_row(player.snapshots().latest().value().current_elo_rating());
      table.column(3).insert_row(player.snapshots().latest().value().average_elo_rating());
      table.column(4).insert_row(player.snapshots().latest().value().average_victory_points_per_game());
      table.column(5).insert_row(player.snapshots().latest().value().print_place_percentage_and_count({1}));
      table.column(6).insert_row(player.snapshots().latest().value().print_place_percentage_and_count({2}));
      table.column(7).insert_row(player.snapshots().latest().value().print_place_percentage_and_count({3}));
    }
    line(table.print_as_markdown());
  }

  void players_ratings_plot(const std::filesystem::path& directory) noexcept {
    if (std::filesystem::exists(directory / Path::PlayersDirectoryName)) {
      line("![Ratings Plot](" + std::filesystem::path{directory / Path::PlayersDirectoryName / Path::RatingsPlotFileStem}.string() + "." + Path::PlotImageFileExtension.string() + ")");
    }
  }

  void players_points_plot(const std::filesystem::path& directory) noexcept {
    if (std::filesystem::exists(directory / Path::PlayersDirectoryName)) {
      line("![Points Plot](" + std::filesystem::path{directory / Path::PlayersDirectoryName / Path::PointsPlotFileStem}.string() + "." + Path::PlotImageFileExtension.string() + ")");
    }
    blank_line();
    line("Victory points are adjusted relative to a 10-point game.");
  }

  void players_win_rates_plot(const std::filesystem::path& directory) noexcept {
    if (std::filesystem::exists(directory / Path::PlayersDirectoryName)) {
      line("![Win Rates Plot](" + std::filesystem::path{directory / Path::PlayersDirectoryName / Path::WinRatesPlotFileStem}.string() + "." + Path::PlotImageFileExtension.string() + ")");
    }
  }

  void factions_section() noexcept {
    section(section_title_factions_);
    list_link(section_title_factions_ + " " + subsection_title_summary_);
    list_link(section_title_factions_ + " " + subsection_title_ratings_);
    list_link(section_title_factions_ + " " + subsection_title_points_);
    list_link(section_title_factions_ + " " + subsection_title_win_rates_);
    link_back_to_top();
    subsection(section_title_factions_ + " " + subsection_title_summary_);
    line("Coming soon!");
    link_back_to_section(section_title_factions_);
    subsection(section_title_factions_ + " " + subsection_title_ratings_);
    line("Coming soon!");
    link_back_to_section(section_title_factions_);
    subsection(section_title_factions_ + " " + subsection_title_points_);
    line("Coming soon!");
    link_back_to_section(section_title_factions_);
    subsection(section_title_factions_ + " " + subsection_title_win_rates_);
    line("Coming soon!");
    link_back_to_section(section_title_factions_);
  }

  void games_section(const Games& games) noexcept {
    section(section_title_games_);
    games_table(games);
    link_back_to_top();
  }

  void games_table(const Games& games) noexcept {
    Table table;
    table.insert_column("Game", Alignment::Center); // Column index 0
    table.insert_column("Date", Alignment::Center); // Column index 1
    table.insert_column("Mode", Alignment::Center); // Column index 2
    table.insert_column("Points", Alignment::Center); // Column index 3
    table.insert_column("Players", Alignment::Center); // Column index 4
    table.insert_column("Results", Alignment::Left); // Column index 5
    for (const Game& game : games) {
      table.column(0).insert_row(game.index() + 1);
      table.column(1).insert_row(game.date());
      table.column(2).insert_row(game.mode());
      table.column(3).insert_row(game.victory_point_goal());
      table.column(4).insert_row(game.player_names().size());
      table.column(5).insert_row(game.participants().print());
    }
    line(table.print_as_markdown());
  }

  void license_section() noexcept {
    section(section_title_license_);
    line("This work is maintained by Alexandre Coderre-Chabot (https://github.com/acodcha) and licensed under the MIT License. For more details, see the `LICENSE` file or https://mit-license.org/. This work is based on the Twilight Imperium 4th Edition board game by Fantasy Flight Games. The contents, copyrights, and trademarks of everything involving Twilight Imperium 4th Edition are exclusively held by Fantasy Flight Games; I make no claim to any of these in any way.");
    link_back_to_top();
  }

};

} // namespace TI4Echelon
