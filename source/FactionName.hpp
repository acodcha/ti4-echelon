#pragma once

#include "Color.hpp"
#include "Half.hpp"

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
  Custom
};

template <> const std::unordered_map<FactionName, std::string> labels<FactionName>{
  {FactionName::Arborec, "Arborec"},
  {FactionName::ArgentFlight, "Argent Flight"},
  {FactionName::BaronyOfLetnev, "Barony of Letnev"},
  {FactionName::ClanOfSaar, "Clan of Saar"},
  {FactionName::CouncilKeleres, "Council Keleres"},
  {FactionName::EmbersOfMuaat, "Embers of Muaat"},
  {FactionName::EmiratesOfHacan, "Emirates of Hacan"},
  {FactionName::Empyrean, "Empyrean"},
  {FactionName::FederationOfSol, "Federation of Sol"},
  {FactionName::GhostsOfCreuss, "Ghosts of Creuss"},
  {FactionName::L1z1xMindnet, "L1z1x Mindnet"},
  {FactionName::MahactGeneSorcerers, "Mahact Gene-Sorcerers"},
  {FactionName::MentakCoalition, "Mentak Coalition"},
  {FactionName::NaaluCollective, "Naalu Collective"},
  {FactionName::NaazRokhaAlliance, "Naaz-Rokha Alliance"},
  {FactionName::NekroVirus, "Nekro Virus"},
  {FactionName::Nomad, "Nomad"},
  {FactionName::SardakkNorr, "Sardakk N'orr"},
  {FactionName::TitansOfUl, "Titans of Ul"},
  {FactionName::UniversitiesOfJolNar, "Universities of Jol-Nar"},
  {FactionName::VuilraithCabal, "Vuil'raith Cabal"},
  {FactionName::Winnu, "Winnu"},
  {FactionName::XxchaKingdom, "Xxcha Kingdom"},
  {FactionName::YinBrotherhood, "Yin Brotherhood"},
  {FactionName::YssarilTribes, "Yssaril Tribes"},
  {FactionName::Custom, "Custom"}
};

template <> const std::unordered_map<std::string, FactionName> spellings<FactionName>{
  {"Arborec", FactionName::Arborec},
  {"Argent Flight", FactionName::ArgentFlight},
  {"Barony of Letnev", FactionName::BaronyOfLetnev},
  {"Clan of Saar", FactionName::ClanOfSaar},
  {"Council Keleres", FactionName::CouncilKeleres},
  {"Embers of Muaat", FactionName::EmbersOfMuaat},
  {"Emirates of Hacan", FactionName::EmiratesOfHacan},
  {"Empyrean", FactionName::Empyrean},
  {"Federation of Sol", FactionName::FederationOfSol},
  {"Ghosts of Creuss", FactionName::GhostsOfCreuss},
  {"L1z1x Mindnet", FactionName::L1z1xMindnet},
  {"Mahact Gene-Sorcerers", FactionName::MahactGeneSorcerers},
  {"Mentak Coalition", FactionName::MentakCoalition},
  {"Naalu Collective", FactionName::NaaluCollective},
  {"Naaz-Rokha Alliance", FactionName::NaazRokhaAlliance},
  {"Nekro Virus", FactionName::NekroVirus},
  {"Nomad", FactionName::Nomad},
  {"Sardakk N'orr", FactionName::SardakkNorr},
  {"Titans of Ul", FactionName::TitansOfUl},
  {"Universities of Jol-Nar", FactionName::UniversitiesOfJolNar},
  {"Vuil'raith Cabal", FactionName::VuilraithCabal},
  {"Winnu", FactionName::Winnu},
  {"Xxcha Kingdom", FactionName::XxchaKingdom},
  {"Yin Brotherhood", FactionName::YinBrotherhood},
  {"Yssaril Tribes", FactionName::YssarilTribes},
  {"Custom", FactionName::Custom}
};

std::filesystem::path path(const FactionName faction_name) noexcept {
  return {remove_non_alphanumeric_characters(label(faction_name))};
}

/// \brief All faction names listed alphabetically, except for the Custom faction name.
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
  FactionName::YssarilTribes
};

namespace {

template <Half half> const std::set<FactionName, std::less<FactionName>> HalfFactionNames;

template <> const std::set<FactionName, std::less<FactionName>> HalfFactionNames<Half::First>{
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
  FactionName::MentakCoalition
};

template <> const std::set<FactionName, std::less<FactionName>> HalfFactionNames<Half::Second>{
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
  FactionName::YssarilTribes
};

} // namespace

const std::set<FactionName, std::less<FactionName>>& half_faction_names(const Half half) noexcept {
  switch (half) {
    case Half::First:
      return HalfFactionNames<Half::First>;
      break;
    case Half::Second:
      return HalfFactionNames<Half::Second>;
      break;
  }
}

namespace {

const std::map<FactionName, std::size_t, std::less<FactionName>> FactionNamesAndColorIndices{
  {FactionName::Arborec, 0},
  {FactionName::ArgentFlight, 1},
  {FactionName::BaronyOfLetnev, 2},
  {FactionName::ClanOfSaar, 3},
  {FactionName::CouncilKeleres, 4},
  {FactionName::EmbersOfMuaat, 5},
  {FactionName::EmiratesOfHacan, 6},
  {FactionName::Empyrean, 7},
  {FactionName::FederationOfSol, 8},
  {FactionName::GhostsOfCreuss, 9},
  {FactionName::L1z1xMindnet, 10},
  {FactionName::MahactGeneSorcerers, 11},
  {FactionName::MentakCoalition, 12},
  {FactionName::NaaluCollective, 13},
  {FactionName::NaazRokhaAlliance, 14},
  {FactionName::NekroVirus, 15},
  {FactionName::Nomad, 16},
  {FactionName::SardakkNorr, 17},
  {FactionName::TitansOfUl, 18},
  {FactionName::UniversitiesOfJolNar, 19},
  {FactionName::VuilraithCabal, 20},
  {FactionName::Winnu, 21},
  {FactionName::XxchaKingdom, 22},
  {FactionName::YinBrotherhood, 23},
  {FactionName::YssarilTribes, 24}
};

} // namespace

Color color(const FactionName faction_name) noexcept {
  const std::map<FactionName, std::size_t, std::less<FactionName>>::const_iterator found{FactionNamesAndColorIndices.find(faction_name)};
  if (found != FactionNamesAndColorIndices.cend()) {
    return plot_data_color(found->second);
  } else {
    return plot_data_color(0);
  }
}

} // namespace TI4Echelon
