#pragma once

#include "Base.hpp"

namespace TI4Echelon {

enum class Faction : int8_t {
  Arborec,
  ArgentFlight,
  BaronyOfLetnev,
  ClanOfSaar,
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

template <> const std::map<Faction, std::string> labels<Faction>{
  {Faction::Arborec, "Arborec"},
  {Faction::ArgentFlight, "Argent Flight"},
  {Faction::BaronyOfLetnev, "Barony of Letnev"},
  {Faction::ClanOfSaar, "Clan of Saar"},
  {Faction::EmbersOfMuaat, "Embers of Muaat"},
  {Faction::EmiratesOfHacan, "Emirates of Hacan"},
  {Faction::Empyrean, "Empyrean"},
  {Faction::FederationOfSol, "Federation of Sol"},
  {Faction::GhostsOfCreuss, "Ghosts of Creuss"},
  {Faction::L1z1xMindnet, "L1z1x Mindnet"},
  {Faction::MahactGeneSorcerers, "Mahact Gene-Sorcerers"},
  {Faction::MentakCoalition, "Mentak Coalition"},
  {Faction::NaaluCollective, "Naalu Collective"},
  {Faction::NaazRokhaAlliance, "Naaz-Rokha Alliance"},
  {Faction::NekroVirus, "Nekro Virus"},
  {Faction::Nomad, "Nomad"},
  {Faction::SardakkNorr, "Sardakk N'orr"},
  {Faction::TitansOfUl, "Titans of Ul"},
  {Faction::UniversitiesOfJolNar, "Universities of Jol-Nar"},
  {Faction::VuilraithCabal, "Vuil'raith Cabal"},
  {Faction::Winnu, "Winnu"},
  {Faction::XxchaKingdom, "Xxcha Kingdom"},
  {Faction::YinBrotherhood, "Yin Brotherhood"},
  {Faction::YssarilTribes, "Yssaril Tribes"},
  {Faction::Custom, "Custom"}
};

template <> const std::map<std::string, Faction> spellings<Faction>{
  {"Arborec", Faction::Arborec},
  {"Argent Flight", Faction::ArgentFlight},
  {"Barony of Letnev", Faction::BaronyOfLetnev},
  {"Clan of Saar", Faction::ClanOfSaar},
  {"Embers of Muaat", Faction::EmbersOfMuaat},
  {"Emirates of Hacan", Faction::EmiratesOfHacan},
  {"Empyrean", Faction::Empyrean},
  {"Federation of Sol", Faction::FederationOfSol},
  {"Ghosts of Creuss", Faction::GhostsOfCreuss},
  {"L1z1x Mindnet", Faction::L1z1xMindnet},
  {"Mahact Gene-Sorcerers", Faction::MahactGeneSorcerers},
  {"Mentak Coalition", Faction::MentakCoalition},
  {"Naalu Collective", Faction::NaaluCollective},
  {"Naaz-Rokha Alliance", Faction::NaazRokhaAlliance},
  {"Nekro Virus", Faction::NekroVirus},
  {"Nomad", Faction::Nomad},
  {"Sardakk N'orr", Faction::SardakkNorr},
  {"Titans of Ul", Faction::TitansOfUl},
  {"Universities of Jol-Nar", Faction::UniversitiesOfJolNar},
  {"Vuil'raith Cabal", Faction::VuilraithCabal},
  {"Winnu", Faction::Winnu},
  {"Xxcha Kingdom", Faction::XxchaKingdom},
  {"Yin Brotherhood", Faction::YinBrotherhood},
  {"Yssaril Tribes", Faction::YssarilTribes},
  {"Custom", Faction::Custom}
};

} // namespace TI4Echelon
