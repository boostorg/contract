
print '''
# Generated file `python boost_contract_no.jam-gen.py > boost_contract_no.jam`.

# Copyright (C) 2008-2018 Lorenzo Caminiti
# Distributed under the Boost Software License, Version 1.0 (see accompanying
# file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
# See: https://lcaminiti.github.io/boost-contract
'''

# NOTE: Other macros symbols can be added here as needed.
conds = ['entryinv', 'pre', 'exitinv', 'post', 'except', 'check']
defs = {
    'entryinv': 'BOOST_CONTRACT_NO_ENTRY_INVARIANTS',
    'pre':      'BOOST_CONTRACT_NO_PRECONDITIONS',
    'exitinv':  'BOOST_CONTRACT_NO_EXIT_INVARIANTS',
    'post':     'BOOST_CONTRACT_NO_POSTCONDITIONS',
    'except':   'BOOST_CONTRACT_NO_EXCEPTS',
    'check':    'BOOST_CONTRACT_NO_CHECKS'
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

