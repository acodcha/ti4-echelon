#pragma once

#include "Half.hpp"

namespace TI4Echelon {

// The directory and file structure is as follows:
// leaderboard/
//     README.md
//     duration.dat
//     duration.gnuplot
//     duration.png
//     players/
//         points.gnuplot
//         points.png
//         ratings.gnuplot
//         ratings.png
//         winrates.gnuplot
//         winrates.png
//         Alice/
//             data.dat
//         Bob/
//             data.dat
//         etc.
//     factions/
//         points.gnuplot
//         points.png
//         ratings.gnuplot
//         ratings.png
//         winrates.gnuplot
//         winrates.png
//         Arborec/
//             data.dat
//         Argent Flight/
//             data.dat
//         etc.

namespace Path {

const std::filesystem::path PlayersDirectoryName{"players"};

const std::filesystem::path FactionsDirectoryName{"factions"};

const std::filesystem::path LeaderboardFileName{"README.md"};

const std::filesystem::path PlayerDataFileName{"data.dat"};

const std::filesystem::path FactionDataFileName{"data.dat"};

const std::filesystem::path DurationValuesDataFileName{"duration_data.dat"};

const std::filesystem::path DurationRegressionFitDataFileName{
    "duration_regression_fit.dat"};

const std::filesystem::path RatingsPlotFileStem{"ratings"};

const std::filesystem::path PointsPlotFileStem{"points"};

const std::filesystem::path WinRatesPlotFileStem{"winrates"};

const std::filesystem::path DurationPlotFileStem{"duration"};

const std::filesystem::path PlotConfigurationFileExtension{"gnuplot"};

const std::filesystem::path PlotImageFileExtension{"png"};

}  // namespace Path

const std::filesystem::path file_name(
    const std::filesystem::path& stem,
    const std::filesystem::path& extension) noexcept {
  return {stem.string() + "." + extension.string()};
}

const std::filesystem::path file_name(
    const std::filesystem::path& stem, const Half half,
    const std::filesystem::path& extension) noexcept {
  return {stem.string() + label(half) + "." + extension.string()};
}

}  // namespace TI4Echelon
