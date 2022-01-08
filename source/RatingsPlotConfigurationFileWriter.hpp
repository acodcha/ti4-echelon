#pragma once

#include "Players.hpp"
#include "PlotConfigurationFileWriter.hpp"

namespace TI4Echelon {

class RatingsPlotConfigurationFileWriter : public PlotConfigurationFileWriter {

public:

  RatingsPlotConfigurationFileWriter(const std::filesystem::path& directory, const Players& players) : PlotConfigurationFileWriter(directory / Path::PlayersDirectoryName / Path::RatingsPlotFileStem) {
    const int64_t y_minimum{std::min(static_cast<int64_t>(EloRating{}.value() - increment_), nearest_lower_nice_number(players.lowest_elo_rating().value(), increment_))};
    const int64_t y_maximum{std::max(static_cast<int64_t>(EloRating{}.value() + increment_), nearest_higher_nice_number(players.highest_elo_rating().value(), increment_))};
    line("set title \"\"");
    line("set object 1 rectangle from screen 0,0 to screen 1,1 fillstyle solid 1.0 fillcolor rgb \"#" + color_code(Color::LightGray) + "\" behind");
    line("set grid xtics ytics mxtics mytics back");
    line("set key horizontal center top outside");
    line("set xlabel \"Game Number\"");
    line("set xtics nomirror out");
    line("set mxtics 1");
    line("set ylabel \"Rating\"");
    line("set yrange [" + std::to_string(y_minimum) + ":" + std::to_string(y_maximum) + "]");
    line("set ytics mirror out");
    line("set mytics 5");
    line("set y2label \"\"");
    line("set y2range [" + std::to_string(y_minimum) + ":" + std::to_string(y_maximum) + "]");
    line("set y2tics mirror in");
    line("set my2tics 5");
    line("plot \\");
    for (const Player& player : players) {
      if (player.color().has_value()) {
        line("  \"" + std::filesystem::path{directory / Path::PlayersDirectoryName / std::filesystem::path{player.name().value()} / Path::PlayerDataFileName}.string() + "\" u 1:4 w lp lw 2 pt 7 ps 0.1 lt rgb \"#" + color_code(player.color().value()) + "\" t \"" + player.name().value() + "\" , \\");
      }
    }
  }

private:

  static const int64_t increment_{100};

}; // class RatingsPlotConfigurationFileWriter

} // namespace TI4Echelon
