import pprint

import simgen.parse_makefile as SPM
import simgen.basic_simulator as SBS
import simgen.utils as SU

## Map simulator name to its class, for special cases
_special_simulators = {
    "besm6": SBS.BESM6Simulator,
    "i650": SBS.IBM650Simulator,
    "pdp10-ka": SBS.KA10Simulator,
    "vax": SBS.VAXSimulator
}

def get_simulator_ctor(name):
    """Return the class object for special case simulators, otherwise
    return the base 'SIMHBasicSimulator'
    """
    return _special_simulators.get(name) or SBS.SIMHBasicSimulator


class SimCollection:
    """A collection of simulators.
    """
    def __init__(self, dir_macro):
        self.source_macros = {}
        self.macro_uses = {}
        self.simulators = {}

    def get_simulator(self, name, dir_macro, _dir_path, test_name):
        sim = self.simulators.get(name)
        if sim is None:
            sim = (get_simulator_ctor(name))(name, dir_macro, test_name)
            self.simulators[name] = sim
        return sim

    def add_source_macro(self, macro, macro_def, sim):
        if macro not in self.source_macros:
            self.source_macros[macro] = macro_def

        used = self.macro_uses.get(macro)
        if used is None:
            self.macro_uses[macro] = []
            used = self.macro_uses[macro]
        used.append(sim)

    def get_simulator_vars(self, debug=0):
        simvars = set()
        ignored = set(self.source_macros.keys())
        for macval in self.source_macros.values():
            ## This could be replaced by a functools.reduce()
            for val in macval:
                simvars = simvars.union(set(SPM.extract_variables(val)))

        for sim in self.simulators.values():
            simvars = simvars.union(sim.get_source_vars().union(sim.get_include_vars()))

        simvars = simvars.difference(ignored).difference(SPM._special_vars)
        SU.emit_debug(debug, 2, 'simvars {0}'.format(simvars))
        return simvars

    def write_simulators(self, stream, debug=0, individual=False):
        ## Emit source macros
        dontexpand = set([smac for smac, uses in self.macro_uses.items() if len(uses) > 1])
        SU.emit_debug(debug, 2, "{0}: dontexpand {1}".format(self.__class__.__name__, dontexpand))

        if len(dontexpand) > 0:
            smac_sorted = list(dontexpand)
            smac_sorted.sort()
            for smac in smac_sorted:
                stream.write('\n\n')
                stream.write('set({0}\n'.format(smac))
                stream.write('\n'.join([' ' * 4 + f for f in self.source_macros[smac]]))
                stream.write(')')
            stream.write('\n\n')

        ## Emit the simulators
        simnames = list(self.simulators.keys())
        simnames.sort()
        SU.emit_debug(debug, 2, "{0}: Writing {1}".format(self.__class__.__name__, simnames))
        for simname in simnames:
            sim = self.simulators[simname]

            ## Patch up the simulator source lists, expanding macros that aren't
            ## in the macro sources:
            updated_srcs = []
            for src in sim.sources:
                m = SPM._var_rx.match(src)
                if m and m[1] not in dontexpand.union(SPM._special_vars):
                    updated_srcs.extend(self.source_macros[m[1]])
                else:
                    updated_srcs.append(src)
            sim.sources = updated_srcs

            stream.write('\n')
            sim.write_simulator(stream, 0, individual)

    def __len__(self):
        return len(self.simulators)

if '_dispatch' in pprint.PrettyPrinter.__dict__:
    def simcoll_pprinter(pprinter, simcoll, stream, indent, allowance, context, level):
        cls = simcoll.__class__
        stream.write(cls.__name__ + '(')
        indent += len(cls.__name__) + 1
        pprinter._format(simcoll.source_macros, stream, indent, allowance + 2, context, level)
        stream.write(',\n' + ' ' * indent)
        uses_dict = dict([(sim, len(uses)) for (sim, uses) in simcoll.macro_uses.items()])
        pprinter._format(uses_dict, stream, indent, allowance + 2, context, level)
        stream.write(',\n' + ' ' * indent)
        pprinter._format(simcoll.simulators, stream, indent, allowance + 2, context, level)
        stream.write(')')

    pprint.PrettyPrinter._dispatch[SimCollection.__repr__] = simcoll_pprinter
