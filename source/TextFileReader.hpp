#pragma once

#include "FileReader.hpp"

namespace TI4Echelon {

/// \brief General-purpose plain text file reader.
class TextFileReader : public FileReader {

public:

  TextFileReader(const std::filesystem::path& path) : FileReader(path) {
    if (stream_.is_open()) {
      std::string line;
      while (std::getline(stream_, line)) {
        lines_.push_back(line);
      }
    }
  }

  struct const_iterator : public std::vector<std::string>::const_iterator {
    const_iterator(const std::vector<std::string>::const_iterator i) noexcept : std::vector<std::string>::const_iterator(i) {}
  };

  std::size_t size() const noexcept {
    return lines_.size();
  }

  const_iterator cbegin() const noexcept {
   return const_iterator(lines_.cbegin());
  }

  const_iterator begin() const noexcept {
   return cbegin();
  }

  const_iterator cend() const noexcept {
   return const_iterator(lines_.cend());
  }

  const_iterator end() const noexcept {
   return cend();
  }

private:

  std::vector<std::string> lines_;

}; // class TextFileReader

} // namespace TI4Echelon
