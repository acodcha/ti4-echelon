#pragma once

#include "FileWriter.hpp"

namespace TI4Echelon {

/// \brief General-purpose plain text file writer.
class TextFileWriter : public FileWriter {
protected:
  TextFileWriter(const std::filesystem::path& path,
                 const std::filesystem::perms& permissions =
                     {std::filesystem::perms::owner_read
                      | std::filesystem::perms::owner_write
                      | std::filesystem::perms::group_read
                      | std::filesystem::perms::others_read})
    : FileWriter(path, permissions) {}

  void line(const std::string& text) noexcept {
    if (stream_.is_open()) {
      stream_ << text << std::endl;
    }
  }

  void blank_line() noexcept { line(""); }

};  // class TextFileWriter

}  // namespace TI4Echelon
