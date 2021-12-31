#include "Games.hpp"
#include "Instructions.hpp"

int main(int argc, char *argv[]) {
  const TI4Echelon::Instructions instructions(argc, argv);
  const TI4Echelon::Games games{instructions.games_file()};
  TI4Echelon::message("End of " + TI4Echelon::Program::Title + ".");
  return EXIT_SUCCESS;
}
