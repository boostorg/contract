
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

//[stroustrup97_string_header
// File: string.hpp
#ifndef STRING_HPP_
#define STRING_HPP_

#include <contract.hpp>
#include <cstring>

// Adapted from an example presented in [Stroustrup1997] to illustrate
// importance of class invariants. Simple preconditions were added where it
// made sense. This should be compiled with postconditions checking turned off
// (define the `CONTRACT_CONFIG_NO_POSTCONDITIONS` macro) because
// postconditions are deliberately not used.
// See [Stroustrup1997] for a discussion on the importance of class invariants,
// and on pros and cons of using pre and post conditions.
CONTRACT_CLASS(
    class (string)
) {
    CONTRACT_CLASS_INVARIANT(
        // It would be better to assert conditions separately so to generate
        // more informative error in case they fail.
        chars_ ? true : throw invariant_error(),
        size_ >= 0 ? true : throw invariant_error(),
        too_large >= size_ ? true : throw invariant_error(),
        chars_[size_] == '\0' ? true : throw invariant_error()
    )

    // Broken contracts throw user defined exceptions.
    public: class range_error {};
    public: class invariant_error {};
    public: class null_error {};
    public: class too_large_error {};

    public: enum { too_large = 16000 }; // Length limit.

    CONTRACT_CONSTRUCTOR(
        public (string) ( (const char*) chars )
            precondition(
                chars ? true : throw null_error(),
                strlen(chars) <= too_large ? true : throw too_large_error()
            )
    ) ; // Deferred body definition.

    CONTRACT_CONSTRUCTOR(
        public (string) ( (const string&) other )
    ) ;

    CONTRACT_DESTRUCTOR(
        public (~string) ( void )
    ) ;

    CONTRACT_FUNCTION(
        public (char&) operator([])(at) ( int index )
            precondition(
                index >= 0 ? true : throw range_error(),
                size_ > index ? true : throw range_error()
            )
    ) ;

    CONTRACT_FUNCTION(
        public int (size) ( void ) const
    ) ;

    CONTRACT_FUNCTION( // Not public so it does not check class invariants.
        private void (init) ( (const char*) q )
    ) ;
    
    private: int size_;
    private: char* chars_;
};

#endif // #include guard
//]

