#pragma once

#include "File.hpp"

namespace TI4Echelon {

/// \brief General-purpose file reader.
class FileReader : public File<std::ifstream> {

protected:

  FileReader(const std::filesystem::path& path) noexcept : File(path) {}

}; // class FileReader

} // namespace TI4Echelon
