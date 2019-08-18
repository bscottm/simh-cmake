#
# Build/rebuild the windows-build components using CMake and Ninja
#
# (scooter me fecit.)

param (
  # Force a clean rebuild. Default is false.
  [switch]$clean = $false,
  [string]$tool  = "ninja",
  [switch]$help  = $false,
  [switch]$debug = $false,
  [string]$arch = "32"
)

$myname = $MyInvocation.MyCommand.Name

function Builder-Help {
@'
Valid flags and options:

-arch:[32|64]  string  Compile-to architecture: 32 or 64, default 32
-clean         flag    Clean build and staging directories before building
-debug         flag    Build for Debug, default is build for Release
-help          flag    Display this help message
-tool:name     string  CMake Generator, default is "ninja"

Currently supported tools:

ninja    Ninja buildsystem
mingw    MinGW Makefiles
vs2019   Visual Studio 16 2019
vs2017   Visual Studio 15 2017
'@
}

if ($help)
{
  Builder-Help
  exit 0
}

# Determine the CMake generator... and validate the tool, while we're at it.
$cmakeGen = ""
$cmake_target_arch=""

switch ($tool)
{
  "ninja"  { $cmakeGen = "Ninja"; break }
  "mingw"  { $cmakeGen = "MinGW Makefiles"; break }
  "vs2019" {
    $cmakeGen = "Visual Studio 16 2019";
    if ($arch -eq "32")
    {
      $cmake_target_arch = "-Awin32";
    }
    break
  }
  "vs2017" {
    $cmakeGen = "Visual Studio 15 2017";
    if ($arch -eq "64")
    {
      $cmakeGen = "$cmakeGen Win64";
    }
    break
  }
  default  {
    "${myname}: Don't know about this tool: $tool";
    "";
    Builder-Help;
    exit 1;
    break; }
}

$build=[System.IO.Path]::GetFullPath((Join-Path (Get-Location) "cmake-build"))
$topdir=$(pwd)

# Clean out the build directory
if ($clean -and (Test-Path -Path $build))
{
  "-- Removing the build directory (${build})"
  remove-item -recurse -force $build | out-null
}

"-- Build directory: $build"
new-item -erroraction:ignore -itemtype "directory" $build

# Default is a release build, when it matters
$cmake_config="Release"
if ($debug)
{
  $cmake_config="Debug"
}

push-location $build
cmake -G "$cmakeGen" $cmake_target_arch $topdir
cmake --build . --config $cmake_config --target install
pop-location
