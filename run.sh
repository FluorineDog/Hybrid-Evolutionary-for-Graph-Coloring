#!/bin/bash
CONFIG="-DSTRIDE=10000 -DSTRIDE_NOTIFY=20000 -DSCALE=1 -DPOPULATION=5"
FILE=DSJC125.1.col
COLOR=6

cd build 
rm * -rf
CXXFLAGS=$CONFIG cmake .. || exit
cd .. 
make -C build || exit
./build/main data/${FILE} ${COLOR}    >> log/${FILE}-${COLOR}.log
./build/main data/${FILE} ${COLOR} 10 >> log/${FILE}-${COLOR}.log
./build/main data/${FILE} ${COLOR} 20 >> log/${FILE}-${COLOR}.log
./build/main data/${FILE} ${COLOR} 30 >> log/${FILE}-${COLOR}.log


# comment "exit" to add second pass
exit

CONFIG="-DSTRIDE=10000 -DSTRIDE_NOTIFY=50000 -DPOPULATION=5"
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

