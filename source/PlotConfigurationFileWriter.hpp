#pragma once

#include "Path.hpp"
#include "TextFileWriter.hpp"

namespace TI4Echelon {

/// \brief General-purpose plot configuration file writer for Gnuplot (.gnuplot).
class PlotConfigurationFileWriter : public TextFileWriter {

public:

  ~PlotConfigurationFileWriter() noexcept {
    blank_line();
  }

protected:

  /// \brief Constructor. Takes a file stem, i.e. a file path without a file extension. The file extension is appended automatically.
  PlotConfigurationFileWriter(const std::filesystem::path& stem) noexcept : TextFileWriter(stem.string() + "." + Path::PlotConfigurationFileExtension.string()) {
    line("set terminal pngcairo color size " + std::to_string(PlotWidthPixels) + "," + std::to_string(PlotHeightPixels) + " enhanced font \"Verdana,10\"");
    line("set output \"" + stem.string() + "." + Path::PlotImageFileExtension.string() + "\"");
  }

  int64_t nearest_higher_nice_number(const double value, const int64_t increment) const noexcept {
    return increment * static_cast<int64_t>(std::ceil(value / increment));
  }

  int64_t nearest_lower_nice_number(const double value, const int64_t increment) const noexcept {
    return increment * static_cast<int64_t>(std::floor(value / increment));
  }

}; // class PlotConfigurationFileWriter

} // namespace TI4Echelon
