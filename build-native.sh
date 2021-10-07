#!/bin/sh
mkdir -p build-native
#(cd build && cmake -DCMAKE_BUILD_TYPE=Debug ..)
(cd build-native && cmake ..)
(cd build-native && make VERBOSE=1 -j ${nprocs})
(build-native/test/cpp/cpptest)
