
# Copyright (C) 2008-2012 Lorenzo Caminiti
# Distributed under the Boost Software License, Version 1.0
# (see accompanying file LICENSE_1_0.txt or a copy at
# http://www.boost.org/LICENSE_1_0.txt)
# Home at http://sourceforge.net/projects/contractpp

import sys

print 'Importing module:', sys.argv[1]
pydef = __import__(sys.argv[1]) # Import checks contracts (preconditions, etc).

# Check that function can be called successfully.
pydef.f()
pydef.g()
pydef.h()

# Check that docs were set correctly.
assert pydef.f.__doc__ == '''
f() -> None :
    Documentation for f

    C++ signature :
        void f()'''
assert pydef.g.__doc__ == '''
g() -> None :
    Documentation for g

    C++ signature :
        void g()'''
assert pydef.h.__doc__ == '''
h() -> None :
    Documentation for h

    C++ signature :
        void h()'''

