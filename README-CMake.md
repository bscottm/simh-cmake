# SIMH Build via CMake, v4.0 - CURRENT

<!-- TOC -->autoauto- [SIMH Build via CMake, v4.0 - CURRENT](#simh-build-via-cmake-v40---current)auto    - [Introduction](#introduction)auto    - [Prerequisites](#prerequisites)auto    - [Quick Start](#quick-start)auto    - [The Handcrafted Way](#the-handcrafted-way)autoauto<!-- /TOC -->

## Introduction

CMake is a meta-build system, that is, a build system generator for other software development systems and integrated development environments (IDEs). This gives you a lot of choice with respect to your choice of IDE and build system, such as:

  * Visual Studio 2019 ("Visual Studio 16 2019")
  * Visual Studio 2017 ("Visual Studio 15 2017")
  * MinGW Makefiles
  * Ninja build files
  * GNU Makefiles

The CMake build solution is not intended to replace the existing SIMH `makefile` (aka "cheap man's configure") or existing Visual Studio solution and project files. CMake is just another approach to building and developing the SIMH simulators. The fact that it can generate all of the Visual Studio solutions or operates with the SublimeText(tm) IDE build system is merely z happy coincidence.

## Prerequisites

You need the following installed on your system:

  * A C compiler (GCC, MSVC, etc.)
  * CMake version 3.14 or higher

On Windows(tm), you will also need the `windows-build` repository, side-by-side with the `sim-master` repository:

    simh
    |- window-build
    |  |- build-stage
    |  |- ...
    |
    |- sim-master
    |  |- VAX
    |  |- PDP8
    |  |- ...

## Quick Start

1. (Windows) Execute the `cmake-generator.ps1` Powershell script:

````
    PS> .\cmake-generator -tool:vs2019 -clean
````

2. (*nix) Execute the `cmake-generator.sh` shell script:

````
    $ ./cmake-generatir.sh --tool=gnu --clean
````

Both scripts create a `cmake-build` subdirectory and run `cmake` to generate the build system's files. For example, `vs2019` will generate VS2019 solution and project files for 32-bit Debug and Release configurations. Other tools:

  * `-tool:ninja`/`--tool=ninja`: Generate [Ninja][1] build system files.
  * `-tool:mingw`: Generate [MinGW][2] makefiles

The `clean` flag tells the generator script to remove the `cmake-build` directory before generating build system artifacts.

[1]: http://ninja-build.org
[2]: https://mingw-w64.org/

## The Handcrafted Way

1. Create a directory in which you will build the simulators. _Note_: The CMake build system __will not__ let you do an "in-tree" build.

````
    sim-master$ mkdir cmake-build
    sim-master$ cd cmake-build
    cmake-build$ _
````

2. Generate your build system.

````
    cmake-build$ cmake -G "Visual Studio 16 2019" -Awin32 ..
````

3a. Use your IDE. For MSVC users, the solution is named `simh.sln`. Subdirectories (`VAX`, `PDP11`, `PDP8`, ...) have the indivudal simulator projects.

3b. Build the simulators on the command line:

````
    cmake-build$ cmake --build . --config Release
````

If you're a MSVC user, the `cmake --build` is your preferred way of building from the command line. You can still use `msbuild` to build the `simh.sln` solution and the individual `.vcxproj` projects, but only if you're a glutton for punishment.