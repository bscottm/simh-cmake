# Build `simh` using CMake

<!-- TOC -->

- [Why CMake?](#why-cmake)
- [Quickstart For The Impatient](#quickstart-for-the-impatient)
  - [Linux/WSL](#linuxwsl)
  - [Windows](#windows)
- [Details](#details)
  - [Tools and Runtime Library Dependencies](#tools-and-runtime-library-dependencies)
  - [CMake Configuration Options](#cmake-configuration-options)
  - [Directory Structure/Layout](#directory-structurelayout)
  - [Regenerating the `CMakeLists.txt` Files](#regenerating-the-cmakeliststxt-files)
  - [Step-by-Step](#step-by-step)
    - [Linux/*nix platforms](#linuxnix-platforms)
- [Motivation](#motivation)

<!-- /TOC -->


## Why CMake?

[CMake][cmake] is a cross-platform "meta" build system that provides similar functionality to
GNU _autotools_ within a more integrated and platform-agnostic framework. Two of the motivating
factors for providing a [CMake][cmake]-based alternative build system were library dependency
management (i.e., SDL2, SDL2_ttf, et. al.) and support for other build tools. A sample of
[CMake][cmake]'s supported build tools/environments includes:

  - Unix (GNU) Makefiles
  - [MinGW Makefiles][mingw64]
  - [Ninja][ninja] build tool
  - MS Visual Studio solutions (2015, 2017, 2019)
  - IDE build wrappers, such as [Sublime Text](https://www.sublimetext.com)
    and [CodeBlocks](http://www.codeblocks.org)

[CMake][cmake] (aka `simh-cmake`) is not intended to supplant, supercede or replace the
existing `simh` build infrastructure. If you like the existing `makefile` "poor man's
configure" approach, there's nothing to stop you from using it. [CMake][cmake] is a parallel
build system to the `simh` `makefile` and is just another way to build `simh`'s simulators. If
you look under the hood, you'll find a Python script that generates [CMake][cmake]'s
`CMakeLists.txt` files automagically from the `simh` `makefile`.


## Quickstart For The Impatient

The quickstart consists of:

  - Clone the `simh` repository, if you haven't done that already
  - Install runtime dependency development libraries (Linux)
  - Run the appropriate `cmake-builder` script for your platform

There are two scripts, `cmake/cmake-builder.ps1` (Windows PowerShell) and
`cmake/cmake-builder.sh` (_bash_), that automate the entire `simh-cmake` build sequence. This
sequence consists of four phases: _configure/generate_, _build_, _test_ and _install_. If the
build succeeds (and you see a lot of `-- Installing ` lines at the end of the output), you
should have a complete set of simulators under the top-level `simh/BIN` subdirectory.

On Windows (and potentially on Linux if you haven't installed the dependency development
libraries), `simh-cmake` will download, compile and locally install the runtime dependencies.
There is no support (yet) for Microsoft's [vcpkg][vcpkg]; it is planned at a future date. The
runtime dependency library build, followed by the simulator build, is called a [CMake][cmake]
"superbuild". The superbuild should only execute once; `simh-cmake` will regenerate the build
tool's files once the runtime dependency libraries are successfully detected and found.

### Linux/WSL

The quickstart shell steps below were tested on Ubuntu 18, both natively and under Windows
Services for Linux (WSL). Package names, such as `libsdl2-ttf`, may vary between Linux
distributions. For other ideas or to see how SIMH is built on [Gitlab][gitlab], refer to the
`.gitlab-ci.yml` configuration file.

The default [CMake][cmake] generator is "Unix Makefiles", i.e., [CMake][cmake] generates
everything for GNU `make`. [Ninja][ninja] is an alternate supported builder, which can be used
by passing the `--flavor=ninja` option to the `cmake/cmake-builder.sh` script.

```shell
## clone the SIMH repository (skip if you did this already)
$ git clone  https://github.com/simh/simh.git simh
$ cd simh

## Install development dependency libraries (skip if these are)
## already installed. It doesn't hurt to make sure that they are
## installed.)
$ sudo apt-get update -qq -y && \
  sudo apt-get install -qq -y cmake libpcre2-8-0 libpcre2-dev libsdl2-ttf-dev zlib1g-dev && \
  sudo apt-get install -qq -y libpcap-dev libvdeplug-dev

## Install the Ninja builder if desired, otherwise, skip this step.
$ sudo apt-get install -qq -y ninja-build

## Invoke the automation script for Unix Makefiles. Lots of output ensues.
$ cmake/cmake-builder.sh

## For Ninja (lighter weight and highly parallel compared to GNU make):
$ cmake/cmake-builder.sh --flavor=ninja

## Help from the script:
$ cmake/cmake-builder.sh --help
Configure and build simh simulators on Linux and *nix-like platforms.

Subdirectories:
cmake/build-unix:  Makefile-based build simulators
cmake/build-ninja: Ninja build-based simulators

Options:
--------
--clean (-x)      Remove the build subdirectory
--generate (-g)   Generate the build environment, don't compile/build
--parallel (-p)   Enable build parallelism (parallel builds)
--nonetwork       Build simulators without network support
--notest          Do not execute 'ctest' test cases
--noinstall       Do not install SIMH simulators.
--testonly        Do not build, execute the 'ctest' test cases
--installonly     Do not build, install the SIMH simulators
--allInOne        Use 'all-in-one' project structure (vs. individual)

--flavor (-f)     Specifies the build flavor: 'unix' or 'ninja'
--config (-c)     Specifies the build configuraiton: 'Release' or 'Debug'

--help (-h)       Print this help.
```


### Windows

These quickstart steps were tested using Visual Studio 2019 and using [MinGW][mingw64]/GCC. These
have not been tested with the [CLang][clang] compiler.

Building on Windows is slightly more complicated than building on Linux because development
package management is not as well standardized as compared to Linux distributions. The
following quickstart steps use the [Scoop][scoop] package manager to install required
development tools.

Runtime dependencies, such as `SDL2`, `PNG`, `zlib`, are automagically handled by the
`simh-cmake` build process, also known as "the superbuild." The superbuild should only occur
once to compile and locally install the runtime dependency libraries, header files and DLLs.
Once the runtime dependency libraries are installed, the superbuild regenerates the build
environment to use the locally installed dependencies.

To make things even more complicated, there are a variety of [CMake][cmake] genenerators,
depending on which compiler you have installed and whether you are using [MinGW][mingw64] or
Visual Studio. If you are using [MinGW][mingw64], __do not use `pkg-config` to install `SDL2`
and `SDL2-ttf`__ -- let `simh-cmake` compile and locally install those two dependencies. There
is an active ticket with Kitware to resolve this issue.

__Emulated Ethernet via Packet Capture (PCAP):__ If you want emulated Ethernet support in
Windows-based simulators, you __have__ to install the [NPCAP][npcap] package.

```shell
# If you have Visual Studio installed, skip the following two development
# tool installation steps.
#
# Install development tools using Scoop (Chocolatey is another option, package
# names are different, YMMV).
PS> scoop install 7zip cmake gcc winflexbison git msys2
# If you want/need the Ninja build system (an alternative to mingw32-make):
PS> scoop install ninja

# Clone the SIMH repository, if needed.
PS> git clone  https://github.com/simh/simh.git simh
PS> cd simh

# Choose one of the following build steps, depending on which development
# environment you use/installed:

# Visual Studio 2019 build, Release configuration. Simulators and runtime
# dependencies will install into the simh/BIN/Win32/Release directory.
PS> cmake\cmake-builder.ps1 -flavor vs2019

# MinGW/GCC build, Release build type. Simulators and runtime
# dependencies will install into the simh/BIN directory.
PS> cmake\cmake-builder.ps1 -flavor mingw

# Ninja/GCC build, Release build type. Simulators and runtime
# dependencies will install into the simh/BIN directory.
PS> cmake\cmake-builder.ps1 -flavor ninja

## Help output from the script:
PS> cmake\cmake-builder.ps1 -help
Configure and build simh's dependencies and simulators using the Microsoft
Visual Studio C compiler or MinGW-W64-based gcc compiler.

cmake/build-vs* subdirectories: MSVC build products and artifacts
cmake/build-mingw subdirectory: MinGW-W64 products and artifacts
cmake/build-ninja subdirectory: Ninja builder products and artifacts

Arguments:
-clean                 Remove and recreate the build subdirectory before
                       configuring and building
-generate              Generate build environment, do not compile/build.
                       (Useful for generating MSVC solutions, then compile/-
                       build within the Visual Studio IDE.)
-parallel              Enable build parallelism (parallel target builds)
-nonetwork             Build simulators without network support.
-notest                Do not run 'ctest' test cases.
-noinstall             Do not install simulator executables
-installOnly           Only execute the simulator executable installation
                       phase.
-allInOne              Use the simh_makefile.cmake "all-in-one" project
                       configuration vs. individual CMakeList.txt projects.
                       (default: off)

-flavor (2019|vs2019)  Generate build environment for Visual Studio 2019 (default)
-flavor (2017|vs2017)  Generate build environment for Visual Studio 2017
-flavor (2015|vs2015)  Generate build environment for Visual Studio 2015
-flavor (2013|vs2013)  Generate build environment for Visual Studio 2013
-flavor (2012|vs2012)  Generate build environment for Visual Studio 2012
-flavor mingw          Generate build environment for MinGW GCC/mingw32-make
-flavor ninja          Generate build environment for MinGW GCC/ninja

-config Release        Build dependencies and simulators for Release (optimized) (default)
-config Debug          Build dependencies and simulators for Debug

-help                  Output this help.
```

### Running Simulators

Assuming that the `cmake-builder.ps1` or `cmake-builder.sh` script successfully completed and installed
the simulators, running a simulator is very straightforward:

```shell
## Linux and MinGW/GCC (anyone except VS...)
$ BIN/vax

MicroVAX 3900 simulator V4.0-0 Current        git commit id: ad9fce56
sim>

## Visual Studio:
PS> BIN\Win32\Release\vax

MicroVAX 3900 simulator V4.0-0 Current        git commit id: ad9fce56
sim>
```


## Details

### Tools and Runtime Library Dependencies

The table below lists the development tools and packages needed to build the
`simh` simulators, with corresponding `apt`, `rpm` and `Scoop` package names,
where available. Blank names indicate that the package is not offered via the
respective package manager.

| Prerequisite             | Category   | `apt` package   | `rpm` package  | [Scoop][scoop] package | Notes  |
| ------------------------ | ---------- | --------------- | -------------- | ---------------------- | :----: |
| [CMake][cmake]           | Dev. tool  | cmake           | cmake          | cmake                  | (1)    |
| [Git][gitscm]            | Dev. tool  | git             | git            | git                    | (1, 2) |
| [bison][bison]           | Dev. tool  | bison           | bison          | winflexbison           | (2, 3) |
| [flex][flex]             | Dev. tool  | flex            | flex           | winflexbison           | (2, 3) |
| [Npcap][npcap]           | Runtime    |                 |                |                        | (4)    |
| [zlib][zlib]             | Dependency | zlib1g-dev      | zlib-devel     |                        | (5)    |
| [pcre2][pcre2]           | Dependency | libpcre2-dev    | pcre2-devel    |                        | (5)    |
| [libpng][libpng]         | Dependency | libpng-dev      | libpng-devel   |                        | (5)    |
| [FreeType][FreeType]     | Dependency | libfreetype-dev | freetype-devel |                        | (5)    |
| [libpcap][libpcap]       | Dependency | libpcap-dev     | libpcap-devel  |                        | (5)    |
| [SDL2][SDL2]             | Dependency | libsdl2-dev     | SDL2-devel     |                        | (5)    |
| [SDL_ttf][SDL2_ttf]      | Dependency | libsdl2-ttf-dev |                |                        | (5)    |
| [pthreads4w][pthreads4w] | Dependency |                 |                |                        | (6)    |

_Notes_:

(1) Required development tool.

(2) Tool might already be installed on your system.

(3) Tool might already be installed in Linux and *nix systems; [winflexbison][winflexbison] is
    package that installs both the [bison][bison] and [flex][flex] tools for Windows developers.
    [bison][bison] and [flex][flex] are _only_ required to compile the [libpcap][libpcap] packet
    capture library. If you do not need emulated native Ethernet networking, [bison][bison] and
    [flex][flex] are optional.

(4) [Npcap][npcap] is a Windows packet capture device driver. It is a runtime requirement used
    by simulators that emulate native Ethernet networking on Windows.

(5) If the package name is blank or you do not have the package installed, `simh-cmake` will
    download and compile the library dependency from source. [Scoop][scoop] does not provide these
    development library dependencies, so all dependencies will be built from source on Windows.
    Similarly, `SDL_ttf` support may not be available for RPM package-based systems (RedHat,
    CentOS, ArchLinux, ...), but will be compiled from source.

(6) [pthreads4w][pthreads4w] provides the POSIX `pthreads` API using a native Windows
    implementation. This dependency is built only when using the _Visual Studio_ compiler.
    [Mingw-w64][mingw64] provides a `pthreads` library as a part of the `gcc` compiler toolchain.

### CMake Configuration Options

The default `simh-cmake` configuration is _"Batteries Included"_: all options are enabled as
noted below. They generally mirror those in the `makefile`:

* `WITH_NETWORK`: Enable (=1)/disable (=0) simulator networking support. (def: enabled)
* `WITH_PCAP`: Enable (=1)/disable (=0) libpcap (packet capture) support. (def: enabled)
* `WITH_SLIRP`: Enable (=1)/disable (=0) SLIRP network support. (def: enabled)
* `WITH_VDE`: Enable (=1)/disable (=0) VDE2/VDE4 network support. (def: enabled, Linux only)
* `WITH_TAP`: Enable (=1)/disable (=0) TAP/TUN device network support. (def: enabled, Linux only)
* `WITH_VIDEO`: Enable (=1)/disable (=0) simulator display and graphics support (def: enabled)
* `PANDA_LIGHTS`: Enable (=1)/disable (=0) KA-10/KI-11 simulator's Panda display. (def: disabled)
* `DONT_USE_ROMS`: Enable (=1)/disable (=0) building hardcoded support ROMs. (def: disabled)
* `ENABLE_CPPCHECK`: Enable (=1)/disable (=0) [cppcheck][cppcheck] static code checking rules.
* `ALL_IN_ONE`: Use the 'all-in-one' project definitions (vs. individual CMakeLists.txt) (def: disabled)

__ALL_IN_ONE project definitions__: This option is discouraged, and should never be used by
Visual Studio developers. The "all-in-one" project definitions are a variation on how
`simh-cmake` configures the individual simulators. For Visual Studio developers and IDE
enthusiasts for whom individual simulator projects are important, this option will make all
simulator suprojects disappear and likely make your IDE unusable or unsuitable to compile SIMH.
If your normal development environment is Emacs or Vi/ViM, IDE subprojects aren't important and
this option is available to you. It doesn't improve compile or build times.


### Directory Structure/Layout

`simh-cmake` is relatively self-contained within the `cmake` subdirectory. The exceptions are
the `simh` top-level directory `CMakeLists.txt` file and the individual simulator
`CMakeLists.txt` files. The individual simulator `CMakeLists.txt` files are automagically
generated from the `simh` `makefile` by the `cmake/generate.py` script -- see [this
section](#regenerating-the-cmakeliststxt-files) for more information.

The directory structure and layout is:

```
simh
| - CMakeLists.txt         ## Top-level, "master" project defs for SIMH and
|                          ## simulators
|
+ 3b2                      ## 3b2 simulator
| - CMakeLists.txt         ## Individual subproject CMake defs for 3b2
| - ...                    ## 3b2 sources
+ ALTAIR                   ## Altair simulator
| - CMakeLists.txt         ## Individual subproject CMake defs for Altair
| - ...                    ## Altair sources
+ AltairZ80
| - CMakeLists.txt         ## Individual subproject CMake defs for AltairZ80
| - ...                    ## AltairZ80 sources
+ BIN                      ## SIMH's preferred installation location
| + Win32/Release          ## Visual Studio Release configuration installation loc.
| + Win32/Debug            ## Visual Studio Debug configuration installation loc.
...
+ cmake
| + build-vs2019           ## Subdirectory for VS 2019 build artifacts
| + build-mingw            ## Subdirectory for MinGW build artifacts
| + build-ninja            ## Subdirectory for Ninja build artifacts
| + build-unix             ## Subdirectory for GNU make build artifacts
| + dependencies           ## Local installation subdirectory hierarchy for
|                          ## runtime dependencies
| - *.cmake                ## CMake packages and modules
| - generate.py            ## CMakeLists.txt generator script
```

Git will ignore all of the `cmake/build-*` and `cmake/dependencies` subdirectories. These
subdirectories encapsulate all of the build artifacts and products associated with a particular
compiler/build environment. It is actually safe to delete these subdirectories if you want to
start over from scratch. Moreover, you can also develop and target multiple compilers, since
their [CMake][cmake] outputs are compartmentalized.

### Regenerating the `CMakeLists.txt` Files

`simh-cmake` is a parallel build system to the `makefile`. The `makefile` is the authoritative
source for simulators that can be built (the `all :` rule) as well as how those simulators
compile and options needed to compile them. Consequently, the individual simulator
`CMakeLists.txt` project definitions are automagically generated from the `makefile` using the
`cmake/generate.py` Python3 script.

__Simulator developers:__ If you add a new simulator to SIMH or change a simulator's source
file list, compile options, etc., you will have to regenerate the `CMakeLists.txt` files. It's
relatively painless and Git will detect which have changed to minimize the amount of repository
churn:

```
$ cd cmake
$ python3 -m generate
```

That's it. Basically, if you change `makefile`, regenerate.

There is nothing that prevent you from manually editing a `CMakeLists.txt` file while doing
development (see the individual `CMakeLists.txt` files and `cmake/add_simulator.cmake` for
information on how to define your own simulator, as well as available options.) Just keep in
mind that the `makefile` is authoritative and all of your changes will be wiped out by the next
`CMakeList.txt` regeneration.

### Step-by-Step

It is basically up to you to choose the build system with which you're most comfortable and probably already use. [CMake][cmake] generates the files and
environment for your preferred build system from the `CMakeFiles.txt` configuration file. [CMake Generators](#cmake-generators) has more information
about which build systems your [CMake][cmake] installation supports.

The process to build `simh` with [CMake][cmake] follows the steps below:

1. Clone the `simh` Git repository, if you haven't done so already.
2. Create a subdirectory in which you will build the simulators.
 
    _Note_: This [CMake][cmake] configuration **will not allow you** to configure, build or compile `simh` in the source
    tree. Building `simh` simulators with [CMake][cmake] ***must*** be done in a separate directory, which is usually a
    subdirectory within the source tree. An informal convention for subdirectory names is `cmake-<something>`, e.g.,
    `cmake-unix` for Unix Makefile builds and `cmake-ninja` for [Ninja][ninja]-based builds (`.gitignore` ignores all
    subdirectories that start with `cmake-`.)

3. Compile the dependencies
  - Detect which dependencies need to be built
  - Generate the build environment to build the dependencies (if any)
  - Build dependencies (if any)
4. Compile the simulators
  - Configure and generate the build environment for the simulators
  - Build the simulators

#### Linux/*nix platforms

The following shell 

``` shell
# Install Ubuntu/Linux dependencies
$ sudo apt install cmake bison flex zlib1g-dev libpcre2-dev libpng-dev libpcap-dev libsdl2-dev libsdl2-ttf-dev

# Clone the simh repository (if you haven't done so already)
$ git clone  https://github.com/simh/simh.git simh
$ cd simh

# make a build directory and generate Unix Makefiles
$ mkdir cmake-unix
$ cd cmake-unix
$ cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release ..

# First time around, d/l and build dependency libraries, if they're
# not found (usually the case on Windows, YMMV on *nix):
$ cmake --build . --config Release

# Second time around: Reconfigure using the newly built dependency libraries
# and build simh's simulators
$ cmake -G Ninja -DCMAKE_BUILD_TYPE=Release ..
$ cmake --build . --config Release

# Alternatively, you can go into your favorite IDE and build from within your
# IDE. Or, with the Ninja build system, you could just type `ninja` instead of
# `cmake --build . --configure Release`. Or if you used "Unix Makefiles", you
# could just type `make`. (See the pattern yet?)

# Oh, so you want to run stuff? From inside the build?
# Need to add the build-stage/bin directory to your PATH:
$ PATH=`pwd`/build-stage/bin:$PATH

# For Windows Powershell:
# $env:PATH="$(Get-Location)\build-stage\bin;C:\Windows\System32\Npcap;$env:PATH"

# Run the vax simulator from inside the build:
$ VAX/vax

# Install will install to the `BIN` directory inside the source tree:
$ cmake --install .
```

[CMake][cmake] enables (or disables) options at configuration time:

```shell
# Assuming that you are in the cmake-ninja build subdirectory already.
# Remove the CMakeCache.txt file if you are reconfiguring your build system:
$ rm -f CMakeCache.txt

# Then reconfigure:
$ cmake -G Ninja -DCMAKE_BUILD_TYPE=Release -DWITH_NETWORK=Off -DENABLE_CPPCHECK=Off

# Alteratively ("0" and "Off" are equivalent)
$ cmake -G Ninja -DCMAKE_BUILD_TYPE=Release -DWITH_NETWORK=0 -DENABLE_CPPCHECK=0
```

## Motivation

**Note**: This is personal opinion. There are many personal opinions like this,
but this one is mine. (With apologies to the USMC "Rifle Creed.")

`simh` is a difficult package to build from scratch, especially if you're on a Windows
platform. There's a separate directory tree you have to check out that has to sit parallel to
the main `simh` codebase (aka `sim-master`.) It's an approach that I've used in the past and
it's hard to maintain (viz. a recent commit log entry that says that `git` forks should _not_
fork the `windows-build` subdirectory.) That's not a particularly clean or intuitive way of
building software. It's also prone to errors and doesn't lend itself to upgrading dependency
libraries.

[cmake]: https://cmake.org
[cppcheck]: http://cppcheck.sourceforge.net/
[ninja]: https://ninja-build.org/
[scoop]: https://scoop.sh/
[gitscm]: https://git-scm.com/
[bison]: https://www.gnu.org/software/bison/
[flex]: https://github.com/westes/flex
[npcap]: https://nmap.org/npcap/
[zlib]: https://www.zlib.net
[pcre2]: https://pcre.org
[libpng]: http://www.libpng.org/pub/png/libpng.html
[FreeType]: https://www.freetype.org/
[libpcap]: https://www.tcpdump.org/
[SDL2]: https://www.libsdl.org/
[SDL2_ttf]: https://www.libsdl.org/projects/SDL_ttf/
[mingw64]: https://mingw-w64.org/
[winflexbison]: https://github.com/lexxmark/winflexbison
[pthreads4w]: https://github.com/jwinarske/pthreads4w
[chocolatey]: https://chocolatey.org/
[vcpkg]: https://github.com/Microsoft/vcpkg
[gitlab]: https://gitlab.com/scooter-phd/simh-cmake
[clang]: https://clang.llvm.org/
