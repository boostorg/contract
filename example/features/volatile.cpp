
// Copyright (C) 2008-2016 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

#include <boost/contract.hpp>
#include <cassert>

//[volatile
class a {
public:
    void invariant() const volatile;    // Invariants cv qualified.
    void invariant() const;             // Invariants const qualified.

    a() { // Check both cv and const invariant (at exit if no throw).
        boost::contract::check c= boost::contract::constructor(this);
    }

    ~a() { // Check both cv and const invariant (at entry).
        boost::contract::check c = boost::contract::destructor(this);
    }

    void m() { // Check const invariant (at entry and exit if no throw).
        boost::contract::check c = boost::contract::public_function(this);
    }

    void c() const { // Check const invariant (at entry and exit if no throw).
        boost::contract::check c = boost::contract::public_function(this);
    }
    
    void v() volatile { // Check cv invariant (at entry and exit if no throw).
        boost::contract::check c = boost::contract::public_function(this);
    }
    
    void cv() const volatile { // Check cv inv. (at entry and exit if no throw).
        boost::contract::check c = boost::contract::public_function(this);
    }
};
//]

bool cv_invariant_checked, const_invariant_checked;
void a::invariant() const volatile { cv_invariant_checked = true; }
void a::invariant() const { const_invariant_checked = true; }

int main() {
    // These failures properly handled only when invariants checked.
    #ifndef BOOST_CONTRACT_NO_EXIT_INVARIANTS
        {
            cv_invariant_checked = const_invariant_checked = false;
            a x;
            assert(cv_invariant_checked);
            assert(const_invariant_checked);

            cv_invariant_checked = const_invariant_checked = false;
            x.m();
            assert(!cv_invariant_checked);
            assert(const_invariant_checked);
            
            cv_invariant_checked = const_invariant_checked = false;
            x.c();
            assert(!cv_invariant_checked);
            assert(const_invariant_checked);
            
            cv_invariant_checked = const_invariant_checked = false;
            x.v();
            assert(cv_invariant_checked);
            assert(!const_invariant_checked);
            
            cv_invariant_checked = const_invariant_checked = false;
            x.cv();
            assert(cv_invariant_checked);
            assert(!const_invariant_checked);
        
            cv_invariant_checked = const_invariant_checked = false;
        } // Call destructor.
        #ifndef BOOST_CONTRACT_NO_ENTRY_INVARIANTS
            assert(cv_invariant_checked);
            assert(const_invariant_checked);
        #endif
    #endif

    return 0;
}

