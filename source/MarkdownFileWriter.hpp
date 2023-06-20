#pragma once

#include "Table.hpp"
#include "TextFileWriter.hpp"

namespace TI4Echelon {

class MarkdownFileWriter : public TextFileWriter {
public:
  MarkdownFileWriter(const std::filesystem::path& path) noexcept
    : TextFileWriter(path) {}

protected:
  void section(const std::string& section_title) noexcept {
    blank_line();
    line("# " + section_title);
    blank_line();
  }

  void subsection(const std::string& subsection_title) noexcept {
    blank_line();
    line("## " + subsection_title);
    blank_line();
  }

  void table(const Table& table) noexcept { line(table.print_as_markdown()); }

  void list(const std::string& text) noexcept { line("- " + text); }

  void link_back_to_section(const std::string& section) noexcept {
    blank_line();
    line("[(Back to " + section + ")](#"
         + lowercase(replace_character(
             remove_non_alphanumeric_non_space_characters(section), ' ', '-'))
         + ")");
  }

  void link_back_to_top() noexcept {
    blank_line();
    line("[(Back to Top)](#)");
  }

  std::string link(const std::string& section) const noexcept {
    return "[" + section + "](#"
           + lowercase(replace_character(
               remove_non_alphanumeric_non_space_characters(section), ' ', '-'))
           + ")";
  }

  std::string link(
      const std::string& title, const std::string& section) const noexcept {
    return "[" + title + "](#"
           + lowercase(replace_character(
               remove_non_alphanumeric_non_space_characters(section), ' ', '-'))
           + ")";
  }

};  // class MarkdownFileWriter

}  // namespace TI4Echelon
