#include "Players.hpp"
#include "Instructions.hpp"

int main(int argc, char *argv[]) {
  const TI4Echelon::Instructions instructions(argc, argv);
  const TI4Echelon::Games games{instructions.games_file()};
  const TI4Echelon::Players players{games};
  TI4Echelon::message("End of " + TI4Echelon::Program::Title + ".");
  return EXIT_SUCCESS;
}
