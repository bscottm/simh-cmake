## cmake-builder.ps1
##
## CMake-based configure and build script for simh using MSVC and MinGW-W64.
##
## - The default builds SIMH for Visual Studio 2019 in the Release configuration.
## - The "-flavor" command line parameter switches between the various MSVC and
##   MinGW builds.
## - The "-config" command line parameter switches between Debug and Release
## - For all options, "-help" is available.
##
## The thumbnail overview: Create a subdirectory, run CMake to configure the
## build environment, build dependency libraries and then reconfigure and build
## the simulators.
##
## This script produces a "Batteries Included" set of simulators, which implies that
## Npcap is installed.
##
## Author: B. Scott Michel
## "scooter me fecit"

param (
    [switch] $clean       = $false,
    [switch] $help        = $false,
    [string] $flavor      = "2019",
    [string] $config      = "Release",
    [switch] $nonetwork   = $false,
    [switch] $notest      = $false,
    [switch] $parallel    = $false,
    [switch] $generate    = $false
)

$scriptName = $MyInvocation.InvocationName.replace('.\', '')

function Show-Help
{
    @"
Configure and build simh's dependencies and simulators using the Microsoft
Visual Studio C compiler or MinGW-W64-based gcc compiler.

cmake-vs* subdirectories: MSVC build products and artifacts
cmake-mingw subdirectory: MinGW-W64 products and artifacts

Arguments:
-clean           Remove and recreate the build subdirectory before configuring
                 and building
-generate        Generate build environment, do not compile/build.
                 (Useful for generating MSVC solutions, then compile/build within
		  the Visual Studio IDE.)
-parallel        Enable build parallelism (parallel target builds)
-nonetwork       Build simulators without network support.
-notest          Do not run 'ctest' test cases.

-flavor 2019     Generate build environment for Visual Studio 2019 (default)
-flavor 2017     Generate build environment for Visual Studio 2017
-flavor 2015     Generate build environment for Visual Studio 2015
-flavor 2013     Generate build environment for Visual Studio 2013
-flavor 2012     Generate build environment for Visual Studio 2012
-flavor mingw    Generate build environment for MinGW-W64

-config Release  Build dependencies and simulators for Release (optimized) (default)
-config Debug    Build dependencies and simulators for Debug

-help            Output this help.
"@

    exit 0
}

## Output help early and exit.
if ($help)
{
    Show-Help
}

## Sanity checking: Check that utilities we expect exist...
## CMake: Save the location of the command because we'll invoke it later. Same
## with CTest
$cmakeCmd = $(Get-Command -Name cmake.exe -ErrorAction Ignore).Path
$ctestCmd = $(Get-Command -Name ctest.exe -ErrorAction Ignore).Path
if ($cmakeCmd.Length -gt 0)
{
    Write-Output "** ${scriptName}: cmake is '${cmakeCmd}'"
}
else {
    @"
!! ${scriptName} error:

The 'cmake' command was not found. Please ensure that you have installed CMake
and that your PATH environment variable references the directory in which it
was installed.
"@

    exit 1
}

## bison/winbison and flex/winflex: Just make sure they exist.
if (!$nonetwork) {
  $haveBison = $false
  $haveFlex  = $false
  foreach ($i in @("bison", "winbison")) {
    if ($(Get-Command $i -ErrorAction Ignore).Path.Length -gt 0) { $haveBison = $true }
  }

  foreach ($i in @("flex",  "winflex")) {
    if ($(Get-Command $i -ErrorAction Ignore).Path.Length -gt 0) { $haveFlex  = $true }
  }

  if (!$haveBison)
  {
      @"
  !! ${scriptName} error:

  Did not find 'bison' or 'winbison'. Please ensure you have installed bison or
  winbison and that your PATH environment variables references the directory in
  which it was installed.
"@
  }

  if (!$haveFlex)
  {
      @"
  !! ${scriptName} error:

  Did not find 'flex' or 'winflex'. Please ensure you have installed flex or
  winflex and that your PATH environment variables references the directory in
  which it was installed.
"@
  }

  if (!$haveBison -or !$haveFlex)
  {
    exit 1
  }
}

## Check for GCC and mingw32-make if user wants the mingw flavor build.
if ($flavor -eq "mingw" -or $flavor -eq "ninja")
{
    if ($(Get-Command gcc -ErrorAction Ignore).Path.Length -eq 0) {
        @"
!! ${scriptName} error:

Did not find 'gcc', the GNU C/C++ compiler toolchain. Please ensure you have
installed gcc and that your PATH environment variables references the directory
in which it was installed.
"@
        exit 1
    }

    if ($(Get-Command mingw32-make -ErrorAction Ignore).Path.Length -eq 0) {
        @"
!! ${scriptName} error:

Did not find 'mingw32-make'. Please ensure you have installed mingw32-make and
that your PATH environment variables references the directory in which it was
installed.

Note: 'mingw32-make' is part of the MinGW-W64 software ecosystem. You may need
to open a MSYS or MinGW64 terminal window and use 'pacman' to install it.

Alternatively, if you use the Scoop package manager, 'scoop install gcc'
will install this as part of the current GCC compiler instalation.
"@
        exit 1
    }
}

if (!$nonetwork -and !(Test-Path -Path "C:\Windows\System32\Npcap"))
{
    ## Note: Windows does redirection under the covers to make the 32-bit
    ## version of Npcap appear in the C:\Windows\System32 directory. But
    ## it should be sufficient to detect the 64-bit runtime because both
    ## get installed.
    @"
!! ${scriptName} error:

Did not find the Npcap packet capture runtime. Please install it for simulator
network support:

    https://nmap.org/npcap/

Or invoke this script with the "-nonetwork" flag to disable networking support.

"@
}

## Look for Git's /usr/bin subdirectory: CMake (and other utilities) have issues
## with the /bin/sh installed there (Git's version of MinGW.)

$tmp_path = $env:PATH
$git_usrbin = "${env:ProgramFiles}\Git\usr\bin"
$tmp_path = ($tmp_path.Split(';') | Where-Object { $_ -ne "${git_usrbin}"}) -join ';'
if ($tmp_path -ne ${env:PATH})
{
    "** ${scriptName}: Removed ${git_usrbin} from PATH (Git MinGW problem)"
    $env:PATH = $tmp_path
}
#
## Setup:
$buildDir  = "cmake-vs"
$generator = "!!invalid!!"
$archFlag  = @()

switch ($flavor)
{
    "2019" {
        $buildDir += $flavor
        $generator = "Visual Studio 16 2019"
        $archFlag  = @("-A", "Win32")
    }
    "2017" {
        $buildDir += $flavor
        $generator = "Visual Studio 15 2017"
    }
    "2015" {
        $buildDir += $flavor
        $generator = "Visual Studio 14 2015"
    }
    "2013" {
        $buildDir += $flavor
        $generator = "Visual Studio 12 2013"
    }
    "2012" {
        $buildDir += $flavor
        $generator = "Visual Studio 11 2012"
    }
    "mingw" {
        $buildDir = "cmake-mingw"
        $generator = "MinGW Makefiles"
    }
    "ninja" {
	$buildDir = "cmake-ninja"
	$generator = "Ninja"
    }
    default {
	Write-Output ""
	Write-Output "!! ${scriptName}: Unrecognized build flavor '${flavor}'."
	Write-Error  "!! ${scriptName}: Unrecognized build flavor '${flavor}'."
	Write-Output ""
        Show-Help
    }
}

if (!@("Release", "Debug").Contains($config))
{
    @"
${scriptName}: Invalid configuration: "${config}".

"@
    Show-Help
}

## Clean out the 
if ((Test-Path -Path ${buildDir}) -and $clean)
{
    "** ${scriptName}: Removing ${buildDir}"
    Remove-Item -recurse -force -Path ${buildDir} -ErrorAction Continue | Out-Null
}

if (!(Test-Path -Path ${buildDir}))
{
    "** ${scriptName}: Creating ${buildDir} subdirectory"
    New-Item -Path ${buildDir} -ItemType Directory | Out-Null
}
else
{
    "** ${scriptName}: ${buildDir} exists."
}

## Where we do the heaving lifting:
$generateArgs = @("-G", ${generator}, "-D", "CMAKE_BUILD_TYPE=${config}") + ${archFlag} + @("..")
if ($nonetwork)
{
    $generateArgs += @("-DWITH_NETWORK:Bool=Off", "-DWITH_PCAP:Bool=Off", "-DWITH_SLIRP:Bool=Off")
}
$generateArgs += @("..")

$buildArgs     =  @("--build", ".", "--config", "${config}")
if ($parallel)
{
  $buildArgs += "--parallel"
}

$buildSpecificArgs = @()
if ($flavor -eq "mingw")
{
  ## Limit the number of parallel jobs mingw32-make can spawn. Otherwise
  ## it'll overwhelm the machine.
  $buildSpecificArgs += @("-j",  "8")
}

$exitval = 0

Push-Location ${buildDir}
try
{
    "** ${scriptName}: Configuring and generating"

    & ${cmakeCmd} ${generateArgs} 2>&1
    if (!$generate)
    {
	"** ${scriptName}: Building simulators."
	& ${cmakeCmd} ${buildArgs} -- ${buildSpecificArgs}
	if (!$notest)
	{
	  ## Let's test our results...
	  ##
	  ## If cmake failed, ctest will also fail. That's OK.
	  ##
	  ## Note: We're in the build directory already, so we can prepend $(Get-Location) for the
	  ## full path to the build directory, then normalize it.
	  $currentPath = $env:PATH
	  $buildStageBin = [System.IO.Path]::GetFullPath("$(Get-Location)\build-stage\bin")
	  $env:PATH =  "${buildStageBin};C:\Windows\System32\Npcap;${env:PATH}"
	  & $ctestCmd @("-C", $config)
	  $env:PATH = $currentPath
	}
    } else {
	"** ${scriptName}: Generated build environment in $(Get-Location)"
    }
}
catch
{
    "** ${scriptName}: Caught error, exiting."
    Format-List * -force -InputObject $_
    $exitval = 1
}
finally
{
    Pop-Location
}

exit $exitval
