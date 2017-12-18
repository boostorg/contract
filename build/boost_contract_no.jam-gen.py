
print '''
# Generated file `python boost_contract_no.jam-gen.py > boost_contract_no.jam`.

# Copyright (C) 2008-2018 Lorenzo Caminiti
# Distributed under the Boost Software License, Version 1.0 (see accompanying
# file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
# See: https://lcaminiti.github.io/boost-contract
'''

import collections
import itertools

defs = collections.OrderedDict([
    # Keys must be short (~2 chars) to avoid MSVC link error on long file names.
    ('yi', 'BOOST_CONTRACT_NO_ENTRY_INVARIANTS'),
    ('pe', 'BOOST_CONTRACT_NO_PRECONDITIONS'),
    ('xi', 'BOOST_CONTRACT_NO_EXIT_INVARIANTS'),
    ('po', 'BOOST_CONTRACT_NO_POSTCONDITIONS'),
    ('ex', 'BOOST_CONTRACT_NO_EXCEPTS'),
    ('ck', 'BOOST_CONTRACT_NO_CHECKS')
    # Add more macros here.
])

print 'module boost_contract_no {\n'
s = ''
exit
for r in range(len(defs.keys())):
    for comb in itertools.combinations(defs.keys(), r + 1):
        c = ''
        d = ''
        sep = ''
        for cond in comb:
            c += sep + cond
            sep = '_'
            d += " <define>" + defs[cond]
        s += ' ' + c
        print 'rule defs_{0} {{ return {1} ; }}\n'.format(c, d)
print '''rule combinations {{ return {0} ; }}

}} # module

# All combinations: {1}
'''.format(s, s.replace(" ", ","))

