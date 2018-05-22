#!/bin/bash
CONFIG="-DSTRIP=10000 -DSTRIP_NOTIFY=50000 -DPOPULATION=5"
FILE=DSJC125.1.col
COLOR=5

cd build 
rm * -rf
CXXFLAGS=$CONFIG cmake .. || exit
cd .. 
make -C build || exit
./build/main data/${FILE} ${COLOR}    >> log/${FILE}-${COLOR}.log
./build/main data/${FILE} ${COLOR} 10 >> log/${FILE}-${COLOR}.log
./build/main data/${FILE} ${COLOR} 20 >> log/${FILE}-${COLOR}.log
./build/main data/${FILE} ${COLOR} 30 >> log/${FILE}-${COLOR}.log


CONFIG="-DSTRIP=10000 -DSTRIP_NOTIFY=50000 -DPOPULATION=5"
FILE=DSJC250.1.col
COLOR=8
cd build 
rm * -rf
CXXFLAGS=$CONFIG cmake .. || exit
cd .. 
make -C build || exit
./build/main data/${FILE} ${COLOR}    >> log/${FILE}-${COLOR}.log
./build/main data/${FILE} ${COLOR} 10 >> log/${FILE}-${COLOR}.log
./build/main data/${FILE} ${COLOR} 20 >> log/${FILE}-${COLOR}.log
./build/main data/${FILE} ${COLOR} 30 >> log/${FILE}-${COLOR}.log


