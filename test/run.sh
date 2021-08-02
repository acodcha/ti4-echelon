#!/bin/sh
set -e
cd "${0%/*}"
./clear.sh
../build/bin/ti4_leaderboard_generator --games games.txt --leaderboard leaderboard

