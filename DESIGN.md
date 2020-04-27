# CharLS-JS Design

The [original JS build of CharLS](https://github.com/cornerstonejs/charls) 
was done in 2016 specifically to add JPEG-LS decoding to
[cornerstonejs](https://github.com/cornerstonejs).  Unfortunately nobody
picked up maintainence for the original project so it fell behind
a major version release of CharLS and the addition of WASM to
browsers and NodeJS.  

To avoid the library falling behind again, I thought it would be good
to [merge it into the main CharLS library](https://github.com/team-charls/charls/issues/13).
After quite a bit of research and experimentation, I decided it would be better
to keep the JS/WASM code separate from the main CharLS library but improve the way
the JS/WASM project was setup.  Part of my research lead me to discover
[Modern CMake](https://cliutils.gitlab.io/modern-cmake/) which lead
to an prototype of how it would work with EMSCRIPTEN 
[here](https://github.com/chafey/modern-cpp-lib-js).

## Git Submodules

The main charls is referenced as a git submodule.  This strategy ensures
that JS/WASM code does not creep into the main charls library so it can
remain pure C/C++ code.  This strategy also simplifies maintenance since the
charls submodule tracks the master branch and can be easily updated to
new versions via 

``` bash
git pull --recurse-submodules
git submodule update --remote
```

## EMBIND

The original JS build of CharLS required quite a bit of JavaScript glue
code to use.  This glue code was messy and not packaged with the actual build
itself making it difficult to use.  I discovered [EMBIND](https://emscripten.org/docs/porting/connecting_cpp_and_javascript/embind.html)
which solves this problem by allow you to write the JavaScript bridge code
in C++ and expose it via EMBIND.  I used this to create wrapper classes that
handle the encoding, decoding, memory management and access to other properties
such as the nearLossless parameter and interleaveMode.