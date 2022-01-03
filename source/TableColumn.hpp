#pragma once

#include "Alignment.hpp"
#include "TableCell.hpp"

namespace TI4Echelon {

/// \brief Column in a table.
class TableColumn {

public:

  /// \brief Default constructor. Initializes to an empty column.
  TableColumn() noexcept {}

  /// \brief Construct a column with a header and an alignment, but no rows. Rows can be inserted later.
  TableColumn(const std::string& header, const Alignment alignment) noexcept : header_(header), alignment_(alignment) {}

  const std::string& header() const noexcept {
    return header_;
  }

  const Alignment alignment() const noexcept {
    return alignment_;
  }

  struct iterator : public std::vector<TableCell>::iterator {
    iterator(const std::vector<TableCell>::iterator i) noexcept : std::vector<TableCell>::iterator(i) {}
  };

  struct const_iterator : public std::vector<TableCell>::const_iterator {
    const_iterator(const std::vector<TableCell>::const_iterator i) noexcept : std::vector<TableCell>::const_iterator(i) {}
  };

  struct reverse_iterator : public std::vector<TableCell>::reverse_iterator {
    reverse_iterator(const std::vector<TableCell>::reverse_iterator i) noexcept : std::vector<TableCell>::reverse_iterator(i) {}
  };

  struct const_reverse_iterator : public std::vector<TableCell>::const_reverse_iterator {
    const_reverse_iterator(const std::vector<TableCell>::const_reverse_iterator i) noexcept : std::vector<TableCell>::const_reverse_iterator(i) {}
  };

  bool empty() const noexcept {
    return cells_.empty();
  }

  std::size_t number_of_rows() const noexcept {
    return cells_.size();
  }

  iterator begin() noexcept {
    return iterator(cells_.begin());
  }

  const_iterator cbegin() const noexcept {
    return const_iterator(cells_.cbegin());
  }

  reverse_iterator rbegin() noexcept {
    return reverse_iterator(cells_.rbegin());
  }

  const_reverse_iterator crbegin() const noexcept {
    return const_reverse_iterator(cells_.crbegin());
  }

  iterator end() noexcept {
    return iterator(cells_.end());
  }

  const_iterator cend() const noexcept {
    return const_iterator(cells_.cend());
  }

  reverse_iterator rend() noexcept {
    return reverse_iterator(cells_.rend());
  }

  const_reverse_iterator crend() const noexcept {
    return const_reverse_iterator(cells_.crend());
  }

  void insert_row(const TableCell& cell) noexcept {
    cells_.push_back(cell);
  }

  const TableCell& row(const std::size_t index) const {
    cells_.at(index);
  }

protected:

  std::string header_;

  Alignment alignment_{Alignment::Center};

  std::vector<TableCell> cells_;

}; // class TableColumn

} // namespace TI4Echelon
