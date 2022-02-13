#!/bin/sh
mkdir -p build
#(cd build && emconfigure cmake -DCMAKE_BUILD_TYPE=Debug ..)

(cd build && emcmake cmake -DBUILD_WEB=OFF ..)
(cd build && emmake make VERBOSE=1 -j ${nprocs})
cp ./build/src/charlsjs.js ./dist
cp ./build/src/charlsjs.wasm ./dist

(cd build && emcmake cmake -DBUILD_WEB=ON ..)
(cd build && emmake make VERBOSE=1 -j ${nprocs})
cp ./build/src/charlsjs.js ./dist/charlsjs.web.js

(cd test/node; npm run test)
