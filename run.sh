cd build 
rm * -rf
CXXFLAGS="-DSTRIP=10 -DSTRIP_NOTIFY=20 -DPOPULATION=2" cmake .. || exit
cd .. 
make -C build || exit
./build/main data/DSJC125.1.col 5  >> log/125.1.log
./build/main data/DSJC125.1.col 5 1 >> log/125.1.log
./build/main data/DSJC125.1.col 5 2 >> log/125.1.log
./build/main data/DSJC125.1.col 5 3 >> log/125.1.log

./build/main data/DSJC125.1.col 5  >> log/125.1.log
