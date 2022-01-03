#include "Instructions.hpp"
#include "Leaderboard.hpp"

int main(int argc, char *argv[]) {
  const TI4Echelon::Instructions instructions(argc, argv);
  const TI4Echelon::Games games{instructions.games_file()};
  const TI4Echelon::Players players{games};
  const TI4Echelon::Leaderboard leaderboard{instructions.leaderboard_directory(), games, players};
  TI4Echelon::message("End of " + TI4Echelon::Program::Title + ".");
  return EXIT_SUCCESS;
}
