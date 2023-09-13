#pragma once

#include "Base.hpp"

namespace TI4Echelon {

/// \brief General-purpose file handler.
template <class FileStream>
class File {
public:
  ~File() noexcept {
    if (stream_.is_open()) {
      stream_.close();
    }
  }

  const std::filesystem::path& path() const noexcept {
    return path_;
  }

protected:
  std::filesystem::path path_;

  FileStream stream_;

  File(const std::filesystem::path& path) : path_(path) {
    if (!path_.empty()) {
      stream_.open(path_.string());
      if (!stream_.is_open()) {
        error("Could not open the file: " + path_.string());
      }
    }
  }

};  // class File

}  // namespace TI4Echelon
