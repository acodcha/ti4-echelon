#pragma once

#include "Color.hpp"
#include "Games.hpp"
#include "PlotConfigurationFileWriter.hpp"

namespace TI4Echelon {

class DurationPlotConfigurationFileWriter : public PlotConfigurationFileWriter {

public:

  DurationPlotConfigurationFileWriter(const std::filesystem::path& directory, const Games& games) : PlotConfigurationFileWriter(directory / Path::DurationPlotFileStem) {
    const int64_t y_minimum{std::max(static_cast<int64_t>(0), nearest_lower_nice_number(games.duration_versus_number_of_players().minimum_duration_in_hours(), increment_))};
    const int64_t y_maximum{std::max(increment_, nearest_higher_nice_number(games.duration_versus_number_of_players().maximum_duration_in_hours(), increment_))};
    line("set title \"\"");
    line("set object 1 rectangle from screen 0,0 to screen 1,1 fillstyle solid 1.0 fillcolor rgb \"#" + color_code(Color::LightGray) + "\" behind");
    line("set grid xtics ytics mxtics mytics back");
    line("set key horizontal center top outside");
    line("set xlabel \"Number of Players\"");
    line("set xrange [2:8]");
    line("set xtics nomirror out 1");
    line("set mxtics 1");
    line("set ylabel \"Game Duration in Hours\"");
    line("set yrange [" + std::to_string(y_minimum) + ":" + std::to_string(y_maximum) + "]");
    line("set ytics mirror out 1");
    line("set mytics 4");
    line("set y2label \"\"");
    line("set y2range [" + std::to_string(y_minimum) + ":" + std::to_string(y_maximum) + "]");
    line("set y2tics mirror in 1");
    line("set my2tics 4");
    line("plot \\");
    line("  \"" + std::filesystem::path{directory / Path::DurationDataFileName}.string() + "\" u 1:2 w p pt 7 ps 1 lt rgb \"#000000\" t \"\" , \\");
    line("  \"" + std::filesystem::path{directory / Path::DurationDataFileName}.string() + "\" u 1:3 w lp lw 2 pt 7 ps 0.1 lt rgb \"#000000\" t \"" + games.duration_versus_number_of_players().print() + "\" , \\");
  }

private:

  static const int64_t increment_{1};

}; // class DurationPlotConfigurationFileWriter

} // namespace TI4Echelon
