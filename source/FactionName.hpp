#pragma once

#include "Base.hpp"

namespace TI4Echelon {

enum class FactionName : int8_t {
  Arborec,
  ArgentFlight,
  BaronyOfLetnev,
  ClanOfSaar,
  CouncilKeleres,
  EmbersOfMuaat,
  EmiratesOfHacan,
  Empyrean,
  FederationOfSol,
  GhostsOfCreuss,
  L1z1xMindnet,
  MahactGeneSorcerers,
  MentakCoalition,
  NaaluCollective,
  NaazRokhaAlliance,
  NekroVirus,
  Nomad,
  SardakkNorr,
  TitansOfUl,
  UniversitiesOfJolNar,
  VuilraithCabal,
  Winnu,
  XxchaKingdom,
  YinBrotherhood,
  YssarilTribes,
  Custom,
};

template <>
const std::unordered_map<FactionName, std::string> labels<FactionName>{
    {FactionName::Arborec,              "Arborec"                },
    {FactionName::ArgentFlight,         "Argent Flight"          },
    {FactionName::BaronyOfLetnev,       "Barony of Letnev"       },
    {FactionName::ClanOfSaar,           "Clan of Saar"           },
    {FactionName::CouncilKeleres,       "Council Keleres"        },
    {FactionName::EmbersOfMuaat,        "Embers of Muaat"        },
    {FactionName::EmiratesOfHacan,      "Emirates of Hacan"      },
    {FactionName::Empyrean,             "Empyrean"               },
    {FactionName::FederationOfSol,      "Federation of Sol"      },
    {FactionName::GhostsOfCreuss,       "Ghosts of Creuss"       },
    {FactionName::L1z1xMindnet,         "L1z1x Mindnet"          },
    {FactionName::MahactGeneSorcerers,  "Mahact Gene-Sorcerers"  },
    {FactionName::MentakCoalition,      "Mentak Coalition"       },
    {FactionName::NaaluCollective,      "Naalu Collective"       },
    {FactionName::NaazRokhaAlliance,    "Naaz-Rokha Alliance"    },
    {FactionName::NekroVirus,           "Nekro Virus"            },
    {FactionName::Nomad,                "Nomad"                  },
    {FactionName::SardakkNorr,          "Sardakk N'orr"          },
    {FactionName::TitansOfUl,           "Titans of Ul"           },
    {FactionName::UniversitiesOfJolNar, "Universities of Jol-Nar"},
    {FactionName::VuilraithCabal,       "Vuil'raith Cabal"       },
    {FactionName::Winnu,                "Winnu"                  },
    {FactionName::XxchaKingdom,         "Xxcha Kingdom"          },
    {FactionName::YinBrotherhood,       "Yin Brotherhood"        },
    {FactionName::YssarilTribes,        "Yssaril Tribes"         },
    {FactionName::Custom,               "Custom"                 },
};

template <>
const std::unordered_map<std::string, FactionName> spellings<FactionName>{
    {"Arborec",                 FactionName::Arborec             },
    {"Argent Flight",           FactionName::ArgentFlight        },
    {"Barony of Letnev",        FactionName::BaronyOfLetnev      },
    {"Clan of Saar",            FactionName::ClanOfSaar          },
    {"Council Keleres",         FactionName::CouncilKeleres      },
    {"Embers of Muaat",         FactionName::EmbersOfMuaat       },
    {"Emirates of Hacan",       FactionName::EmiratesOfHacan     },
    {"Empyrean",                FactionName::Empyrean            },
    {"Federation of Sol",       FactionName::FederationOfSol     },
    {"Ghosts of Creuss",        FactionName::GhostsOfCreuss      },
    {"L1z1x Mindnet",           FactionName::L1z1xMindnet        },
    {"Mahact Gene-Sorcerers",   FactionName::MahactGeneSorcerers },
    {"Mentak Coalition",        FactionName::MentakCoalition     },
    {"Naalu Collective",        FactionName::NaaluCollective     },
    {"Naaz-Rokha Alliance",     FactionName::NaazRokhaAlliance   },
    {"Nekro Virus",             FactionName::NekroVirus          },
    {"Nomad",                   FactionName::Nomad               },
    {"Sardakk N'orr",           FactionName::SardakkNorr         },
    {"Titans of Ul",            FactionName::TitansOfUl          },
    {"Universities of Jol-Nar", FactionName::UniversitiesOfJolNar},
    {"Vuil'raith Cabal",        FactionName::VuilraithCabal      },
    {"Winnu",                   FactionName::Winnu               },
    {"Xxcha Kingdom",           FactionName::XxchaKingdom        },
    {"Yin Brotherhood",         FactionName::YinBrotherhood      },
    {"Yssaril Tribes",          FactionName::YssarilTribes       },
    {"Custom",                  FactionName::Custom              },
};

std::filesystem::path path(const FactionName faction_name) noexcept {
  return {remove_non_alphanumeric_characters(label(faction_name))};
}

/// \brief All faction names listed alphabetically, except for the Custom
/// faction name.
const std::set<FactionName, std::less<FactionName>> FactionNames{
    FactionName::Arborec,
    FactionName::ArgentFlight,
    FactionName::BaronyOfLetnev,
    FactionName::ClanOfSaar,
    FactionName::CouncilKeleres,
    FactionName::EmbersOfMuaat,
    FactionName::EmiratesOfHacan,
    FactionName::Empyrean,
    FactionName::FederationOfSol,
    FactionName::GhostsOfCreuss,
    FactionName::L1z1xMindnet,
    FactionName::MahactGeneSorcerers,
    FactionName::MentakCoalition,
    FactionName::NaaluCollective,
    FactionName::NaazRokhaAlliance,
    FactionName::NekroVirus,
    FactionName::Nomad,
    FactionName::SardakkNorr,
    FactionName::TitansOfUl,
    FactionName::UniversitiesOfJolNar,
    FactionName::VuilraithCabal,
    FactionName::Winnu,
    FactionName::XxchaKingdom,
    FactionName::YinBrotherhood,
    FactionName::YssarilTribes,
};

std::size_t number_of_non_custom_factions(
    const std::set<FactionName>& faction_names) noexcept {
  std::size_t counter{0};
  for (const FactionName faction_name : faction_names) {
    if (faction_name != FactionName::Custom) {
      ++counter;
    }
  }
  return counter;
}

}  // namespace TI4Echelon
