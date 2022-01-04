#pragma once

#include "Players.hpp"
#include "PlotConfigurationFileWriter.hpp"

namespace TI4Echelon {

class WinRatesPlotConfigurationFileWriter : public PlotConfigurationFileWriter {

public:

  WinRatesPlotConfigurationFileWriter(const std::filesystem::path& directory, const Players& players) : PlotConfigurationFileWriter(directory / Path::PlayersDirectoryName / Path::WinRatesPlotFileStem) {
    line("set title \"\"");
    line("set object 1 rectangle from screen 0,0 to screen 1,1 fillstyle solid 1.0 fillcolor rgb \"#BFBFBF\" behind");
    line("set grid xtics ytics mxtics mytics back");
    line("set key horizontal center top outside");
    line("set xlabel \"Game Number\"");
    line("set xtics nomirror out");
    line("set mxtics 1");
    line("set ylabel \"Win Rate Percentage");
    line("set yrange [0:100]");
    line("set ytics mirror out 10.0");
    line("set mytics 10");
    line("set y2label \"\"");
    line("set y2range [0:100]");
    line("set y2tics mirror in 10.0");
    line("set my2tics 10");
    line("plot \\");
    for (const Player& player : players) {
      if (player.color().has_value()) {
        line("  \"" + std::filesystem::path{directory / Path::PlayersDirectoryName / std::filesystem::path{player.name().value()} / Path::PlayerDataFileName}.string() + "\" u 1:7 w lp lw 2 pt 7 ps 0.1 lt rgb \"#" + color_code(player.color().value()) + "\" t \"" + player.name().value() + "\" , \\");
      }
    }
  }

}; // class WinRatesPlotConfigurationFileWriter

} // namespace TI4Echelon
