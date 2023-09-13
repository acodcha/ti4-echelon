#pragma once

#include "Base.hpp"

namespace TI4Echelon {

enum class GameMode : int8_t {
  FreeForAll,
  Teams
};

template <>
const std::unordered_map<GameMode, std::string> labels<GameMode>{
    {GameMode::FreeForAll, "Free-for-All"},
    {GameMode::Teams,      "Teams"       },
};

template <>
const std::unordered_map<std::string, GameMode> spellings<GameMode>{
    {"Free-for-All", GameMode::FreeForAll},
    {"free-for-all", GameMode::FreeForAll},
    {"Teams",        GameMode::Teams     },
    {"teams",        GameMode::Teams     },
};

}  // namespace TI4Echelon
