#pragma once

#include "Table.hpp"
#include "TextFileWriter.hpp"

namespace TI4Echelon {

class DataFileWriter : public TextFileWriter {

public:

  DataFileWriter(const std::filesystem::path& path, const Table& table) : TextFileWriter(path) {
    line(table.print_as_data());
    blank_line();
  }

}; // class DataFileWriter

} // namespace TI4Echelon
