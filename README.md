[![build and test](https://github.com/acodcha/ti4-echelon/actions/workflows/build_and_test.yml/badge.svg?branch=main)](https://github.com/acodcha/ti4-echelon/actions/workflows/build_and_test.yml)

[Setup](#setup) · [Usage](#usage) · [Games File](#games-file) · [Factions](#factions) · [Documentation](#documentation) · [License](#license)

# Setup

The following packages are required:

- **C++17 Compiler:** Any C++17 compiler will do, such as GCC or Clang. On Ubuntu, install GCC with `sudo apt install g++` or Clang with `sudo apt install clang`.
- **CMake:** On Ubuntu, install with `sudo apt install cmake`.
- **Gnuplot:** On Ubuntu, install with `sudo apt install gnuplot`.

Build the program with:

```
mkdir build
cd build
cmake ..
make
```

This builds the `build/bin/ti4-echelon` program.

You can optionally run tests from the `build` directory with:

```
make test
```

You can optionally install the program from the `build` directory with:

```
sudo make install
```

This installs the program to `/usr/local/bin/ti4-echelon`. To uninstall the program, simply delete it.

[(Back to Top)](#)

# Usage

Run with no arguments or with the `--help` argument to obtain usage information.

Otherwise, for regular use, run with:

```
ti4-echelon --games <path> --leaderboard <path>
```

- `--games <path>` specifies the path to the games file to be read. Required.
- `--leaderboard <path>` specifies the path to the directory in which the leaderboard will be written. Optional. If omitted, no leaderboard is written.

[(Back to Top)](#)

# Games File

The games file is a plain text file with the following format:

```
2021-07-31 free-for-all 10
1st Alice 10 Winnu
2nd Bob 9 Xxcha Kingdom
3rd Carol 8 Clan of Saar
4th David 8 Universities of Jol-Nar
5th Erin 7 Empyrean
6th Frank 6 Argent Flight

2021-07-24 teams 14
1st Bob 15 Mentak Coalition
1st Alice 11 Titans of Ul
2nd Carol 13 Nomad
2nd Gabby 11 Mahact Gene-Sorcerers
3rd David 12 Yssaril Tribes
3rd Hugo 10 Arborec

etc.
```

- Games are separated by one or more blank lines.
- Each game consists of a header line followed by a number of result lines.
- The header line must contain a **date**, a **game mode**, and a **goal number of victory points**, in this order, each separated by whitespace.
- Each result line must contain a **place**, a **player name**, a **number of victory points**, and a **faction name**, in this order, each separated by whitespace.
- Dates must be in the YYYY-MM-DD format.
- The game mode must be one of either `free-for-all` or `teams`.
- Places are case-sensitive and must exactly match one of the following spellings: `1st`, `2nd`, `3rd`, `4th`, `5th`, `6th`, `7th`, `8th`.
- In free-for-all games, each player must have a unique place. Recall that initiative breaks ties in victory points, and additional victory points in excess of the game's goal number of victory points are worthless.
- When playing in teams, all players on the same team must have the same place; this is how teams are identified.
- Player names are case-sensitive and cannot contain any whitespace.

[(Back to Top)](#)

# Factions

The faction names in the games file are case-sensitive and must exactly match one of the following spellings:

- `Arborec`
- `Argent Flight`
- `Barony of Letnev`
- `Clan of Saar`
- `Embers of Muaat`
- `Emirates of Hacan`
- `Empyrean`
- `Federation of Sol`
- `Ghosts of Creuss`
- `L1z1x Mindnet`
- `Mahact Gene-Sorcerers`
- `Mentak Coalition`
- `Naalu Collective`
- `Naaz-Rokha Alliance`
- `Nekro Virus`
- `Nomad`
- `Sardakk N'orr`
- `Titans of Ul`
- `Universities of Jol-Nar`
- `Vuil'raith Cabal`
- `Winnu`
- `Xxcha Kingdom`
- `Yin Brotherhood`
- `Yssaril Tribes`
- `Custom`

Remarks:

- Note the numeral ones (`1`) in `L1z1x Mindnet`.
- Note the hyphen (`-`) in `Mahact Gene-Sorcerers`, `Naaz-Rokha Alliance`, and `Universities of Jol-Nar`.
- Note the apostrophe (`'`) in `Sardakk N'orr` and `Vuil'raith Cabal`.
- If playing a Frankendraft-style game with custom factions, use `Custom` as the faction name.

[(Back to Top)](#)

# Documentation

Building the documentation requires additional packages:

- **Doxygen:** On Ubuntu, install with `sudo apt install doxygen`.
- **Graphviz:** On Ubuntu, install with `sudo apt install graphviz`.
- **TeX Live:** On Ubuntu, install with `sudo apt install texlive texlive-fonts-extra`.

Documentation is optional and disabled by default but can be generated from the `build` directory with:

```
cmake .. -DBUILD_DOCS=ON
make docs
```

This generates HTML documentation using Doxygen. The documentation is located in `docs/html`. Open the `docs/html/index.html` file in any web browser to view the documentation.

[(Back to Top)](#)

# License

This work is maintained by Alexandre Coderre-Chabot (<https://github.com/acodcha>) and licensed under the MIT License. For more details, see the `LICENSE` file or <https://mit-license.org/>. This work is based on the Twilight Imperium 4th Edition board game by Fantasy Flight Games. The contents, copyrights, and trademarks of everything involving Twilight Imperium 4th Edition are exclusively held by Fantasy Flight Games; I make no claim to any of these in any way.

[(Back to Top)](#)
