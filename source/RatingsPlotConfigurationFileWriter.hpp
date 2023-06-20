#pragma once

#include "Factions.hpp"
#include "Players.hpp"
#include "PlotConfigurationFileWriter.hpp"

namespace TI4Echelon {

class RatingsPlotConfigurationFileWriter : public PlotConfigurationFileWriter {
public:
  RatingsPlotConfigurationFileWriter(
      const std::filesystem::path& directory, const Players& players)
    : PlotConfigurationFileWriter(
        directory / Path::PlayersDirectoryName / Path::RatingsPlotFileStem) {
    const int64_t y_minimum{std::min(
        static_cast<int64_t>(EloRating{}.value() - increment_),
        nearest_lower_nice_number(
            players.lowest_elo_rating().value(), increment_))};
    const int64_t y_maximum{std::max(
        static_cast<int64_t>(EloRating{}.value() + increment_),
        nearest_higher_nice_number(
            players.highest_elo_rating().value(), increment_))};
    initialize(y_minimum, y_maximum);
    for (const Player& player : players) {
      if (player.color().has_value()) {
        line("  \""
             + std::filesystem::path{directory / Path::PlayersDirectoryName
                                     / player.name().path()
                                     / Path::PlayerDataFileName}
                   .string()
             + "\" u 1:4 w lp lw 2 pt 7 ps 0.1 lt rgb \"#"
             + color_code(player.color().value()) + "\" t \""
             + player.name().value() + "\" , \\");
      }
    }
  }

  RatingsPlotConfigurationFileWriter(const std::filesystem::path& directory,
                                     const Factions& factions, const Half half)
    : PlotConfigurationFileWriter(
        directory / Path::FactionsDirectoryName
        / std::filesystem::path{
            Path::RatingsPlotFileStem.string() + label(half)}) {
    const int64_t y_minimum{std::min(
        static_cast<int64_t>(EloRating{}.value() - increment_),
        nearest_lower_nice_number(
            factions.lowest_elo_rating().value(), increment_))};
    const int64_t y_maximum{std::max(
        static_cast<int64_t>(EloRating{}.value() + increment_),
        nearest_higher_nice_number(
            factions.highest_elo_rating().value(), increment_))};
    initialize(y_minimum, y_maximum);
    for (const Faction& faction : factions) {
      if (faction.half().has_value() && faction.half().value() == half
          && faction.color().has_value()) {
        line("  \""
             + std::filesystem::path{directory / Path::FactionsDirectoryName
                                     / TI4Echelon::path(faction.name())
                                     / Path::FactionDataFileName}
                   .string()
             + "\" u 1:4 w lp lw 2 pt 7 ps 0.1 lt rgb \"#"
             + color_code(faction.color().value()) + "\" t \""
             + label(faction.name()) + "\" , \\");
      }
    }
  }

private:
  static const int64_t increment_{100};

  void initialize(const int64_t y_minimum, const int64_t y_maximum) noexcept {
    line("set title \"\"");
    line(
        "set object 1 rectangle from screen 0,0 to screen 1,1 fillstyle solid "
        "1.0 fillcolor rgb \"#"
        + color_code(Color::LightGray) + "\" behind");
    line("set grid xtics ytics mxtics mytics back");
    line("set key horizontal center top outside");
    line("set xlabel \"Game Number\"");
    line("set xtics nomirror out");
    line("set mxtics 1");
    line("set ylabel \"Rating\"");
    line("set yrange [" + std::to_string(y_minimum) + ":"
         + std::to_string(y_maximum) + "]");
    line("set ytics mirror out");
    line("set mytics 5");
    line("set y2label \"\"");
    line("set y2range [" + std::to_string(y_minimum) + ":"
         + std::to_string(y_maximum) + "]");
    line("set y2tics mirror in");
    line("set my2tics 5");
    line("plot \\");
  }

};  // class RatingsPlotConfigurationFileWriter

}  // namespace TI4Echelon
