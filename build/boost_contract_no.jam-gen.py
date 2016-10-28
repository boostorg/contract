
print '''
# Generated file `python boost_contract_no.jam-gen.py > boost_contract_no.jam`.
'''

# NOTE: Other macros symbols can be added here as needed.
conds = ['entryinv', 'pre', 'exitinv', 'post', 'except']
defs = {
    'entryinv': 'BOOST_CONTRACT_NO_ENTRY_INVARIANTS',
    'pre':      'BOOST_CONTRACT_NO_PRECONDITIONS',
    'exitinv':  'BOOST_CONTRACT_NO_EXIT_INVARIANTS',
    'post':     'BOOST_CONTRACT_NO_POSTCONDITIONS',
    'except':   'BOOST_CONTRACT_NO_EXCEPTS'
}

import itertools
print 'module boost_contract_no {\n'
s = ''
for r in range(len(conds)):
    for comb in itertools.combinations(conds, r + 1):
        c = ''
        d = ''
        sep = ''
        for cond in comb:
            c += sep + cond
            sep = '_'
            d += " <define>" + defs[cond]
        s += ' ' + c
        print 'rule defs_{0} {{ return {1} ; }}\n'.format(c, d)
print '''
rule conds {{ return {0} ; }}

}} # module
'''.format(s)

