import pprint

import simgen.parse_makefile as SPM
import simgen.utils as SU

class SIMHBasicSimulator:
    """
    """
    def __init__(self, sim_name, dir_macro, test_name):
        self.sim_name = sim_name
        self.dir_macro = dir_macro
        self.test_name = test_name
        self.int64 = False
        self.full64 = False
        self.video = False
        self.sources = []
        self.defines = []
        self.includes = []

    def add_source(self, src):
        if src not in self.sources:
            self.sources.append(src)

    def add_include(self, incl):
        if incl not in self.includes:
            self.includes.append(incl)

    def add_define(self, define):
        if define not in self.defines:
            self.defines.append(define)

    def scan_for_flags(self, defs):
        """Scan for USE_INT64/USE_ADDR64 in the simulator's defines and set the
        'int64' and 'full64' instance variables. If found, these defines are
        removed. Also look for any of the "DISPLAY" make macros, and, if found,
        set the 'video' instance variable.
        """
        use_int64 = 'USE_INT64' in self.defines
        use_addr64 = 'USE_ADDR64' in self.defines
        if use_int64 or use_addr64:
            self.int64  = use_int64 and not use_addr64
            self.full64 = use_int64 and use_addr64
            try:
                self.defines.remove('USE_INT64')
            except:
                pass
            try:
                self.defines.remove('USE_ADDR64')
            except:
                pass
        self.video = any(map(lambda s: 'DISPLAY' in SPM.shallow_expand_vars(s, defs), self.sources))
        if self.video:
            try:
                self.sources.remove('${DISPLAYL}')
            except:
                pass
            try:
                self.sources.remove('$(DISPLAYL)')
            except:
                pass

    def cleanup_defines(self):
        """Remove command line defines that aren't needed (because the CMake interface libraries
        already define them.)
        """
        for define in ['USE_SIM_CARD', 'USE_SIM_VIDEO', 'USE_NETWORK', 'USE_SHARED']:
            try:
                self.defines.remove(define)
            except:
                pass

    def get_source_vars(self):
        srcvars = set()
        for src in self.sources:
            srcvars = srcvars.union(set(SPM.extract_variables(src)))
        return srcvars

    def get_include_vars(self):
        incvars = set()
        for inc in self.includes:
            incvars = incvars.union(set(SPM.extract_variables(inc)))
        return incvars

    def write_simulator(self, stream, indent, individual=False):
        if individual:
            ## When writing an individual CMakeList.txt, we can take advantage of the CMAKE_CURRENT_SOURCE_DIR
            ## as a replacement for the SIMH directory macro.
            srcs = [ src.replace(self.dir_macro + '/', '') for src in self.sources]
            incs = [ inc if inc != self.dir_macro else '${CMAKE_CURRENT_SOURCE_DIR}' for inc in self.includes]
        else:
            ## But when writing out the BF CMakeLists.txt, make everything explicit.
            srcs = self.sources
            incs = self.includes

        if self.video:
            stream.write(' ' * indent + 'if (BUILD_WITH_VIDEO)\n')
            indent += 4

        indent4 = ' ' * (indent + 4)
        indent8 = ' ' * (indent + 8)
        stream.write(' ' * indent + 'add_simulator({}\n'.format(self.sim_name))
        stream.write(' ' * (indent + 4) + 'SOURCES\n')
        stream.write('\n'.join(map(lambda src: indent8 + src, srcs)))
        if len(self.includes) > 0:
            stream.write('\n' + indent4 + 'INCLUDES\n')
            stream.write('\n'.join([ indent8 + inc for inc in incs]))
        if len(self.defines) > 0:
            stream.write('\n' + indent4 + 'DEFINES\n')
            stream.write('\n'.join(map(lambda dfn: indent8 + dfn, self.defines)))
        if self.int64:
            stream.write('\n' + indent4 + 'INT64')
        if self.full64:
            stream.write('\n' + indent4 + 'FULL64')
        if self.video:
            stream.write('\n' + indent4 + "VIDEO")
        stream.write('\n' + indent4 + "TEST " + self.test_name)
        if not individual:
            stream.write('\n' + indent4 + "SOURCE_DIR " + self.dir_macro)
        stream.write(')\n')

        if self.video:
            indent -= 4
            stream.write(' ' * indent + 'endif (BUILD_WITH_VIDEO)\n')

    def __repr__(self):
        return '{0}({1},{2},{3},{4})'.format(self.__class__.__name__, self.sim_name.__repr__(),
            self.sources.__repr__(), self.includes.__repr__(), self.defines.__repr__())


