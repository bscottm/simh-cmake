## cmake_container.py
##
## A container for a collection of SIMH simulators
##
##

import sys
import os
import re
import pprint
import functools

import simgen.parse_makefile as SPM
import simgen.sim_collection as SC
import simgen.utils as SU

## Corresponding special variable uses in the makefile:
_special_sources = frozenset(['${DISPLAYL}', '$(DISPLAYL)'])

## Banner header for individual CMakeLists.txt files:
_individual_header = [
    '##',
    '## This is an automagically generated file. Do NOT EDIT.',
    '## Any changes you make will be overwritten!!',
    '##',
    '## Make changes to the SIMH top-level makefile and then run the',
    '## "cmake/generate.py" script to regenerate these files.',
    '##',
    '##     python -m cmake/generate --help',
    '##',
    '## ' + '-' * 60 + '\n',
    ]

## Banner header for the BF CMakeLists.txt
_all_in_one_banner = [
    '## ' + '-' * 60,
    '## This is an automagically generated file. Do NOT EDIT.',
    '## Any changes you make will be overwritten!!',
    '##',
    '## Make changes to the SIMH top-level makefile and use the',
    '## cmake/generate.py script to regenerate these files.',
    '##',
    '##     python -m cmake/generate --help',
    '##',
    '## ' + '-' * 60 + '\n',
    ]

