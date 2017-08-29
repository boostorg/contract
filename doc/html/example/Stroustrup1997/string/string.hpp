// Copyright (C) 2009-2010 Lorenzo Caminiti.
// Use, modification, and distribution is subject to the
// Contract++ Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt.)

// Example of invariant and simple preconditions that throw user
// defined exception on contract failure.

#include <contract.hpp>

// Adapted from an example presented in [Stroustrup1997] to illustrate 
// importance of invariants. Simple preconditions were added where it
// made sense. This should be compiled with CHECK_POSTCONDITION off
// because postconditions are deliberately not used.
// See [Stroustrup1997] for a discussion on the importance of
// invariants, and on pros and cons of using pre and post conditions.
class String {

    CONTRACT_INVARIANT( ({
        if (p == 0 || sz < 0 || TOO_LARGE <= sz || p[sz])
            throw Invariant();
    }) )

    int sz;
    char* p;

public:
    class Range {};                 // exception classes
    class Invariant {};
    class Null {};
    class Too_large {};

    enum { TOO_LARGE = 16000 };     // length limit

    String(const char* q)
    CONTRACT_CONSTRUCTOR( (class) (String)
            (public) (String)( (const char*)(q) )
    (precondition) ({
        if (!q) throw Null();
        if (strlen(q) > TOO_LARGE) throw Too_large();
    })
    (body) (
        ;
    ) )

    ~String(void)
    CONTRACT_DESTRUCTOR( (class) (String)
            (public) (String)( (void) )
    (body) (
        ;
    ) )

    char& operator[](int i)
    CONTRACT_FUNCTION( (class) (String)
            (public) (char&) (operator([], at))( (int)(i) )
    (precondition) ({
        if (i < 0 || sz <= i) throw Range();
    })
    (body) (
        ;
    ) )

    int size(void)
    CONTRACT_FUNCTION( (class) (String)
            (public) (int) (size)( (void) )
    (body) (
        ;
    ) )
};