class BESM6Simulator(SIMHBasicSimulator):
    """The (fine Communist) BESM6 simulator needs some extra code
    in the CMakeLists.txt to detect a suitable font that supports
    Cyrillic.
    """
    def __init__(self, sim_name, dir_macro, test_name):
        super().__init__(sim_name, dir_macro, test_name)
        self.defines.append("FONTFILE=${besm6_font}")

    def scan_for_flags(self, defs):
        super().scan_for_flags(defs)
        self.video = True

    def write_simulator(self, stream, indent, individual=False):
        ## Fixups... :-)
        try:
            self.defines.remove('FONTFILE=$(FONTFILE)')
        except:
            pass
        try:
            self.defines.remove('FONTFILE=${FONTFILE}')
        except:
            pass

        ## Add the search for a font file.
        stream.write('\n'.join([
            'set(besm6_font)',
            'foreach (fdir IN ITEMS',
            '           "/usr/share/fonts" "/Library/Fonts" "/usr/lib/jvm"',
            '           "/System/Library/Frameworks/JavaVM.framework/Versions"',
            '           "$ENV{WINDIR}/Fonts")',
            '    foreach (font IN ITEMS',
            '                "DejaVuSans.ttf" "LucidaSansRegular.ttf"',
            '                "FreeSans.ttf" "AppleGothic.ttf" "tahoma.ttf")',
            '        if (EXISTS ${fdir}/${font})',
            '            get_filename_component(fontfile ${fdir}/${font} ABSOLUTE)',
            '            list(APPEND besm6_font ${fontfile})',
            '        endif ()',
            '    endforeach()',
            'endforeach()',
            '',
            'if (besm6_font)',
            '    list(LENGTH besm6_font besm6_font_len)',
            '    if (besm6_font_len GREATER 1)',
            '        message(STATUS "BESM6: Fonts found ${besm6_font}")',
            '    endif ()',
            '    list(GET besm6_font 0 besm6_font)',
            '    message(STATUS "BESM6: Using ${besm6_font}")',
            'endif (besm6_font)',
            '',
            'if (besm6_font)\n']))
        super().write_simulator(stream, indent + 4, individual)
        stream.write('endif ()\n')

class VAXSimulator(SIMHBasicSimulator):
    """
    """
    def __init__(self, sim_name, dir_macro, test_name):
        super().__init__(sim_name, dir_macro, test_name)

    def write_simulator(self, stream, indent, individual=False):
        super().write_simulator(stream, indent, individual)
        stream.write('\n')
        stream.write('\n'.join([
            'set(vax_symlink_dir_src ${CMAKE_CURRENT_BINARY_DIR})',
            'if (CMAKE_CONFIGURATION_TYPES)',
            '    string(APPEND vax_symlink_dir_src "/$<CONFIG>")',
            'endif (CMAKE_CONFIGURATION_TYPES)',
            ' '.join(['add_custom_command(TARGET vax POST_BUILD',
                      ' '.join(['COMMAND "${CMAKE_COMMAND}" -E copy_if_different',
                                'vax${CMAKE_EXECUTABLE_SUFFIX}',
                                'microvax3900${CMAKE_EXECUTABLE_SUFFIX}']),
                                'COMMENT '
                                  '"Copy vax${CMAKE_EXECUTABLE_SUFFIX} to '
                                  'microvax3900${CMAKE_EXECUTABLE_SUFFIX}"',
                                'WORKING_DIRECTORY ${vax_symlink_dir_src})']),
                      'install(FILES ${vax_symlink_dir_src}/microvax3900${CMAKE_EXECUTABLE_SUFFIX}',
                      '        DESTINATION ${CMAKE_INSTALL_BINDIR})']))
        stream.write('\n')

class KA10Simulator(SIMHBasicSimulator):
    def __init__(self, sim_name, dir_macro, test_name):
        super().__init__(sim_name, dir_macro, test_name)

    def write_simulator(self, stream, indent, individual=False):
        super().write_simulator(stream, indent, individual)
        stream.write('\n')
        stream.write('\n'.join([
            'if (PANDA_LIGHTS)',
            '  target_sources(pdp10-ka PUBLIC ${KA10D}/ka10_lights.c)',
            '  target_compile_definitions(pdp10-ka PUBLIC PANDA_LIGHTS)',
            '  target_link_libraries(pdp10-ka PUBLIC usb-1.0)',
            'endif (PANDA_LIGHTS)'
        ]))
        stream.write('\n')

if '_dispatch' in pprint.PrettyPrinter.__dict__:
    def sim_pprinter(pprinter, sim, stream, indent, allowance, context, level):
        cls = sim.__class__
        stream.write(cls.__name__ + '(')
        indent += len(cls.__name__) + 1
        pprinter._format(sim.sim_name, stream, indent, allowance + 2, context, level)
        stream.write(',')
        pprinter._format(sim.dir_macro, stream, indent, allowance + 2, context, level)
        stream.write(',')
        pprinter._format(sim.int64, stream, indent, allowance + 2, context, level)
        stream.write(',')
        pprinter._format(sim.full64, stream, indent, allowance + 2, context, level)
        stream.write(',')
        pprinter._format(sim.video, stream, indent, allowance + 2, context, level)
        stream.write(',')
        pprinter._format(sim.sources, stream, indent, allowance + 2, context, level)
        stream.write(',\n' + ' ' * indent)
        pprinter._format(sim.defines, stream, indent, allowance + 2, context, level)
        stream.write(',\n' + ' ' * indent)
        pprinter._format(sim.includes, stream, indent, allowance + 2, context, level)
        stream.write(')')

    pprint.PrettyPrinter._dispatch[SIMHBasicSimulator.__repr__] = sim_pprinter