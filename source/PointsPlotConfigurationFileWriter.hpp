#pragma once

#include "Players.hpp"
#include "PlotConfigurationFileWriter.hpp"

namespace TI4Echelon {

class PointsPlotConfigurationFileWriter : public PlotConfigurationFileWriter {

public:

  PointsPlotConfigurationFileWriter(const std::filesystem::path& directory, const Players& players) : PlotConfigurationFileWriter(directory / Path::PlayersDirectoryName / Path::PointsPlotFileStem) {
    line("set title \"\"");
    line("set object 1 rectangle from screen 0,0 to screen 1,1 fillstyle solid 1.0 fillcolor rgb \"#" + color_code(Color::LightGray) + "\" behind");
    line("set grid xtics ytics mxtics mytics back");
    line("set key horizontal center top outside");
    line("set xlabel \"Game Number\"");
    line("set xtics nomirror out");
    line("set mxtics 1");
    line("set ylabel \"Average Victory Points per Game\"");
    line("set yrange [0:10]");
    line("set ytics mirror out 1.0");
    line("set mytics 10");
    line("set y2label \"\"");
    line("set y2range [0:10]");
    line("set y2tics mirror in 1.0");
    line("set my2tics 10");
    line("plot \\");
    for (const Player& player : players) {
      if (player.color().has_value()) {
        line("  \"" + std::filesystem::path{directory / Path::PlayersDirectoryName / std::filesystem::path{player.name().value()} / Path::PlayerDataFileName}.string() + "\" u 1:6 w lp lw 2 pt 7 ps 0.1 lt rgb \"#" + color_code(player.color().value()) + "\" t \"" + player.name().value() + "\" , \\");
      }
    }
  }

}; // class PointsPlotConfigurationFileWriter

} // namespace TI4Echelon
