#pragma once

#include "String.hpp"

namespace TI4Echelon {

template<typename Enumeration>
const std::unordered_map<Enumeration, std::string> labels;

template<typename Enumeration>
std::string label(const Enumeration& type) noexcept {
  const typename std::unordered_map<Enumeration, std::string>::const_iterator
      found{labels<Enumeration>.find(type)};
  if (found != labels<Enumeration>.cend()) {
    return found->second;
  } else {
    return {};
  }
}

template<typename Enumeration>
std::string label(const std::optional<Enumeration>& type) noexcept {
  if (type.has_value()) {
    return label(type.value());
  } else {
    return {};
  }
}

template<typename Enumeration>
const std::unordered_map<std::string, Enumeration> spellings;

template<typename Enumeration>
std::optional<Enumeration> type(const std::string& spelling) noexcept {
  const typename std::unordered_map<std::string, Enumeration>::const_iterator
      enumeration{spellings<Enumeration>.find(spelling)};
  if (enumeration != spellings<Enumeration>.cend()) {
    return {enumeration->second};
  } else {
    const std::optional<Enumeration> no_data;
    return no_data;
  }
}

}  // namespace TI4Echelon
