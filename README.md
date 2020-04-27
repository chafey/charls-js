# charls-js
JS/WASM build of CharLS

## Try It Out!

Try it in your browser [here](https://chafey.github.com/charls-js/test/browser/index.html)

## Usage

See example usage for web in test/browser and node.js in test/node

## Dependencies

* CMake 3.17 or better
* A C++ compatible compiler
* Emscripten SDK 1.39.4 or better
* NodeJS 8.0 or later

## Visual Studio Code Remote Containers Support

This project includes support for developing in a docker container using the 
Visual Studio Code Remote - Containers extension.  The configured docker container
includes emscripten, cmake and gcc so you can build, debug and run this project
immediately without having to deal with toolchain dependencies. The default build task
(shift+control+b) is to configure, build and run the tests

NOTE: If you don't use VS Code but want to use Docker, you can try using the 
Dockerfile in the .devcontainer folder.

## building WASM (requires EMSCRIPTEN)

```bash
build.sh
```

After building, you can run the browser based test by running an http server
at the root of this project and opening the file test/browser/index.html  I use 
[HTTP Server / HTML Preview](https://marketplace.visualstudio.com/items?itemName=Flixs.vs-code-http-server-and-html-preview)

## building native C++

```bash
build-native.sh
```