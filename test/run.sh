#!/bin/sh
set -e
cd "${0%/*}"
./clear.sh
../build/bin/ti4-echelon --games games.txt --leaderboard leaderboard
