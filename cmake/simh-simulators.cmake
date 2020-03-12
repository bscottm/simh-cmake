##
## This is an automagically generated file. Do NOT EDIT.
## Any changes you make will be overwritten!!
##
## Make changes to the SIMH top-level makefile and then run the
## "cmake/generate.py" script to regenerate these files.
##
##     python -m cmake/generate --help
##
## ------------------------------------------------------------
set(ALTAIRD    "${CMAKE_SOURCE_DIR}/ALTAIR")
set(ALTAIRZ80D "${CMAKE_SOURCE_DIR}/AltairZ80")
set(ATT3B2D    "${CMAKE_SOURCE_DIR}/3B2")
set(B5500D     "${CMAKE_SOURCE_DIR}/B5500")
set(BESM6D     "${CMAKE_SOURCE_DIR}/BESM6")
set(CDC1700D   "${CMAKE_SOURCE_DIR}/CDC1700")
set(GRID       "${CMAKE_SOURCE_DIR}/GRI")
set(H316D      "${CMAKE_SOURCE_DIR}/H316")
set(HP2100D    "${CMAKE_SOURCE_DIR}/HP2100")
set(HP3000D    "${CMAKE_SOURCE_DIR}/HP3000")
set(I1401D     "${CMAKE_SOURCE_DIR}/I1401")
set(I1620D     "${CMAKE_SOURCE_DIR}/I1620")
set(I7000D     "${CMAKE_SOURCE_DIR}/I7000")
set(I7010D     "${CMAKE_SOURCE_DIR}/I7000")
set(I7094D     "${CMAKE_SOURCE_DIR}/I7094")
set(IBM1130D   "${CMAKE_SOURCE_DIR}/Ibm1130")
set(ID16D      "${CMAKE_SOURCE_DIR}/Interdata")
set(ID32D      "${CMAKE_SOURCE_DIR}/Interdata")
set(KA10D      "${CMAKE_SOURCE_DIR}/PDP10")
set(KI10D      "${CMAKE_SOURCE_DIR}/PDP10")
set(KL10D      "${CMAKE_SOURCE_DIR}/PDP10")
set(LGPD       "${CMAKE_SOURCE_DIR}/LGP")
set(NOVAD      "${CMAKE_SOURCE_DIR}/NOVA")
set(PDP10D     "${CMAKE_SOURCE_DIR}/PDP10")
set(PDP11D     "${CMAKE_SOURCE_DIR}/PDP11")
set(PDP18BD    "${CMAKE_SOURCE_DIR}/PDP18B")
set(PDP1D      "${CMAKE_SOURCE_DIR}/PDP1")
set(PDP6D      "${CMAKE_SOURCE_DIR}/PDP10")
set(PDP8D      "${CMAKE_SOURCE_DIR}/PDP8")
set(S3D        "${CMAKE_SOURCE_DIR}/S3")
set(SDSD       "${CMAKE_SOURCE_DIR}/SDS")
set(SIGMAD     "${CMAKE_SOURCE_DIR}/sigma")
set(SSEMD      "${CMAKE_SOURCE_DIR}/SSEM")
set(TX0D       "${CMAKE_SOURCE_DIR}/TX-0")
set(UC15D      "${CMAKE_SOURCE_DIR}/PDP11")
set(VAXD       "${CMAKE_SOURCE_DIR}/VAX")

set(DISPLAYD   "${CMAKE_SOURCE_DIR}/display")
set(DISPLAY340 "${DISPLAYD}/type340.c")
set(DISPLAYNG  "${DISPLAYD}/ng.c")
set(DISPLAYVT  "${DISPLAYD}/vt11.c")

set(INTELSYSD  "${CMAKE_SOURCE_DIR}/Intel-Systems")
set(IMDS210C   "${INTELSYSD}/common")
set(IMDS210D   "${INTELSYSD}/imds-210")
set(IMDS220C   "${INTELSYSD}/common")
set(IMDS220D   "${INTELSYSD}/imds-220")
set(IMDS225C   "${INTELSYSD}/common")
set(IMDS225D   "${INTELSYSD}/imds-225")
set(IMDS230C   "${INTELSYSD}/common")
set(IMDS230D   "${INTELSYSD}/imds-230")
set(IMDS800C   "${INTELSYSD}/common")
set(IMDS800D   "${INTELSYSD}/imds-800")
set(IMDS810C   "${INTELSYSD}/common")
set(IMDS810D   "${INTELSYSD}/imds-810")
set(ISYS8010C  "${INTELSYSD}/common")
set(ISYS8010D  "${INTELSYSD}/isys8010")
set(ISYS8020C  "${INTELSYSD}/common")
set(ISYS8020D  "${INTELSYSD}/isys8020")
set(ISYS8024C  "${INTELSYSD}/common")
set(ISYS8024D  "${INTELSYSD}/isys8024")
set(ISYS8030C  "${INTELSYSD}/common")
set(ISYS8030D  "${INTELSYSD}/isys8030")
set(SCELBIC    "${INTELSYSD}/common")
set(SCELBID    "${INTELSYSD}/scelbi")

## ----------------------------------------

add_subdirectory(3B2)
add_subdirectory(ALTAIR)
add_subdirectory(AltairZ80)
add_subdirectory(B5500)
add_subdirectory(BESM6)
add_subdirectory(CDC1700)
add_subdirectory(GRI)
add_subdirectory(H316)
add_subdirectory(HP2100)
add_subdirectory(HP3000)
add_subdirectory(I1401)
add_subdirectory(I1620)
add_subdirectory(I7000)
add_subdirectory(I7094)
add_subdirectory(Ibm1130)
add_subdirectory(Intel-Systems/imds-210)
add_subdirectory(Intel-Systems/imds-220)
add_subdirectory(Intel-Systems/imds-225)
add_subdirectory(Intel-Systems/imds-230)
add_subdirectory(Intel-Systems/imds-800)
add_subdirectory(Intel-Systems/imds-810)
add_subdirectory(Intel-Systems/isys8010)
add_subdirectory(Intel-Systems/isys8020)
add_subdirectory(Intel-Systems/isys8024)
add_subdirectory(Intel-Systems/isys8030)
add_subdirectory(Intel-Systems/scelbi)
add_subdirectory(Interdata)
add_subdirectory(LGP)
add_subdirectory(NOVA)
add_subdirectory(PDP1)
add_subdirectory(PDP10)
add_subdirectory(PDP11)
add_subdirectory(PDP18B)
add_subdirectory(PDP8)
add_subdirectory(S3)
add_subdirectory(SDS)
add_subdirectory(SSEM)
add_subdirectory(TX-0)
add_subdirectory(VAX)
add_subdirectory(sigma)