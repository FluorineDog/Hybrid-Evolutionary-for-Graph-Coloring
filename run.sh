#!/bin/bash
CONFIG="-DSTRIP=10000 -DSTRIP_NOTIFY=20000 -DSCALE=1 -DPOPULATION=5"
FILE=DSJC500.5.col
COLOR=48

cd build 
rm * -rf
CXXFLAGS=$CONFIG cmake .. || exit
cd .. 
make -C build || exit
./build/main data/${FILE} ${COLOR}    >> log/${FILE}-${COLOR}.log
./build/main data/${FILE} ${COLOR} 10 >> log/${FILE}-${COLOR}.log
./build/main data/${FILE} ${COLOR} 20 >> log/${FILE}-${COLOR}.log
./build/main data/${FILE} ${COLOR} 30 >> log/${FILE}-${COLOR}.log
exit

CONFIG="-DSTRIP=10000 -DSTRIP_NOTIFY=50000 -DPOPULATION=5"
FILE=DSJC250.9.col
COLOR=72
cd build 
rm * -rf
CXXFLAGS=$CONFIG cmake .. || exit
cd .. 
make -C build || exit
./build/main data/${FILE} ${COLOR}    >> log/${FILE}-${COLOR}.log
./build/main data/${FILE} ${COLOR} 10 >> log/${FILE}-${COLOR}.log
./build/main data/${FILE} ${COLOR} 20 >> log/${FILE}-${COLOR}.log
./build/main data/${FILE} ${COLOR} 30 >> log/${FILE}-${COLOR}.log


