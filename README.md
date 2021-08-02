# Twilight Imperium 4th Edition Leaderboard Generator
Generates a simple leaderboard for Twilight Imperium 4th Edition games.

**Contents:**
- [Dependencies](#dependencies)
- [Configuration and Build](#configuration-and-build)
- [Installation](#installation)
- [Documentation](#documentation)
- [Testing](#testing)
- [Usage](#usage)
  - [Games File](#usage-games-file)
  - [Factions](#usage-factions)
- [License](#license)
- [Maintainer](#maintainer)

## Dependencies
The following packages are required:
- **C++17 Compiler:** Any C++17 compiler will do, such as GCC or Clang. On Ubuntu, install GCC with `sudo apt install g++` or Clang with `sudo apt install clang`.
- **CMake:** On Ubuntu, install with `sudo apt install cmake`.
- **Gnuplot:** On Ubuntu, install with `sudo apt install gnuplot`.

[^ Back to Top](#twilight-imperium-4th-edition-leaderboard-generator)

## Configuration and Build
Configure and build the program with:

```
mkdir build
cd build
cmake ..
make
```

[^ Back to Top](#twilight-imperium-4th-edition-leaderboard-generator)

## Installation
Once you have configured and built the program, install it from the `build` directory with:

```
sudo make install
```

This installs the program to `/usr/local/bin/ti4_leaderboard_generator`. To uninstall the program, simply delete it.

[^ Back to Top](#twilight-imperium-4th-edition-leaderboard-generator)

## Documentation
Building the documentation is optional and requires additional packages:
- **Doxygen:** On Ubuntu, install with `sudo apt install doxygen`.
- **Graphviz:** On Ubuntu, install with `sudo apt install graphviz`.
- **TeX Live:** On Ubuntu, install with `sudo apt install texlive texlive-fonts-extra`.

Documentation is disabled by default but can be generated from the `build` directory with:

```
cmake .. -DBUILD_DOCS=ON
make docs
```

This generates HTML documentation using Doxygen. The documentation is located in `docs/html`. Open the `docs/html/index.html` file in any web browser to view the documentation.

[^ Back to Top](#twilight-imperium-4th-edition-leaderboard-generator)

## Testing
Once you have configured and built the program, run tests from the `build` directory with:

```
make test
```

[^ Back to Top](#twilight-imperium-4th-edition-leaderboard-generator)

## Usage
Run with no arguments or with the `--help` argument to obtain usage information.

Otherwise, for regular use, run with:

```
ti4_leaderboard_generator --games <path> --leaderboard <path>
```

- `--games <path>` specifies the path to the games file to be read. Required.
- `--leaderboard <path>` specifies the path to the directory in which the leaderboard will be written. Optional. If omitted, no leaderboard is written.

[^ Back to Top](#twilight-imperium-4th-edition-leaderboard-generator)

### Usage: Games File
The games file must have the following format:

```
2021-07-31
1st Alice 10 Winnu
2nd Bob 9 Xxcha Kingdom
3rd Carol 8 Clan of Saar
4th David 8 Universities of Jol-Nar
5th Erin 7 Empyrean
6th Frank 6 Argent Flight

2021-07-24
1st Bob 10 Mentak Coalition
2nd Alice 9 Titans of Ul
3rd Erin 9 Nomad
4th Carol 7 Mahact Gene-Sorcerers
5th David 6 Yssaril Tribes

etc.
```

- Games are separated by a blank line.
- Each game consists of a date and a list of places, player names, victory points, and faction names.
- Dates must be in the YYYY-MM-DD format.
- Player names are case-sensitive and cannot contain any whitespace.
- Each player must have a unique place. Note that initiative is used to break ties in number of victory points.
- Places are case-sensitive and must exactly match one of the following spellings: 1st, 2nd, 3rd, 4th, 5th, 6th, 7th, 8th.

[^ Back to Usage](#usage)

### Usage: Factions
Factions are case-sensitive and must exactly match one of the following spellings:

- Arborec
- Argent Flight
- Barony of Letnev
- Clan of Saar
- Embers of Muaat
- Emirates of Hacan
- Empyrean
- Federation of Sol
- Ghosts of Creuss
- L1z1x Mindnet
- Mahact Gene-Sorcerers
- Mentak Coalition
- Naalu Collective
- Naaz-Rokha Alliance
- Nekro Virus
- Nomad
- Sardakk N'orr
- Titans of Ul
- Universities of Jol-Nar
- Vuil'raith Cabal
- Winnu
- Xxcha Kingdom
- Yin Brotherhood
- Yssaril Tribes
- Custom

Remarks:
- Note the numeral one (1) characters in L1z1x Mindnet.
- Note the hyphen (-) in Mahact Gene-Sorcerers, Naaz-Rokha Alliance, and Universities of Jol-Nar.
- Note the apostrophe (') in Sardakk N'orr and Vuil'raith Cabal.
- If playing a Frankendraft-type game with custom factions, use "Custom" as the faction name.

[^ Back to Usage](#usage)

## License
This work is licensed under the MIT License. For more details, see the [LICENSE](LICENSE) file or <https://mit-license.org/>.

[^ Back to Top](#twilight-imperium-4th-edition-leaderboard-generator)

## Maintainer
- Alexandre Coderre-Chabot (<https://github.com/acodcha>)

[^ Back to Top](#twilight-imperium-4th-edition-leaderboard-generator)

