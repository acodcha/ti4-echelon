#pragma once

#include "TableColumn.hpp"

namespace TI4Echelon {

/// \brief General-purpose table for printing in Data (.dat) or Markdown (.md) files.
class Table {

public:

  /// \brief Default constructor. Initializes to an empty table. Columns can be added later.
  Table() noexcept {}

  std::string print_as_data() const noexcept {
    std::stringstream stream;
    stream << print_data_header();
    const std::size_t number_of_rows_{number_of_rows()};
    for (std::size_t row_index = 0; row_index < number_of_rows_; ++row_index) {
      stream << std::endl << print_data_row(row_index);
    }
    return stream.str();
  }

  std::string print_as_markdown() const noexcept {
    std::stringstream stream;
    stream << print_markdown_header();
    stream << std::endl << print_markdown_alignment();
    const std::size_t number_of_rows_{number_of_rows()};
    for (std::size_t row_index = 0; row_index < number_of_rows_; ++row_index) {
      stream << std::endl << print_markdown_row(row_index);
    }
    return stream.str();
  }

  struct iterator : public std::vector<TableColumn>::iterator {
    iterator(const std::vector<TableColumn>::iterator i) noexcept : std::vector<TableColumn>::iterator(i) {}
  };

  struct const_iterator : public std::vector<TableColumn>::const_iterator {
    const_iterator(const std::vector<TableColumn>::const_iterator i) noexcept : std::vector<TableColumn>::const_iterator(i) {}
  };

  struct reverse_iterator : public std::vector<TableColumn>::reverse_iterator {
    reverse_iterator(const std::vector<TableColumn>::reverse_iterator i) noexcept : std::vector<TableColumn>::reverse_iterator(i) {}
  };

  struct const_reverse_iterator : public std::vector<TableColumn>::const_reverse_iterator {
    const_reverse_iterator(const std::vector<TableColumn>::const_reverse_iterator i) noexcept : std::vector<TableColumn>::const_reverse_iterator(i) {}
  };

  bool empty() const noexcept {
    return columns_.empty();
  }

  std::size_t number_of_columns() const noexcept {
    return columns_.size();
  }

  /// \brief Number of rows, excluding the header and alignment rows, if any.
  std::size_t number_of_rows() const noexcept {
    std::size_t number_of_rows_{0};
    for (const TableColumn& column : columns_) {
      if (column.number_of_rows() > number_of_rows_) {
        number_of_rows_ = column.number_of_rows();
      }
    }
    return number_of_rows_;
  }

  iterator begin() noexcept {
    return iterator(columns_.begin());
  }

  const_iterator cbegin() const noexcept {
    return const_iterator(columns_.cbegin());
  }

  reverse_iterator rbegin() noexcept {
    return reverse_iterator(columns_.rbegin());
  }

  const_reverse_iterator crbegin() const noexcept {
    return const_reverse_iterator(columns_.crbegin());
  }

  iterator end() noexcept {
    return iterator(columns_.end());
  }

  const_iterator cend() const noexcept {
    return const_iterator(columns_.cend());
  }

  reverse_iterator rend() noexcept {
    return reverse_iterator(columns_.rend());
  }

  const_reverse_iterator crend() const noexcept {
    return const_reverse_iterator(columns_.crend());
  }

  void insert_column(const std::string& header, const Alignment alignment = Alignment::Center) noexcept {
    columns_.emplace_back(header, alignment);
  }

  const TableColumn& column(const std::size_t index) const {
    return columns_.at(index);
  }

  TableColumn& column(const std::size_t index) {
    return columns_.at(index);
  }

protected:

  std::vector<TableColumn> columns_;

  std::string print_data_header() const noexcept {
    std::string text{"#"};
    for (const TableColumn& column : columns_) {
      if (text.size() > 1) {
        text += " ";
      }
      text += column.header();
    }
    return text;
  }

  std::string print_markdown_header() const noexcept {
    std::string text{"|"};
    for (const TableColumn& column : columns_) {
      text += " " + markdown_boldface(column.header()) + " |";
    }
    return text;
  }

  std::string print_markdown_alignment() const noexcept {
    std::string text{"|"};
    for (const TableColumn& column : columns_) {
      text += " " + markdown(column.alignment()) + " |";
    }
    return text;
  }

  std::string print_data_row(const std::size_t index) const noexcept {
    std::string text;
    for (const TableColumn& column : columns_) {
      if (index < column.number_of_rows()) {
        if (!text.empty()) {
          text += " ";
        }
        text += column.row(index).print();
      } else {
        text += " ";
      }
    }
    return text;
  }

  std::string print_markdown_row(const std::size_t index) const noexcept {
    std::string text{"|"};
    for (const TableColumn& column : columns_) {
      if (index < column.number_of_rows()) {
        text += " " + column.row(index).print() + " |";
      } else {
        text += "  |";
      }
    }
    return text;
  }

}; // class Table

} // namespace TI4Echelon
