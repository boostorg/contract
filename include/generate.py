
# Copyright (C) 2008-2012 Lorenzo Caminiti
# Distributed under the Boost Software License, Version 1.0
# (see accompanying file LICENSE_1_0.txt or a copy at
# http://www.boost.org/LICENSE_1_0.txt)
# Home at http://sourceforge.net/projects/contractpp

import os

scripts = [
    ("contract/detail/preprocessor/array", "first_n-generate.py"),
    ("contract/detail/preprocessor/array", "rest_n-generate.py"),
    ("contract/detail/preprocessor/facilities", "is_digit-generate.py"),
    ("contract/detail/preprocessor/traits/aux_", "apply-generate.py"),
    ("contract/detail/preprocessor/traits/aux_", "list-generate.py"),
    ("contract/detail/preprocessor/traits/aux_",
            "select_assertion_-generate.py"),
    ("contract/detail/preprocessor/traits/func", "catches-generate.py"),
    ("contract/detail/preprocessor/traits/func", "postconditions-generate.py"),
    ("contract/detail/preprocessor/tuple", "split-generate.py"),
]

root = os.getcwd()
for s in scripts:
    dir = s[0]
    cmd = "python " + s[1]
    print
    print dir + "$ " + cmd
    os.chdir(dir)
    os.system(cmd)
    os.chdir(root)

print
print "Done. (Add any missing generation Python script to this script.)",

