#pragma once

#include "Base.hpp"

namespace TI4Echelon {

// leaderboard/
//     README.md
//     players/
//         points.gnuplot
//         points.png
//         ratings.gnuplot
//         ratings.png
//         winrates.gnuplot
//         winrates.png
//         Alice/
//             README.md
//             data.dat
//             points.gnuplot
//             points.png
//             ratings.gnuplot
//             ratings.png
//             winrates.gnuplot
//             winrates.png
//     factions/
//         points.gnuplot
//         points.png
//         ratings.gnuplot
//         ratings.png
//         winrates.gnuplot
//         winrates.png
//         Arborec/
//             README.md
//             data.dat
//             points.gnuplot
//             points.png
//             ratings.gnuplot
//             ratings.png
//             winrates.gnuplot
//             winrates.png

namespace Path {

const std::filesystem::path PlayersDirectoryName{"players"};

const std::filesystem::path FactionsDirectoryName{"factions"};

const std::filesystem::path LeaderboardFileName{"README.md"};

const std::filesystem::path DataFileName{"data.dat"};

const std::filesystem::path RatingsPlotFileStem{"ratings"};

const std::filesystem::path PointsPlotFileStem{"points"};

const std::filesystem::path WinRatesPlotFileStem{"winrates"};

const std::filesystem::path PlotConfigurationFileExtension{"gnuplot"};

const std::filesystem::path PlotImageFileExtension{"png"};

} // namespace Path

const std::filesystem::path file_name(const std::filesystem::path& stem, const std::filesystem::path& extension) noexcept {
  return {stem.string() + "." + extension.string()};
}

} // namespace TI4Echelon