class CMakeBuildSystem:
    """A container for collections of SIMH simulators and automagic
    CMakeLists.txt driver.

    This is the top-level container that stores collections of SIMH simulators
    in the 'SIM'
    """

    ## Compile command line elements that are ignored.
    _ignore_compile_elems = frozenset(['${LDFLAGS}', '$(LDFLAGS)',
        '${CC_OUTSPEC}', '$(CC_OUTSPEC)',
        '${SIM}', '$(SIM)',
        '-o', '$@',
        '${NETWORK_OPT}', '$(NETWORK_OPT)',
        '${SCSI}', '$(SCSI)',
        '${DISPLAY_OPT}', '$(DISPLAY_OPT)',
        '${VIDEO_CCDEFS}', '$(VIDEO_CCDEFS)',
        '${VIDEO_LDFLAGS}', '$(VIDEO_LDFLAGS)'])

    def __init__(self):
        # "Special" variables that we look for in source code lists and which we'll
        # emit into the CMakeLists.txt files.
        self.vars = {'DISPLAYVT': ['${DISPLAYD}/vt11.c'],
            'DISPLAY340': ['${DISPLAYD}/type340.c'],
            'DISPLAYNG': ['${DISPLAYD}/ng.c'],
            'DISPLAYIII': ['${DISPLAYD}/iii.c'] }
        # Subdirectory -> SimColletion mapping
        self.dirs = {}


    def extract(self, compile_action, test_name, sim_dir, sim_name, defs, debug=0, depth=''):
        """Extract sources, defines, includes and flags from the simulator's
        compile action in the makefile.
        """
        sim_dir_path = SPM.expand_vars(sim_dir, defs).replace('./', '')
        simcoll = self.dirs.get(sim_dir_path)
        if simcoll is None:
            simcoll = SC.SimCollection(sim_dir)
            self.dirs[sim_dir_path] = simcoll

        sim = simcoll.get_simulator(sim_name, sim_dir, sim_dir_path, test_name)

        # Remove compile command line elements and do one level of variable expansion, split the resulting
        # string into a list.
        all_comps = []
        for comp in [ SPM.normalize_variables(act) for act in compile_action.split() if not self.compile_elems_to_ignore(act) ]:
            all_comps.extend(comp.split())

        if debug >= 3:
            print('{0}all_comps after filtering:'.format(depth))
            pprint.pp(all_comps)

        # Iterate through the final compile component list and extract source files, includes
        # and defines.
        #
        # Deferred: Looking for options that set the i64, z64, video library options.
        while all_comps:
            comp = all_comps[0]
            # print(':: comp {0}'.format(comp))
            if self.is_source(comp):
                # Source file...
                ## sim.add_source(comp.replace(sim_dir + '/', ''))
                sim.add_source(comp)
            elif comp.startswith('-I'):
                all_comps = self.process_flag(all_comps, defs, sim.add_include)
            elif comp.startswith('-D'):
                all_comps = self.process_flag(all_comps, defs, sim.add_define)
            elif comp.startswith('-L') or comp.startswith('-l'):
                ## It's a library path or library. Skip.
                pass
            else:
                # Solitary variable expansion?
                m = SPM._var_rx.match(comp)
                if m:
                    varname = m.group(1)
                    if varname not in SPM._special_vars:
                        if not self.is_source_macro(comp, defs):
                            expand = [ SPM.normalize_variables(elem) for elem in SPM.shallow_expand_vars(comp, defs).split()
                                       if not self.source_elems_to_ignore(elem) ]
                            SU.emit_debug(debug, 3, '{0}var expanded {1} -> {2}'.format(depth, comp, expand))
                            all_comps[1:] = expand + all_comps[1:]
                        else:
                            ## Source macro
                            vardef = defs.get(varname)
                            if vardef is not None:
                                vardef = [ SPM.normalize_variables(v) for v in vardef.split() if not self.source_elems_to_ignore(v) ]
                                SU.emit_debug(debug, 3, '{0}source macro: {1} -> {2}'.format(depth, varname, vardef))
                                simcoll.add_source_macro(varname, vardef, sim)
                                sim.add_source(comp)
                            else:
                                print('{0}undefined make macro: {1}'.format(depth, varname))
                    else:
                        sim.add_source(comp)
                else:
                    # Nope.
                    print('{0}unknown component: {1}'.format(depth, comp))
            all_comps = all_comps[1:]

        sim.scan_for_flags(defs)
        sim.cleanup_defines()

        if debug >= 2:
            pprint.pprint(sim)


    def compile_elems_to_ignore(self, elem):
        return (elem in self._ignore_compile_elems or elem.endswith('_LDFLAGS'))

    def source_elems_to_ignore(self, elem):
        return self.compile_elems_to_ignore(elem) or elem in _special_sources


    def is_source_macro(self, var, defs):
        """Is the macro/variable a list of sources?
        """
        expanded = SPM.expand_vars(var, defs).split()
        # print('is_source_macro {}'.format(expanded))
        return all(map(lambda src: self.is_source(src), expanded))


    def is_source(self, thing):
        return thing.endswith('.c')


    def process_flag(self, comps, defs, process_func):
        if len(comps[0]) > 2:
            # "-Ddef"
            val = comps[0][2:]
        else:
            # "-D def"
            val = comps[1]
            comps = comps[1:]
        m = SPM._var_rx.match(val)
        if m:
            var = m.group(1)
            if var not in self.vars:
                self.vars[var] = defs[var]

        process_func(val)
        return comps


    def collect_vars(self, defs, debug=0):
        """Add indirectly referenced macros and variables, adding them to the defines dictionary.

        Indirectly referenced macros and variables are macros and variables embedded in existing
        variables, source macros and include lists. For example, SIMHD is an indirect reference
        in "KA10D = ${SIMHD}/ka10" because KA10D might never have been expanded by 'extract()'.
        """

        def scan_var(varset, var):
            tmp = var
            return varset.union(set(SPM.extract_variables(tmp)))

        def replace_simhd(l, v):
            l.append(v.replace('SIMHD', 'CMAKE_SOURCE_DIR'))
            return l

        simvars = set()
        for v in self.vars.values():
            if isinstance(v, list):
                simvars = functools.reduce(scan_var, v, simvars)
            else:
                simvars = scan_var(simvars, v)

        for dir in self.dirs.keys():
            simvars = simvars.union(self.dirs[dir].get_simulator_vars(debug))

        if debug >= 2:
            print('Collected simvars:')
            pprint.pprint(simvars)

        for var in simvars:
            if var not in self.vars:
                if var in defs:
                    self.vars[var] = defs[var]
                else:
                    print('{0}: variable not defined.'.format(var))

        ## Replace SIMHD with CMAKE_SOURCE_DIR
        for k, v in self.vars.items():
            if isinstance(v, list):
                v = functools.reduce(replace_simhd, v, [])
            else:
                v = v.replace('SIMHD', 'CMAKE_SOURCE_DIR')
            self.vars[k] = v


    def write_vars(self, stream):
        def collect_vars(varlist, var):
            varlist.extend(SPM.extract_variables(var))
            return varlist

        varnames = list(self.vars.keys())
        namewidth = max(map(lambda s: len(s), varnames))
        # vardeps maps the parent variable to its dependents, e.g.,
        # INTELSYSD -> [ISYS8010D, ...]
        vardeps = dict()
        # alldeps is the set of all parent and dependents, which will be
        # deleted from a copy of self.vars. The copy has variables that
        # don't depend on anything (except for CMAKE_SOURCE_DIR, but we
        # know that's defined by CMake.)
        alldeps = set()
        for var in varnames:
            if isinstance(self.vars[var], list):
                mvars = functools.reduce(collect_vars, self.vars[var], [])
            else:
                mvars = SPM.extract_variables(self.vars[var])
            mvars = [mvar for mvar in mvars if mvar != "CMAKE_SOURCE_DIR"]
            if mvars:
                alldeps.add(var)
                for mvar in mvars:
                    if mvar not in vardeps:
                        vardeps[mvar] = []
                    vardeps[mvar].append(var)
                    alldeps.add(mvar)

        nodeps = self.vars.copy()
        ## SIMHD will never be used.
        if 'SIMHD' in nodeps:
            del nodeps['SIMHD']
        for dep in alldeps:
            del nodeps[dep]

        varnames = list(nodeps.keys())
        varnames.sort()
        for var in varnames:
            self.emit_value(var, self.vars[var], stream, namewidth)

        ## Now to emit the dependencies
        depnames = list(vardeps.keys())
        depnames.sort()
        for dep in depnames:
            self.write_dep(dep, vardeps, alldeps, namewidth, stream)

        ## stream.write('\n## ' + '-' * 40 + '\n')

    def write_dep(self, dep, vardeps, alldeps, width, stream):
        # Not the most efficient, but it works
        alldeps.discard(dep)
        for parent in [ v for v in vardeps.keys() if dep in vardeps[v]]:
            if dep in parent.values():
                self.write_dep(parent, vardeps, alldeps, width, stream)

        stream.write('\n')
        self.emit_value(dep, self.vars[dep], stream, width)

        children = vardeps[dep]
        children.sort()
        for child in children:
            if child in alldeps:
                self.emit_value(child, self.vars[child], stream, width)
        alldeps -= set(children)

    def emit_value(self, var, value, stream, width=0):
        if isinstance(value, list):
            stream.write('set({:{width}} {})\n'.format(var, ' '.join(map(lambda s: '"' + s + '"', value)),
                                                       width=width))
        else:
            stream.write('set({:{width}} "{}")\n'.format(var, value, width=width))

    def write_simulators(self, toplevel_dir, stream=None, debug=0, individual=True):
        if not individual:
            if stream is None:
                stream = sys.stdout
            stream.write('\n'.join(_all_in_one_banner))
            self.write_vars(stream)

        dirnames = list(self.dirs.keys())
        dirnames.sort()

        for dir in dirnames:
            simcoll = self.dirs[dir]
            if individual:
                subdir_cmake = os.path.join(toplevel_dir, dir, 'CMakeLists.txt')
                print('==== writing to {0}'.format(subdir_cmake))
                with open(subdir_cmake, "w") as stream2:
                    plural = '' if len(self.dirs[dir]) == 1 else 's'
                    stream2.write('## {} simulator{plural}\n'.format(dir, plural=plural))
                    stream2.write('\n'.join(_individual_header))
                    simcoll.write_simulators(stream2, debug, individual)
            else:
                stream.write('\n## ' + '-' * 40 + '\n')
                simcoll.write_simulators(stream, debug, individual)

        if individual:
            simh_subdirs = os.path.join(toplevel_dir, 'cmake', 'simh-simulators.cmake')
            print("==== writing {0}".format(simh_subdirs))
            with open(simh_subdirs, "w") as stream2:
                stream2.write('\n'.join(_individual_header))
                self.write_vars(stream2)
                stream2.write('\n## ' + '-' * 40 + '\n\n')
                stmts = [ 'add_subdirectory(' + dir + ')' for dir in dirnames ]
                stream2.write('\n'.join(stmts))

    ## Representation when printed
    def __repr__(self):
        return '{0}({1}, {2})'.format(self.__class__.__name__, self.dirs.__repr__(), self.vars.__repr__())


if '_dispatch' in pprint.PrettyPrinter.__dict__:
    def cmake_pprinter(pprinter, cmake, stream, indent, allowance, context, level):
        cls = cmake.__class__
        stream.write(cls.__name__ + '(')
        indent += len(cls.__name__) + 1
        pprinter._format(cmake.dirs, stream, indent, allowance + 2, context, level)
        stream.write(',\n' + ' ' * indent)
        pprinter._format(cmake.vars, stream, indent, allowance + 2, context, level)
        stream.write(')')

    pprint.PrettyPrinter._dispatch[CMakeBuildSystem.__repr__] = cmake_pprinter
