# btflasher

[![Build status](https://ci.appveyor.com/api/projects/status/bqwc27lokvekan5p/branch/master?svg=true)](https://ci.appveyor.com/project/ericyanush/btflasher/branch/master)
[![Build Status](https://travis-ci.org/ericyanush/btflasher.svg?branch=master)](https://travis-ci.org/ericyanush/btflasher)

btflasher is a native node.js addon that provides functionality to enable flashing BrewTroller boards from Javascript.

btflasher utilizes libavrdude, the same library used by avrdude to flash avr devices, along with [serial](https://github.com/wjwwood/serial) (a C++ serial port discovery / communitation library) to discover and identify BrewTroller boards connected to the host computer.

Notes:
btflasher uses a nearly unmodified copy of avrdude source code (currently version 6.3); the only modifications that have been made were to support compiling avrdude source natively on Windows, using the Visual C++ compiler, instead of having to rely on mingw. Supporting compilation using the Visual C++ compiler is necessary to be able to compile the node module for windows, as GCC (mingw) and Visual C++ do not produce binaries with compatible ABI.

To support compliation of libavrdude using the Visual C++ compiler, it was necessary to re-write the build system using a system compatible with native windows builds, as opposed to using autotools.

**Note:** The libavrdude binary produced for this project may or may not be 100% compatible with all programmers and features supported by the official avrdude binaries.

## Build Requirements

- CMake (v3.2+)
- Node.js 
- NPM
- Recent version of GCC or LLVM/Clang (macOS / Linux)
- Visual Studio C++ Build Tools (or Visual Studio) 2015
- Windows Driver Kit (WDK) (Windows only)

### Building

Running the command npm install from the root of the source directory will fetch the necessary node build dependancies, and kick off a build, using the node interpreter in your path.

To manually build, for a different node version (or for electron/node-webkit) use the cmake-js command: `.node_modules/cmake-js/bin/cmake-js rebuild`. Running this command requires that you have run `npm install` in the source root directory already. For more information on the arguments that cmake.js accepts see [here](https://github.com/cmake-js/cmake-js#installation). 

## Pre-built binaries
Due to the complexity of the build, and to support packaging node-webkit apps from a single build host, pre-built binary distributions are available from the release section. There are currently pre-built binaries available for Node 7.2.0 and node-webkit 0.20.0, for 64bit Windows, Mac and Linux. If you install btflasher using npm, targeting one of these systems, npm will automatically install the pre-built binary, if one is available. The binaries are automatically built using Travis (Linux and macOS) and Appveyor (Windows).
