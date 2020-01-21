## The Russian BESM-6 add_simulator
##
## Needs a Cyrillic font for the display console.

set(BESM6_SOURCES
        besm6_cpu.c
        besm6_sys.c
        besm6_mmu.c
        besm6_arith.c
        besm6_disk.c
        besm6_drum.c
        besm6_tty.c
        besm6_panel.c
        besm6_printer.c
        besm6_punch.c
        besm6_punchcard.c)

set(besm6_font)
foreach (fdir IN ITEMS
            "/usr/share/fonts" "/Library/Fonts" "/usr/lib/jvm"
            "/System/Library/Frameworks/JavaVM.framework/Versions"
            "$ENV{WINDIR}/Fonts")
    foreach (font IN ITEMS
                "DejaVuSans.ttf" "LucidaSansRegular.ttf" "FreeSans.ttf" "AppleGothic.ttf" "tahoma.ttf")
        if (EXISTS ${fdir}/${font})
            get_filename_component(fontfile ${fdir}/${font} ABSOLUTE)
            list(APPEND besm6_font ${fontfile})
        endif ()
    endforeach()
endforeach()

if (besm6_font)
    list(GET besm6_font 0 besm6_font)
endif (besm6_font)

if (BUILD_WITH_VIDEO AND besm6_font)
    add_simulator(besm6
        SOURCES
            ${BESM6_SOURCES}
        DEFINES
            FONTFILE=${besm6_font}
        INT64
        VIDEO)
else ()
    add_simulator(besm6
        SOURCES
            ${BESM6_SOURCES}
        INT64)
endif ()