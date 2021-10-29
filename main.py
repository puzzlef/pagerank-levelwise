# https://www.kaggle.com/wolfram77/puzzlef-pagerank-levelwise-adjust-tolerance-analys
import os
from IPython.display import FileLink
src="pagerank-levelwise-adjust-tolerance-analysis"
inp="/kaggle/input/graphs"
out="{}.txt".format(src)
!printf "" > "$out"
display(FileLink(out))
!echo ""

# Download program
!rm -rf $src
!git clone https://github.com/puzzlef/$src
!echo ""

# Run
!g++ -O3 $src/main.cxx
!ulimit -s unlimited && stdbuf --output=L ./a.out $inp/min-1DeadEnd.mtx      2>&1 | tee -a "$out"
!ulimit -s unlimited && stdbuf --output=L ./a.out $inp/min-2SCC.mtx          2>&1 | tee -a "$out"
!ulimit -s unlimited && stdbuf --output=L ./a.out $inp/min-4SCC.mtx          2>&1 | tee -a "$out"
!ulimit -s unlimited && stdbuf --output=L ./a.out $inp/min-NvgraphEx.mtx     2>&1 | tee -a "$out"
