#pragma once

#include "Factions.hpp"
#include "Players.hpp"
#include "PlotConfigurationFileWriter.hpp"

namespace TI4Echelon {

class WinRatesPlotConfigurationFileWriter : public PlotConfigurationFileWriter {

public:

  WinRatesPlotConfigurationFileWriter(const std::filesystem::path& directory, const Players& players) : PlotConfigurationFileWriter(directory / Path::PlayersDirectoryName / Path::WinRatesPlotFileStem) {
    initialize();
    for (const Player& player : players) {
      if (player.color().has_value()) {
        line("  \"" + std::filesystem::path{directory / Path::PlayersDirectoryName / player.name().path() / Path::PlayerDataFileName}.string() + "\" u 1:7 w lp lw 2 pt 7 ps 0.1 lt rgb \"#" + color_code(player.color().value()) + "\" t \"" + player.name().value() + "\" , \\");
      }
    }
  }

  WinRatesPlotConfigurationFileWriter(const std::filesystem::path& directory, const Factions& factions, const Half half) : PlotConfigurationFileWriter(directory / Path::FactionsDirectoryName / std::filesystem::path{Path::WinRatesPlotFileStem.string() + label(half)}) {
    initialize();
    for (const FactionName faction_name : half_faction_names(half)) {
      const Factions::const_iterator faction{factions.find(faction_name)};
      if (faction->color().has_value()) {
        line("  \"" + std::filesystem::path{directory / Path::FactionsDirectoryName / TI4Echelon::path(faction->name()) / Path::FactionDataFileName}.string() + "\" u 1:7 w lp lw 2 pt 7 ps 0.1 lt rgb \"#" + color_code(faction->color().value()) + "\" t \"" + label(faction->name()) + "\" , \\");
      }
    }
  }

private:

  void initialize() noexcept {
    line("set title \"\"");
    line("set object 1 rectangle from screen 0,0 to screen 1,1 fillstyle solid 1.0 fillcolor rgb \"#" + color_code(Color::LightGray) + "\" behind");
    line("set grid xtics ytics mxtics mytics back");
    line("set key horizontal center top outside");
    line("set xlabel \"Game Number\"");
    line("set xtics nomirror out");
    line("set mxtics 1");
    line("set ylabel \"Effective Win Rate Percentage");
    line("set yrange [0:100]");
    line("set ytics mirror out 10.0");
    line("set mytics 5");
    line("set y2label \"\"");
    line("set y2range [0:100]");
    line("set y2tics mirror in 10.0");
    line("set my2tics 5");
    line("plot \\");
  }

}; // class WinRatesPlotConfigurationFileWriter

} // namespace TI4Echelon
