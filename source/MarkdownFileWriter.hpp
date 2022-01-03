#pragma once

#include "Table.hpp"
#include "TextFileWriter.hpp"

namespace TI4Echelon {

class MarkdownFileWriter : public TextFileWriter {

public:

  MarkdownFileWriter(const std::filesystem::path& path) noexcept : TextFileWriter(path) {}

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

  void subsubsection(const std::string& subsubsection_title) noexcept {
    blank_line();
    line("### " + subsubsection_title);
    blank_line();
  }

  void table(const Table& table) noexcept {
    line(table.print_as_markdown());
  }

  void list_link(const std::string link) noexcept {
    line("- [" + link + "](#" + lowercase((replace_character(remove_non_alphanumeric_non_space_characters(link), ' ', '-'))) + ")");
  }

  void nested_list_link(const std::string link) noexcept {
    line("    - [" + link + "](#" + lowercase(replace_character(remove_non_alphanumeric_non_space_characters(link), ' ', '-')) + ")");
  }

  void link_back_to_section(const std::string link) noexcept {
    blank_line();
    line("[(Back to " + link + ")](#" + lowercase(replace_character(remove_non_alphanumeric_non_space_characters(link), ' ', '-')) + ")");
  }

  void link_back_to_top() noexcept {
    blank_line();
    line("[(Back to Top)](#)");
  }

  void link_back_to_main_page() noexcept {
    blank_line();
    line("[(Back to Main Page)](../../#)");
  }

}; // class MarkdownFileWriter

} // namespace MarkdownFileWriter
