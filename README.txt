Boost.Contract -- https://lcaminiti.github.io/boost-contract

This library implements Contract Programming (a.k.a., Design by Contract or DbC)
for the C++ programming language.

All Contract Programming features are supported by this library: subcontracting,
class invariants (also static and volatile), postconditions (with old and return
values), preconditions, customizable actions on assertion failure (terminate,
throw, etc.), optional compilation of assertion and checking, disable assertions
while already checking other assertions (to avoid infinite recursion), etc.

NOTE:   In one of its previous versions, this library passed Boost formal review
        and it was accepted into the Boost libraries. However, the authors have
        not had time yet to add this library to an official Boost release.
See: https://groups.google.com/forum/?fromgroups=#!topic/boost-list/jQ7OjAmos_Y

Copyright (C) 2008-2016 Lorenzo Caminiti
Distributed under the Boost Software License, Version 1.0 (see accompanying
file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
