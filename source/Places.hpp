#pragma once

#include "Base.hpp"

namespace TI4Echelon {

enum class Place : int8_t {
  First = 1,
  Second = 2,
  Third = 3,
  Fourth = 4,
  Fifth = 5,
  Sixth = 6,
  Seventh = 7,
  Eighth = 8
};

template <> const std::unordered_map<Place, std::string> labels<Place>{
  {Place::First, "1st"},
  {Place::Second, "2nd"},
  {Place::Third, "3rd"},
  {Place::Fourth, "4th"},
  {Place::Fifth, "5th"},
  {Place::Sixth, "6th"},
  {Place::Seventh, "7th"},
  {Place::Eighth, "8th"}
};

template <> const std::unordered_map<std::string, Place> spellings<Place>{
  {"1st", Place::First},
  {"2nd", Place::Second},
  {"3rd", Place::Third},
  {"4th", Place::Fourth},
  {"5th", Place::Fifth},
  {"6th", Place::Sixth},
  {"7th", Place::Seventh},
  {"8th", Place::Eighth}
};

} // namespace TI4Echelon
