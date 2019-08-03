## Powershell script to ensure the BIN directory and all of its various components exist.
## This also copies over all of the DLLs.

param(
  [Parameter(ValueFromRemainingArguments)]$args
)

if ($args.count -ne 1)
{
  write-error -message "Not enough arguments." -erroraction stop
}

$bindir=[System.IO.Path]::GetFullPath("$($args[0])\BIN")
$winbuild_bin=[System.IO.Path]::GetFullPath("$($args[0])\..\windows-build\build-stage\bin")
if ((test-path "$bindir") -and (-not (Test-Path "$bindir" -PathType Container)))
{
  remove-item -recurse -force "$bindir"
}

if (-not (Test-Path -LiteralPath "$bindir"))
{
  try {
    new-item -type directory -erroraction:stop -path "$bindir" | out-null

    "*** Created BIN directory ($bindir)"
    new-item -erroraction:ignore -type directory "$bindir\Win32" | out-null
    new-item -erroraction:ignore -type directory "$bindir\Win32\Debug" | out-null
    new-item -erroraction:ignore -type directory "$bindir\Win32\Release" | out-null

    if ((test-path "$winbuild_bin") -and (Test-Path "$winbuild_bin" -type container))
    {
      # pcap installs its stuff in the amd64 subdirectory
      copy-item -path "$winbuild_bin\amd64\*.dll" -destination "$bindir" 
      copy-item -path "$winbuild_bin\*.dll"       -destination "$bindir" 
      copy-item -path "$winbuild_bin\amd64\*.dll" -destination "$bindir\Win32\Debug" 
      copy-item -path "$winbuild_bin\*.dll"       -destination "$bindir\Win32\Debug" 
      copy-item -path "$winbuild_bin\amd64\*.dll" -destination "$bindir\Win32\Release" 
      copy-item -path "$winbuild_bin\*.dll"       -destination "$bindir\Win32\Release" 
    }
  }
  catch {
    Write-Error -Message "Unable to create directory '$bindir'. Error was: $_" -ErrorAction Stop
  }
}
