#!/bin/bash

##-- Bash functions --
showHelp()
{
    [ x"$1" != x ] && { echo "${scriptName}: $1"; echo ""; }
    cat <<EOF
Configure and build simh simulators on Linux and *nix-like platforms.

Subdirectories:
cmake-unix: Makefile-based build simulators
cmake-ninja: Ninja build-based simulators

Options:
--------
--clean (-x)      Remove the build subdirectory 
--generate (-g)   Generate the build environment, don't compile/build
--parallel (-p)   Enable build parallelism (parallel builds)
--nonetwork       Build simulators without network support
--notest          Do not execute 'ctest' test cases
--testonly        Do not build, execute the 'ctest' test cases

--flavor (-f)     Specifies the build flavor: 'unix' or 'ninja'
--config (-c)     Specifies the build configuraiton: 'Release' or 'Debug'

--help (-h)       Print this help.
EOF

    exit 1
}

scriptName=$0
buildClean=
buildSubdir=cmake-unix
buildConfig=Release
nonetwork=
notest=
buildParallel=yes
generateOnly=
testOnly=

## This script really needs GNU getopt. Really.
getopt -T > /dev/null
if [ $? -ne 4 ] ; then
    echo "${scriptName}: GNU getopt needed for this script to function properly."
    exit 1
fi

ARGS=$(getopt \
         --longoptions clean,help,flavor:,config:,nonetwork,notest,parallel,generate,testonly \
	 --options xhf:cpg -- "$@")
if [ $? -ne 0 ] ; then
    showHelp "${scriptName}: Usage error (use -h for help.)"
fi

eval set -- ${ARGS}
while true; do
    case $1 in
	-x | --clean)
	    buildClean=yes; shift
	    ;;
	-h | --help)
	    showHelp
	    ;;
	-f | --flavor)
	    case "$2" in
		unix)
		    buildSubdir=cmake-unix
		    shift 2
		    ;;
		ninja)
		    buildSubdir=cmake-ninja
		    shift 2
		    ;;
		*)
		    showHelp "Invalid build flavor: $2"
		    ;;
	    esac
	    ;;
	-c | --config)
	    case "$2" in
		Release|Debug)
		    buildConfig=$2
		    shift 2
		    ;;
		*)
		    showHelp "Invalid build configuration: $2"
		    ;;
	    esac
	    ;;
	--nonetwork)
	    nonetwork=yes; shift
	    ;;
	--notest)
	    notest=yes; shift
	    ;;
	-p | --parallel)
	    buildParallel=yes; shift
	    ;;
	-g | --generate)
	    generateOnly=yes; shift
	    ;;
	--testonly)
	    testOnly=yes; shift
	    ;;
	--)
	    ## End of options, which we'll ignore.
	    shift; break
	    ;;
    esac
done

[ x"$clean" != x ] && rm -rf ${buildSubdir}
