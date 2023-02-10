#!/usr/bin/env bash
src="pagerank-levelwise-adjust-tolerance-analysis"
out="/home/resources/Documents/subhajit/$src.log"
ulimit -s unlimited
printf "" > "$out"

# Download program
rm -rf $src
git clone https://github.com/puzzlef/$src
cd $src

# Run
g++ -O3 main.cxx
stdbuf --output=L ./a.out ~/data/min-1DeadEnd.mtx      2>&1 | tee -a "$out"
stdbuf --output=L ./a.out ~/data/min-2SCC.mtx          2>&1 | tee -a "$out"
stdbuf --output=L ./a.out ~/data/min-4SCC.mtx          2>&1 | tee -a "$out"
stdbuf --output=L ./a.out ~/data/min-NvgraphEx.mtx     2>&1 | tee -a "$out"
