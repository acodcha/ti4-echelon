#pragma once

#include "File.hpp"

namespace TI4Echelon {

/// \brief General-purpose file writer.
class FileWriter : public File<std::ofstream> {
public:
  ~FileWriter() noexcept {
    set_permissions();
  }

  const std::filesystem::perms& permissions() const noexcept {
    return permissions_;
  }

protected:
  FileWriter(const std::filesystem::path& path,
             const std::filesystem::perms& permissions =
                 {std::filesystem::perms::owner_read
                  | std::filesystem::perms::owner_write
                  | std::filesystem::perms::group_read
                  | std::filesystem::perms::others_read})
    : File(path), permissions_(permissions) {}

  std::filesystem::perms permissions_;

  void set_permissions() noexcept {
    if (!path_.empty()) {
      if (std::filesystem::exists(path_)) {
        std::filesystem::permissions(path_, permissions_);
      }
    }
  }

};  // class FileWriter

}  // namespace TI4Echelon
